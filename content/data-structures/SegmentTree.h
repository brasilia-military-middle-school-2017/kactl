/**
 * Author: Arthur Botelho
 * Description: Half-Open Iterative SegTree
 * Time: O(\log N)
 * Status: not tested
 */
#pragma once

template<class S> struct SegTree{
	using T = typename S::T;
	int n; vector<T> seg;
	SegTree(int s):n(s),seg(2*n,S::id){}
	void update(T x, int i){
		for(seg[i+=n]=x;i/=2;)
			seg[i] = S::op(seg[2*i], seg[2*i+1])
	}
	T query(int l, int r){ // [l, r)
		T vl=S::id, vr=S::id;
		for(l+=n,r+=n;l<r;l/=2,r/=2){
			if (l&1)vl = S::op(vl, seg[l++]);
			if (r&1)vr = S::op(seg[--r], vr);
		} 
		return S::op(vl, vr);
	}
};