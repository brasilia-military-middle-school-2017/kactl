/**
 * Author: Arthur Botelho and ChatGPT
 * Description: Compressed multidimensional SegTree. All update points
 * must be given beforehand. Set updates and inclusive queries.
 * Time: O(log^D K) update/query.
 * Memory: O(K log^(D-1) K).
 */
#pragma once

#define MAs template<class... A>
template<class I, int D, class S> struct CMSEG {
	using T=typename S::T; using P=array<I,D-1>;
	int n; vector<I> x; vector<CMSEG<I,D-1,S>> seg;
	int ilb(I i){return lower_bound(all(x),i)-x.begin();}
	int irb(I i){return upper_bound(all(x),i)-x.begin();}
	CMSEG(vector<array<I,D>> p){
		sort(all(p)); p.erase(unique(all(p)),p.end());
		x.reserve(sz(p));
		for(auto &a:p) if(x.empty() || x.back()!=a[0])x.pb(a[0]);
		vector<vector<P>> ips(2*(n=sz(x)));
		for(auto &a:p){
			P b; rep(j,1,D)b[j-1]=a[j];
			for(int i=ilb(a[0])+n;i;i/=2)ips[i].pb(b);
		}
		seg.reserve(2*n); for(auto &y:ips)seg.eb(move(y));
	}
	MAs T get(I p,A... ps){
		int i=ilb(p);
		return i<n && x[i]==p ? seg[i+n].get(ps...) : S::id;
	}
	MAs void update(T v,I p,A... ps){
		int i=ilb(p)+n; seg[i].update(v,ps...);
		while(i/=2)seg[i].update(S::op(seg[2*i].get(ps...), seg[2*i+1].get(ps...)),ps...);
	}
	MAs T query(I l,I r,A... ps){
		T lv=S::id,rv=S::id;
		for(int L=ilb(l)+n,R=irb(r)+n;L<R;L/=2,R/=2){
			if(L&1)lv=S::op(lv,seg[L++].query(ps...));
			if(R&1)rv=S::op(seg[--R].query(ps...),rv);
		}
		return S::op(lv,rv);
	}
};

template<class I, class S> struct CMSEG<I,0,S> {
	using T=typename S::T;
	T v=S::id;
	CMSEG(vector<array<I,0>> ig){}
	T get(){return v;}
	void update(T x){v=x;}
	T query(){return v;}
};