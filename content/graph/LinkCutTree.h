/**
 * Author: ChatGPT
 * Description: Link-Cut Tree for a dynamic forest. Supports link/cut,
 * connectivity, point set and path queries. Nodes are internally represented as 1-based, API is 0-based.
 * S requires T, id, op and rev. query(u,v) follows path order u to v.
 * Store edge values by creating an extra node for each edge.
 * Time: O(\log N) amortized per operation.
 * Memory: O(N).
 */
#pragma once

template<class S> struct LCT {
	using T=typename S::T;
	struct N {
		int p=0,c[2]={}; T v=S::id,ac=S::id; bool rev=0;
		N(T V=S::id):v(V),ac(V){}
	};
	vector<N> t; vi st;
	LCT(int n=0):t(n+1){st.reserve(n+1);}
	LCT(vector<T> a):t(1){
		for(T v:a)t.eb(v);
		st.reserve(sz(t));
	}
	int node(T v=S::id){return t.eb(v), sz(t)-2;} // returns 0-based id
	bool root(int x){
		int p=t[x].p;
		return !p || (t[p].c[0]!=x && t[p].c[1]!=x);
	}
	void pull(int x){
		t[x].ac=S::op(S::op(t[t[x].c[0]].ac,t[x].v), t[t[x].c[1]].ac);
	}
	void push(int x){
		if(t[x].rev) flip(t[x].c[0]),flip(t[x].c[1]),t[x].rev=0;
	}
	void flip(int x){
		if(!x)return;
		swap(t[x].c[0],t[x].c[1]);
		t[x].ac=S::rev(t[x].ac); t[x].rev^=1;
	}
	void rot(int x){
		int p=t[x].p,g=t[p].p,d=t[p].c[1]==x,b=t[x].c[d^1];
		if(!root(p))t[g].c[t[g].c[1]==p]=x;
		t[x].p=g; t[x].c[d^1]=p; t[p].p=x;
		t[p].c[d]=b; if(b)t[b].p=p;
		pull(p); pull(x);
	}
	void splay(int x){
		int y=x; st.clear(); st.pb(y);
		while(!root(y))st.pb(y=t[y].p);
		while(sz(st))push(st.back()),st.pop_back();
		while(!root(x)){
			int p=t[x].p,g=t[p].p;
			if(!root(p))rot((t[p].c[0]==x)==(t[g].c[0]==p)?p:x);
			rot(x);
		}
	}
	int access(int x){
		int last=0;
		for(int y=x;y;y=t[y].p){
			splay(y); t[y].c[1]=last;
			pull(y); last=y;
		}
		splay(x); return last;
	}
	void rootify(int x){ access(x); flip(x); }
	int findRoot(int x){
		access(x); while(push(x),t[x].c[0])x=t[x].c[0];
		splay(x); return x;
	}
	bool connected(int a,int b){ a++; b++; return a==b || findRoot(a)==findRoot(b); }
	void link(int a,int b){
		a++; b++; rootify(a);
		assert(findRoot(b)!=a); t[a].p=b;
	}
	void cut(int a,int b){
		a++; b++; rootify(a); access(b);
		assert(t[b].c[0]==a && !t[a].c[1]);
		t[b].c[0]=t[a].p=0; pull(b);
	}
	void set(int x,T v){ x++; access(x);t[x].v=v; pull(x); }
	T query(int a,int b){
		a++; b++; rootify(a); access(b); return t[b].ac;
	}
};