/**
 * Author: Arthur Botelho
 * Description: Lazy Seg (half-open), N must be a power of 2. Can be transformed into Seg Beats by uncommenting conditions.
 * Time: O(\log N * (ch + cmp)).
 * Status: lazy tested
 */
#pragma once

template<class S> struct SegBeats{ // n MUST be a power of 2
	using T = typename S::T; using L = typename S::L;
	int n; vector<T> seg; vector<L> lz; vector<bool> ig;
	SegBeats(int s):n(s),seg(2*n,S::id),lz(2*n),ig(2*n,1){}
	void apply(int p, L v, int l, int r){
		seg[p] = S::ch(seg[p],v,l,r);
		if (r-l>1)lz[p] = ig[p] ? v : S::cmp(lz[p], v), ig[p] = 0;
	}
	void prop(int p, int l, int r){
		if (ig[p])return;
		int m = (l+r)/2; ig[p] = 1;
		apply(2*p, lz[p], l, m);
		apply(2*p+1, lz[p], m, r);
	}
	void update(L v, int l, int r){return update(v,l,r,1,0,n);}
	void update(L v, int lq, int rq, int no, int lx, int rx){
		if (rq <= lx or rx <= lq /*or S::brk(v,seg[no])*/)return;
		if (lq <= lx and rx <= rq /*and S::tag(v,seg[no])*/)return apply(no, v, lx, rx);
		int mid = (lx+rx)/2; prop(no,lx,rx); 
		update(v,lq,rq,2*no,lx,mid); update(v,lq,rq,2*no+1,mid,rx);
		seg[no] = S::op(seg[2*no],seg[2*no+1]);
	}
	T query(int l, int r){return query(l,r,1,0,n);}
	T query(int lq, int rq, int no, int lx, int rx){
		if (rq <= lx or rx <= lq)return S::id;
		if (lq <= lx and rx <= rq)return seg[no];
		int mid = (lx+rx)/2; prop(no,lx,rx); 
		return S::op(query(lq,rq,2*no,lx,mid),query(lq,rq,2*no+1,mid,rx));
	}
};