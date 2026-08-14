/**
 * Author: Arthur Botelho
 * Description: Lazy Seg. Can be transformed into Seg Beats by uncommenting conditions.
 * Time: O(\log N * (ch + cmp)).
 * Status: lazy tested
 */
#pragma once

template<class S> struct SegBeats{
	using T = typename S::T; using L = typename S::L;
	int n; vector<T> seg; vector<L> lz; vector<bool> ig;
	SegBeats(unsigned s):n(bit_ceil(s)),seg(2*n,S::id),lz(2*n),ig(2*n,1){}
	void apply(int p, L v, int l, int r){
		seg[p] = S::ch(seg[p],v,l,r-1);
		if (r-l>1)lz[p] = ig[p] ? v : S::cmp(lz[p], v), ig[p] = 0;
	}
	int prop(int p, int l, int r){
		int m = (l+r)/2; 
		if (not ig[p])ig[p] = 1,
			apply(2*p, lz[p], l, m), apply(2*p+1, lz[p], m, r);
		return m;
	}
	void update(L v, int l, int r){return update(v,l,r+1,1,0,n);}
	void update(L v, int lq, int rq, int no, int lx, int rx){
		if (rq <= lx or rx <= lq /*or S::brk(v,seg[no])*/)return;
		if (lq <= lx and rx <= rq /*and S::tag(v,seg[no])*/)return apply(no, v, lx, rx);
		int mx = prop(no,lx,rx); 
		update(v,lq,rq,2*no,lx,mx); update(v,lq,rq,2*no+1,mx,rx);
		seg[no] = S::op(seg[2*no],seg[2*no+1]);
	}
	T query(int l, int r){return query(l,r+1,1,0,n);}
	T query(int lq, int rq, int no, int lx, int rx){
		if (rq <= lx or rx <= lq)return S::id;
		if (lq <= lx and rx <= rq)return seg[no];
		int mx = prop(no,lx,rx); 
		return S::op(query(lq,rq,2*no,lx,mx),query(lq,rq,2*no+1,mx,rx));
	}
};