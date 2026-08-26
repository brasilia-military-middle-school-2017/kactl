/**
 * Author: ChatGPT
 * Description: Sqrt decomposition for many queries and few point updates.
 * S must be a group.
 * Time: $O(\sqrt N)$ set, $O(1)$ query.
 * Memory: $O(N)$.
 * Status: tested at CSES
 */
template<class S> struct SqrtFastQuery {
	using T=typename S::T;
	int n,B,nb; vector<T> a,pre,bpre;
	SqrtFastQuery(vector<T> A):n(sz(A)),B(max(1,(int)sqrt(n))),
		nb((n+B-1)/B),a(move(A)),pre(n),bpre(nb) {
		rep(k,0,nb){
			T x=S::id;
			rep(i,k*B,min(n,(k+1)*B))pre[i]=x=S::op(x,a[i]);
			bpre[k]=S::op(k?bpre[k-1]:S::id,x);
		}
	}
	void set(T x, int i){
		a[i]=x;
		int k=i/B, e=min(n,(k+1)*B);
		T y=i%B ? pre[i-1] : S::id;
		rep(j,i,e)pre[j]=y=S::op(y,a[j]);
		rep(j,k,nb)bpre[j]=S::op(j?bpre[j-1]:S::id,pre[min(n,(j+1)*B)-1]);
	}
	T query(int l,int r){
		auto pref=[&](int i){
			if(i<0)return S::id;
			int k=i/B;
			return S::op(k?bpre[k-1]:S::id,pre[i]);
		};
		return S::op(S::inv(pref(l-1)),pref(r));
	}
};