/**
 * Author: Arthur Botelho
 * Description: Persistent Lazy Sparse Segment Tree. Call "init" to get the root!
 * Time: O(\log N * (ch + cmp))
 * Status: tested at Wilson's "hld" problem in Polygon
 */

template<class I, class S> struct LazyPersistentSeg{
	using T = typename S::T;
	using L = typename S::L;
	I n; vector<int> lc, rc; vector<bool> ig;
	vector<T> val; vector<L> lz;
	int new_node(int l, int r){
		int res = sz(lc);
		lc.pb(l); rc.pb(r); ig.pb(1);
		val.pb(S::op(val[l], val[r])); lz.pb(L());
		return res;
	}
	LazyPersistentSeg(){
		lc.pb(0); rc.pb(0); ig.pb(1);
		val.pb(S::id); lz.pb(L());
	}
	int init(I s){return n = s, new_node(0, 0);}
	int lazy_clone(int i, L v, I lx, I rx){
		int ni = new_node(lc[i], rc[i]);
		lz[ni] = ig[i] ? v : S::cmp(lz[i], v);
		ig[ni] = 0; val[ni] = S::ch(val[i], v, lx, rx);
		return ni;
	}
	I prop(int i, I lx, I rx){
		I mx = lx + (rx - lx) / 2;
		if (not ig[i]){
			ig[i] = 1; if (lx < rx)
			lc[i] = lazy_clone(lc[i], lz[i], lx, mx),
			rc[i] = lazy_clone(rc[i], lz[i], mx, rx);
		}
		return mx;
	}
	int update(L v, I l, I r, int root){return update(v, l, r+1, root, 0, n);}
	int update(L v, I l, I r, int i, I lx, I rx){
		if (r <= lx or rx <= l)return i;
		if (l <= lx and rx <= r)return lazy_clone(i, v, lx, rx);
		I mx = prop(i, lx, rx);
		return new_node(update(v, l, r, lc[i], lx, mx), update(v, l, r, rc[i], mx, rx));
	}
	T query(I l, I r, int root){return query(l, r+1, root, 0, n);}
	T query(I l, I r, int i, I lx, I rx){
		if (r <= lx or rx <= l)return S::id;
		if (l <= lx and rx <= r)return val[i];
		I mx = prop(i, lx, rx);
		return S::op(query(l, r, lc[i], lx, mx), query(l, r, rc[i], mx, rx));
	}
};