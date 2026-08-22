/**
 * Author: ChatGPT
 * Description: Dynamic forest diameter with nonnegative node weights.
 * Vertices are 0-indexed. Use an extra node of weight w for each edge.
 * C is the maximum number of real nodes (vertices + edge nodes).
 * Time: O(\log N) amortized.
 * Memory: O(C).
 * Status: randomized against brute force and sent at K from II SBC Cerrado Contest
 */
#pragma once

template<class T> struct TopTreeDiameter {
	struct D { T s=0,l=0,r=0,d=0; };
	struct V { T a=0,b=0,d=0; };
	static D cat(D x,D y){return {
		x.s+y.s,
		max(x.l,x.s+y.l),
		max(y.r,y.s+x.r),
		max({x.d,y.d,x.r+y.l})
	};}
	static void ins(V& z,T x){
		if(x>z.a)z.b=z.a,z.a=x;
		else if(x>z.b)z.b=x;
	}
	static V rake(V x,V y){
		V z; z.d=max(x.d,y.d);
		ins(z,x.a); ins(z,x.b);
		ins(z,y.a); ins(z,y.b);
		return z;
	}
	static V virt(D x){return {x.l,0,x.d};}
	static D one(T w,V v){return {w,w+v.a,w+v.a,max(v.d,w+v.a+v.b)};}
	struct N {
		int p=-1,c[4]={-1,-1,-1,-1};
		T w=0; D d; V v;
		bool rev=0,fake=1;
		N(){}
		N(T W):w(W),d(one(W,{})),fake(0){}
	};
	vector<N> t; vi pool, st;
	int cap,nxt;
	TopTreeDiameter(int n,int C):t(2*C),cap(C),nxt(n){
		rep(i,0,n)t[i]=N(0);
		rep(i,C,2*C)pool.pb(i);
		st.reserve(2*C);
	}
	int node(T w){return t[nxt]=N(w), nxt++;}
	D gd(int x){return x<0?D():t[x].d;}
	V gv(int x){return x<0?V():(t[x].fake?t[x].v:virt(t[x].d));}
	void pull(int x){
		if(t[x].fake)t[x].v=rake(gv(t[x].c[2]),gv(t[x].c[3]));
		else {
			V v=rake(gv(t[x].c[2]),gv(t[x].c[3]));
			t[x].d=cat(cat(gd(t[x].c[0]),one(t[x].w,v)),gd(t[x].c[1]));
		}
	}
	void flip(int x){
		if(x<0||t[x].fake)return;
		swap(t[x].c[0],t[x].c[1]);
		swap(t[x].d.l,t[x].d.r);
		t[x].rev^=1;
	}
	void push(int x){
		if(x>=0&&t[x].rev)flip(t[x].c[0]),flip(t[x].c[1]),t[x].rev=0;
	}
	int dir(int x){
		int p=t[x].p;
		if(p<0)return -1;
		rep(i,0,4)if(t[p].c[i]==x)return i;
		return -1;
	}
	bool root(int x){
		int p=t[x].p;
		return p<0||(t[x].fake?!t[p].fake:dir(x)>=2);
	}
	void attach(int x,int d,int y){
		t[x].c[d]=y;
		if(y>=0)t[y].p=x;
		pull(x);
	}
	void rot(int x){
		int p=t[x].p,g=t[p].p,dx=dir(x),dp=dir(p);
		attach(p,dx,t[x].c[dx^1]); attach(x,dx^1,p);
		if(dp>=0)attach(g,dp,x);
		else t[x].p=g;
	}
	void splay(int x){
		int y=x; st.clear(); st.pb(y);
		while(!root(y))st.pb(y=t[y].p);
		while(sz(st))push(st.back()),st.pop_back();
		while(!root(x)){
			int p=t[x].p;
			if(!root(p))rot(dir(x)==dir(p)?p:x);
			rot(x);
		}
	}
	int fake(){
		assert(sz(pool));
		int x=pool.back();
		pool.pop_back();
		t[x]=N(); return x;
	}
	void addVirt(int x,int y){
		if(y<0)return;
		rep(d,2,4)if(t[x].c[d]<0)return attach(x,d,y);
		int z=fake(); attach(z,2,t[x].c[2]);
		attach(z,3,y); attach(x,2,z);
	}
	void remVirt(int x){
		int p=t[x].p;
		if(t[p].fake){
			int g=t[p].p,o=t[p].c[dir(x)^1],d=dir(p);
			attach(g,d,o);
			if(t[g].fake)splay(g);
			pool.pb(p);
		}
		else attach(p,dir(x),-1);
		t[x].p=-1;
	}
	int realPar(int x){
		int p=t[x].p;
		if(!t[p].fake)return p;
		splay(p); return t[p].p;
	}

	int access(int x){
		pull(x); splay(x); addVirt(x,t[x].c[1]);
		attach(x,1,-1); int w=x;
		while(t[x].p>=0){
			w=realPar(x); splay(w); remVirt(x);
			addVirt(w,t[w].c[1]);
			attach(w,1,x); splay(x);
		}
		return w;
	}
	void rootify(int x){ access(x); flip(x); }
	int findRoot(int x){
		access(x);
		while(push(x),t[x].c[0]>=0)x=t[x].c[0];
		splay(x); return x;
	}
	bool connected(int a,int b){return a==b||findRoot(a)==findRoot(b);}
	void link(int a,int b){
		rootify(a); assert(findRoot(b)!=a);
		access(b); addVirt(b,a);
	}
	void cut(int a,int b){
		rootify(a); access(b);
		assert(t[b].c[0]==a&&t[a].c[1]<0);
		t[b].c[0]=t[a].p=-1; pull(b);
	}
	void update(int x,T w){ access(x); t[x].w=w; pull(x); }
	T diameter(int x){ access(x); return t[x].d.d; }
};
