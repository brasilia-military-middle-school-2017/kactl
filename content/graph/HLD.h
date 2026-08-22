/**
 * Author: duduFreire, Benjamin Qi, Oleksandr Kulkov, chilli, Arthur Botelho and ChatGPT
 * Source: https://codeforces.com/blog/entry/53170
 * Description: HLD with lazy path updates and queries. EDGE determines
 * whether values are stored on edges; edge values are stored at the child.
 * Root (r) is configurable. query(u,v) follows the order from u to v.
 * Can be adapted to use normal SegTree (may double performance)
 * S requires T,L,id,op,ch,cmp,rev.
 * Time: O(log^2 N) per path operation, O(log N) per point operation.
 * Memory: O(N).
 * Status: randomized against brute force, tested at CSES Path Queries II
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

template<class S, bool EDGE=false> struct HLD {
	using T=typename S::T; using L=typename S::L;
	int n; vi p,siz,hd,ti,hv; SegBeats<S> seg;
	HLD(vector<vi> g, int r):n(sz(g)),
		p(n,-1),siz(n,1),hd(n),ti(n),hv(n,-1),seg(n) {
		p[r]=r; vi ord={r}; ord.reserve(n);
		rep(i,0,sz(ord)) for(int f : g[ord[i]])
			if (f != p[ord[i]])p[f]=ord[i], ord.pb(f);
		reverse(all(ord));
		for(int v : ord) for(int f : g[v]) if (p[f] == v){
			siz[v] += siz[f];
			if (hv[v] < 0 || siz[f] > siz[hv[v]]) hv[v] = f;
		}
		ord.clear(); ord.pb(r); int tim=0;
		while(sz(ord)) {
			int h = ord.back(); ord.pop_back();
			for(int v = h; v >= 0; v = hv[v]) {
				hd[v] = h; ti[v]=tim++;
				for(int f : g[v]) if(p[f]==v && f != hv[v])ord.pb(f);
			}
		}
	}
	template<class A, class B> void process(int u, int v, A up, B down){
		while(hd[u] != hd[v])
			if(ti[hd[u]] > ti[hd[v]])up(ti[hd[u]],ti[u]),u=p[hd[u]];
			else down(ti[hd[v]],ti[v]),v=p[hd[v]];
		if(ti[u] > ti[v])up(ti[v]+EDGE, ti[u]);
		else  down(ti[u]+EDGE, ti[v]);
	}
	T query(int u, int v) {
		T a=S::id,b=S::id; process(u, v,
			[&](int l,int r){a=S::op(a,S::rev(seg.query(l,r)));},
			[&](int l,int r){b=S::op(seg.query(l,r),b);});
		return S::op(a,b);
	}
	void update(L x, int u, int v) {
		auto f=[&](int l,int r){seg.update(x,l,r);};
		process(u,v,f,f);
	}
};

/* Additional operations:
	void update(L x,int v) {seg.update(x,ti[v],ti[v]);}
	int lca(int u,int v) {
		while(hd[u]!=hd[v])
			if(ti[hd[u]]>ti[hd[v]]) u=p[hd[u]];
			else v=p[hd[v]];
		return ti[u]<ti[v] ? u : v;
	}
	T querySubtree(int v) {
		int l=ti[v]+EDGE,r=ti[v]+siz[v]-1;
		return l>r ? S::id : seg.query(l,r);
	}
	void updateSubtree(L x,int v) {
		int l=ti[v]+EDGE,r=ti[v]+siz[v]-1;
		if(l<=r) seg.update(x,l,r);
	}
*/
