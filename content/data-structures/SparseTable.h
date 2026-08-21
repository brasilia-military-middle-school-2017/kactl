/**
 * Author: Arthur Botelho
 * Description: Sparse Table
 * Requires Idempotent Monoid S (op, id)
 * Time: O(1) query, O(n \log n) build
 * Memory: O(n \log n)
 * Status: stress-tested
 */
		
template<class S> struct SpTable{
	using T = typename S::T;
	int n; vector<vector<T>> tab;
	int lg(signed x){return __builtin_clz(1)-__builtin_clz(x);}
	SpTable(vector<T> v):n(sz(v)),tab(1+lg(n),vector<T>(n,S::id)){
		rep(i,0,n)tab[0][i] = v[i];
		rep(i,0,lg(n))rep(j,0,n-(1<<i))
			tab[i+1][j] = S::op(tab[i][j], tab[i][j+(1<<i)]);
	}
	T query(int l, int r){
		int k = lg(++r-l);
		return S::op(tab[k][l], tab[k][r-(1<<k)]);
	}
};
