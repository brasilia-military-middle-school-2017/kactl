/**
 * Author: Arthur Botelho
 * Description: Lazy Sparse Seg, similar to Lazy Seg (I is index type). Queries also create nodes
 * Time: O(\log N * (ch + cmp)).
 * Status: tested at CSES
 */
#pragma once

template<class I, class S> struct LazySparseSeg{
	using T = typename S::T; using L = typename S::L;
	I n; vector<int> lc, rc; vector<bool> ig;
	vector<T> val; vector<L> lz;
	int new_node(){
		int res = sz(lc);
		lc.pb(0); rc.pb(0); ig.pb(1);
		val.pb(S::id); lz.pb(L());
		return res;
	}
	LazySparseSeg(I s): n(s){ new_node(); new_node(); }
	void apply(int i, L v, I lx, I rx){
		val[i] = S::ch(val[i], v, lx, rx-1);
		if (rx-lx>1)lz[i] = ig[i] ? v : S::cmp(lz[i], v), ig[i] = 0;
	}
	I prop(int i, I lx, I rx){
		I mx = (lx+(rx-lx)/2);
		if (!lc[i])lc[i] = new_node(), rc[i] = new_node();
		if (not ig[i])ig[i] = 1, 
			apply(lc[i], lz[i], lx, mx), apply(rc[i], lz[i], mx, rx);
		return mx;
	}
	void update(L v, I l, I r){return update(v, l, r+1, 1, 0, n);}
	void update(L v, I l, I r, int i, I lx, I rx){
		if (r <= lx or rx <= l)return;
		if (l <= lx and rx <= r)return apply(i, v, lx, rx);
		I mx = prop(i, lx, rx);
		int li = lc[i], ri = rc[i];
		update(v, l, r, li, lx, mx); update(v, l, r, ri, mx, rx);
		val[i] = S::op(val[li], val[ri]);
	} 
	T query(I l, I r){return query(l, r+1, 1, 0, n);}
	T query(I l, I r, int i, I lx, I rx){
		if (r <= lx or rx <= l)return S::id;
		if (l <= lx and rx <= r)return val[i];
		I mx = prop(i, lx, rx);
		return S::op(query(l, r, lc[i], lx, mx), query(l, r, rc[i], mx, rx));
	} 
};
