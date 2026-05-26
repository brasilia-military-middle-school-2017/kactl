/**
 * Author: Arthur Botelho
 * Description: Lazy Sparse Seg (half-open). Lazy can be removed (prop, lz, ig, ch/cmp)
 * Time: O(\log N * (ch + cmp)).
 * Status: not tested
 */
#pragma once

template<class I, class S> struct LazySparseSeg{ //I is index type
	using T = typename S::T; //value type
	using L = typename S::L; //update type
	struct Node{int lc, rc; T val; L lz; bool ig;};
	I n; vector<Node> v;
	int new_node(){return v.eb(0,0,S::id,L(),1), sz(v)-1;}
	LazySparseSeg(I s): n(s){
		//v.reserve(MXN); //faster node creation
		new_node(); new_node(); //blank and root node
	}
	void apply(int i, L x, I lx, I rx){
		v[i].val = S::ch(v[i].val, x, lx, rx);
		if (rx-lx>1)v[i].lz = v[i].ig ? x : S::cmp(v[i].lz, x), v[i].ig = 0;
	}
	void prop(int i, I lx, I rx){
		if (!v[i].lc)v[i].lc = new_node(), v[i].rc = new_node();
		if (v[i].ig)return;
		I mx = (lx+(rx-lx)/2); v[i].ig = 1;
		apply(v[i].lc, v[i].lz, lx, mx); apply(v[i].rc, v[i].lz, mx, rx);
	}
	void update(L x, I l, I r){return update(x, l, r, 1, 0, n);}
	void update(L x, I l, I r, int i, I lx, I rx){
		if (r <= lx or rx <= l)return;
		if (l <= lx and rx <= r)return apply(i, x, lx, rx);
		I mx = (lx+(rx-lx)/2); prop(i, lx, rx);
		int lc = v[i].lc, rc = v[i].rc;
		update(x, l, r, lc, lx, mx); update(x, l, r, rc, mx, rx);
		v[i].val = S::op(v[lc].val, v[rc].val);
	} 
	T query(I l, I r){return query(l, r, 1, 0, n);}
	T query(I l, I r, int i, I lx, I rx){
		if (r <= lx or rx <= l)return S::id;
		if (l <= lx and rx <= r)return v[i].val;
		I mx = (lx+(rx-lx)/2); prop(i, lx, rx);
		return S::op(query(l, r, v[i].lc, lx, mx), query(l, r, v[i].rc, mx, rx));
	} 
};
