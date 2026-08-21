/**
 * Author: Arthur Botelho
 * Description: Disjoint Sparse Table
 * Requires Monoid (op, id)
 * Time: O(1)
 * Memory: O(N \log N)
 * Status: tested at CSES
 */

#define repinv(i, a, b) for(int i = (a); i >= (b); i--)
template<class S> struct DiST{ 
	using T = typename S::T;
	int n, h; vector<vector<T>> t;
	int lg(unsigned x){return bit_width(x)-1;}
	DiST(vector<T> v): n(bit_ceil(v.size())),
	 	h(lg(n)), t(h, vector<T>(n)){
		v.resize(n, S::id);
		if (n == 1)t.pb(v);
		for(int d = 0, s = 1; d < h; d++, s *= 2)
		for(int m = s; m < n; m += 2*s){ 
			t[d][m] = v[m]; t[d][m-1] = v[m-1];
			rep(i, m+1, m+s)t[d][i] = S::op(t[d][i-1], v[i]);
			repinv(i, m-2, m-s)t[d][i] = S::op(v[i], t[d][i+1]);
		}
	}
	T query(int l, int r){
		if (l==r)return t[0][l];
		int k = lg(l^r);
		return S::op(t[k][l], t[k][r]);
	}
};
