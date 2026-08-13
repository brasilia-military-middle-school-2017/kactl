/**
 * Author: ChatGPT
 * Description: Compressed Li Chao tree for max queries. Give all query
 * x-coordinates in xs. Lines are added on [l,r].
 * Time: O(log^2 N) add, O(log N) query.
 */
#pragma once

template<class T> struct LiChao {
	static constexpr T NINF = numeric_limits<T>::lowest();
	struct Line {
		T a=0,b=NINF;
		T operator()(T x) { return a*x+b; }
	};
	int n; vector<T> xs; vector<Line> t;
	LiChao(vector<T> _xs):xs(_xs) {
		sort(all(xs)); 
		xs.erase(unique(all(xs)),xs.end());
		n = sz(xs);
		t.resize(4*n);
	}
	void add(Line v, int p, int l, int r) {
		int m=(l+r)/2;
		bool L=v(xs[l])>t[p](xs[l]), M=v(xs[m])>t[p](xs[m]);
		if (M) swap(v,t[p]);
		if (r-l==1) return;
		if (L!=M) add(v,2*p,l,m);
		else add(v,2*p+1,m,r);
	}
	void add(Line v, int ql, int qr, int p, int l, int r) {
		if (qr<=l or r<=ql) return;
		if (ql<=l and r<=qr) return add(v,p,l,r);
		int m=(l+r)/2;
		add(v,ql,qr,2*p,l,m); add(v,ql,qr,2*p+1,m,r);
	}
	void add(T a, T b, T l, T r) {
		int li=lower_bound(all(xs),l)-xs.begin();
		int ri=upper_bound(all(xs),r)-xs.begin();
		if (li<ri) add({a,b},li,ri,1,0,n);
	}
	T query(T x, int i, int p, int l, int r) {
		T ans=t[p](x);
		if (r-l==1) return ans;
		int m=(l+r)/2;
		T best = i < m ? query(x,i,2*p,l,m) : query(x,i,2*p+1,m,r);
		return max(ans, best);
	}
	T query(T x) {
		int i=lower_bound(all(xs),x)-xs.begin();
		return query(x,i,1,0,n);
	}
};