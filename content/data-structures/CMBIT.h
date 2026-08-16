/**
 * Author: Arthur Botelho and Chat GPT
 * Description: Compressed multidimensional BIT. All update points must
 * be given beforehand. Queries are inclusive. K here is the number of update points.
 * Time: O(log^D K) update, O((2log K)^D) query.
 * Memory: O(K log^(D-1) K).
 */
#pragma once

#define MAs template<class... A>
template<class I, int D, class S> struct CMBIT {
	using T=typename S::T; using P=array<I,D-1>;
	int n; vector<I> x; vector<CMBIT<I,D-1,S>> ft;
	int ilb(I i){return (int)(lower_bound(all(x),i)-x.begin());}
	int irb(I i){return (int)(upper_bound(all(x),i)-x.begin());}
	CMBIT(vector<array<I, D>> p){
		sort(all(p)); p.erase(unique(all(p)),p.end());
		x.reserve(sz(p));
		for(auto &a:p) if(x.empty() || x.back()!=a[0])x.pb(a[0]);
		vector<vector<P>> ips(n = sz(x) + 1);
		for(auto &a:p){
			P b; rep(j,1,D) b[j-1]=a[j];
			for(int i=ilb(a[0])+1;i<n;i+=i&-i)ips[i].pb(b);
		}
		ft.reserve(n); for(auto &y:ips) ft.eb(move(y));
	}
	MAs void update(T v, I p, A... ps){
		for(int i=ilb(p)+1;i<n;i+=i&-i)ft[i].update(v,ps...);
	}
	MAs T query(I l, I r, A... ps){
		T a=S::id,b=S::id;
		for(int R = irb(r);R;R-=R&-R)b=S::op(b,ft[R].query(ps...));
		for(int L = ilb(l);L;L-=L&-L)a=S::op(a,ft[L].query(ps...));
		return S::op(b,S::inv(a));
	}
};

template<class I, class S> struct CMBIT<I,0,S> {
	using T=typename S::T;
	T v=S::id;
	CMBIT(vector<array<I,0>> ig) {}
	void update(T x){v=S::op(v,x);}
	T query(){return v;}
};
