/**
 * Author: ChatGPT
 * Description: Logarithmic decomposition. Turns a static DS into an
 * insertion-only dynamic one. DS requires add(x) and build().
 * Active blocks are those k for which bit k of size() is set.
 * Queries should be done by the user, based on active blocks.
 * Time: each element participates in O(log N) builds.
 * Memory: O(N + sum of active DS).
 */
template<class T, class DS> struct LogDecomp {
	vector<T> a; vector<DS> ds;
	void add(T x){
		a.pb(move(x));
		int k=__builtin_ctz(sz(a));
		while(sz(ds)<=k)ds.eb();
		rep(i,0,k+1)ds[i]=DS();
		int l=sz(a)-(1<<k);
		rep(i,l,sz(a))ds[k].add(a[i]);
		ds[k].build();
	}
	bool active(int k) const {return sz(a)>>k&1;}
};