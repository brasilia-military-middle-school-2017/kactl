/**
 * Author: ChatGPT
 * Description: Sqrt decomposition for many point updates and few queries.
 * update(i,x) applies a[i] = op(a[i],x). S must be a commutative monoid.
 * Time: $O(1)$ update, $O(\sqrt N)$ query.
 * Memory: $O(N)$.
 * Status: tested at CSES
 */
template<class S> struct SqrtFastUpdate {
	using T=typename S::T;
	int n, B; vector<T> a, b;
	SqrtFastUpdate(vector<T> A):n(sz(A)),B(max(1,(int)sqrt(n))),
		a(move(A)),b((n+B-1)/B,S::id) {
		rep(i,0,n)b[i/B]=S::op(b[i/B],a[i]);
	}
	void update(T x, int i){
		a[i]=S::op(a[i],x);
		b[i/B]=S::op(b[i/B],x);
	}
	T query(int l,int r){
		T x=S::id;
		while(l<=r && l%B)x=S::op(x,a[l++]);
		while(l+B-1<=r)x=S::op(x,b[l/B]),l+=B;
		while(l<=r)x=S::op(x,a[l++]);
		return x;
	}
};