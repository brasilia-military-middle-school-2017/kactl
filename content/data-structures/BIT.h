/**
 * Author: Arthur Botelho
 * Description: BIT/Fenwick Tree, requires abelian group (T, id, op, inv).
 * For N = $10^7$, allocate h(n)+1 and swap all access bit[i] for bit[h(i)]
 * Time: $O(\log N)$.
 */
#pragma once

#define chf(a, f, b) a = f(a, b)
//int h(x){return x+(x>>10);} for N = $10^7$
template<class S> struct BIT{
	using T = typename S::T;
	int n; vector<T> bit;
	int lb(int x){return x&(-x);}
	BIT(vector<T> v):n(sz(v)),bit(1+n,S::id){
		rep(i,1,n+1){
			chf(bit[i], S::op, v[i-1]);
			if (i+lb(i)<=n)chf(bit[i+lb(i)], S::op, bit[i]);
		}
	}
	void add(T x, int p){for(p++;p<=n;p+=lb(p))chf(bit[p],S::op,x);}
	T query(int l, int r){
		T lv=S::id, rv=S::id; r++;
		for(;r>=1;r-=lb(r))chf(rv,S::op,bit[r]);
		for(;l>=1;l-=lb(l))chf(lv,S::op,bit[l]);
		return S::op(rv,S::inv(lv));
	}
};