/**
 * Author: duduFreire, Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2026-24-02
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Does the same thing as a LazySegment tree, but on a tree and with an extra log factor to the complexity. VAL\_EDGES
 * determines if the values are stored in edges. If so, store the value of each edge on its child vertex.
 * Time: O((\log N)^2) for range operations, O(log(n)) for point operations
 * Status: AC on Police Hypothesis
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

template<class S, bool VAL_EDGES>
struct HLD {
	using T = typename S::T; using L = typename S::L;
	int n,tim=0;
	vector<vi> g;
	vi p,siz,hd,ti;
	SegBeats<S> seg, segi;
	HLD(vector<vi> ag) : n(sz(ag)), g(ag), p(n), siz(n,1), hd(n), ti(n),
	seg(bit_ceil((unsigned)n)), segi(bit_ceil((unsigned)n)) { dfs(0); dfs2(0);}
	void dfs(int v) {
		for (int& u : g[v]) {
			g[u].erase(find(all(g[u]), v));
			p[u]=v;
			dfs(u);
			siz[v] += siz[u];
			if (siz[u] > siz[g[v][0]]) swap(u, g[v][0]);
		}
	}
	void dfs2(int v) {
		ti[v]=tim++;
		for (int u : g[v]) {
			hd[u] = (u == g[v][0] ? hd[v] : u);
			dfs2(u);
		}
	}
	template <class B, class C> // ops are [l, r)
	void process(int u, int v, B op1, C op2) {
		for (;;) {
			if (hd[u] == hd[v]) break;
			if (ti[u] < ti[v]) op2(ti[hd[v]], ti[v]+1), v=p[hd[v]];	
			else op1(ti[hd[u]], ti[u]+1), u=p[hd[u]];
		}
		if (ti[u] < ti[v]) op2(ti[u]+VAL_EDGES, ti[v]+1);
		else op1(ti[v]+VAL_EDGES, ti[u]+1);
	}
	T query(int u, int v) { // inclusive on both ends
		T vu = S::id, vv = S::id;
		process(u,v,
		  [&](int l, int r){ vu = S::op(vu, segi.query(n-r,n-l)); },
		  [&](int l, int r){ vv = S::op(seg.query(l,r), vv); } );	
		return S::op(vu,vv);
	}
	void update(L val, int u, int v) {
		process(u,v,
		  [&](int l, int r){ segi.update(val,n-r,n-l); },
		  [&](int l, int r){ seg.update(val,l,r);  });	
	}
	void update(L val, int u) {
		seg.update(val,ti[u], ti[u]+1);
		segi.update(val,n-ti[u]-1, n-ti[u]);
	}
};
