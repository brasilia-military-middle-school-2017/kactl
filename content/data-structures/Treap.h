/**
 * Author: Arthur Botelho and ChatGPT
 * Description: Implicit Treap. Dynamic array with insert/erase, lazy
 * range updates, queries and reversals. Ranges are inclusive. Operations are described at the end.
 * S requires T,L,id,op,ch,cmp,rev (what happens to range val when reversed). ch always receives [0,len-1].
 * Time: O(log N) expected per operation.
 */
#pragma once

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class S> struct Treap {
	using T=typename S::T; using L=typename S::L;
	struct N {
		int l=0, r=0,c=0; unsigned y=0;
		T v=S::id, ac=S::id; L lz{};
		bool ig=1,rv=0;
		N(int C=0, T V=S::id, unsigned Y=0):c(C),y(Y),v(V),ac(V){}
	};
	vector<N> t; int rt=0;
	Treap():t(1){}
	int node(T v){return t.emplace_back(1,v,rng()), sz(t)-1;}
	void apply(int p,L v){
		if(!p)return;
		t[p].v=S::ch(t[p].v,v,0,0);
		t[p].ac=S::ch(t[p].ac,v,0,t[p].c-1);
		t[p].lz=t[p].ig?v:S::cmp(t[p].lz,v); t[p].ig=0;
	}
	void flip(int p){
		if(!p)return;
		swap(t[p].l,t[p].r);
		t[p].ac=S::rev(t[p].ac);
		t[p].rv^=1;
	}
	void push(int p){
		if(t[p].rv) flip(t[p].l),flip(t[p].r),t[p].rv=0;
		if(!t[p].ig)apply(t[p].l,t[p].lz),apply(t[p].r,t[p].lz),t[p].ig=1;
	}
	void pull(int p){
		t[p].c=t[t[p].l].c+t[t[p].r].c+1;
		t[p].ac=S::op(S::op(t[t[p].l].ac,t[p].v),t[t[p].r].ac);
	}
	pair<int,int> split(int p,int k){ // first k go left
		if(!p)return {};
		push(p);
		if(t[t[p].l].c>=k){
			auto [a,b]=split(t[p].l,k);
			t[p].l=b; pull(p); return {a,p};
		}
		auto [a,b]=split(t[p].r,k-t[t[p].l].c-1);
		t[p].r=a; pull(p); return {p,b};
	}
	int merge(int a,int b){
		if(!a||!b)return a?a:b;
		if(t[a].y>t[b].y){
			push(a); t[a].r=merge(t[a].r,b); pull(a); return a;
		}
		push(b); t[b].l=merge(a,t[b].l); pull(b); return b;
	}
};

/* Additional optional operations:
	Treap(vector<T> a={}):t(1){
		t.reserve(sz(a)+1);
		for(T x:a)rt=merge(rt,node(x));
	}
	array<int,3> cut(int l,int r){
		auto [a,c]=split(rt,r+1);
		auto [x,b]=split(a,l);
		return {x,b,c};
	}
	void join(array<int,3> a){rt=merge(merge(a[0],a[1]),a[2]);}
	void insert(int p,T v){
		auto [a,b]=split(rt,p);
		rt=merge(merge(a,node(v)),b);
	}
	void erase(int l,int r){
		auto a=cut(l,r);
		rt=merge(a[0],a[2]);
	}
	void update(L v,int l,int r){
		auto a=cut(l,r); apply(a[1],v); join(a);
	}
	void reverse(int l,int r){
		auto a=cut(l,r); flip(a[1]); join(a);
	}
	T query(int l,int r){
		auto a=cut(l,r);
		T ans=t[a[1]].ac; join(a); return ans;
	}
	T get(int p){return query(p,p);}
	int size(){return t[rt].c;}
*/