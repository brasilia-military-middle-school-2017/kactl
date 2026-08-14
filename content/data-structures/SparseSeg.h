/**
 * Author: Arthur Botelho
 * Description: Sparse Seg (I is index type)
 * Time: O(\log N)
 * Status: tested at CSES
 */
#pragma once

template<class I, class S> struct SparseSeg{ 
	using T = typename S::T;
	I n; vector<int> lc, rc; vector<T> val;
	int new_node(){
		int res = sz(lc);
		lc.pb(0); rc.pb(0); val.pb(S::id);
		return res;
	}
	SparseSeg(I s): n(s){ new_node(); new_node(); }
	void update(T x, I p){return update(x, p, 1, 0, n);}
	void update(T x, I p, int i, I lx, I rx){
		if (rx-lx==1){val[i] = x; return;}
		I mx = (lx+(rx-lx)/2);
		int li = lc[i], ri = rc[i];
		if (p < mx){
			if (not li)li = lc[i] = new_node();
			update(x, p, li, lx, mx);
		}
		else{
			if (not ri)ri = rc[i] = new_node();
			update(x, p, ri, mx, rx);
		}
		val[i] = S::op(val[li], val[ri]);
	} 
	T query(I l, I r){return query(l, r+1, 1, 0, n);}
	T query(I l, I r, int i, I lx, I rx){
		if (r <= lx or rx <= l)return S::id;
		if (l <= lx and rx <= r)return val[i];
		I mx = (lx+(rx-lx)/2);
		return S::op(query(l, r, lc[i], lx, mx), query(l, r, rc[i], mx, rx));
	} 
};
