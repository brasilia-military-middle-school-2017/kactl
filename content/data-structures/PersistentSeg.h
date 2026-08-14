/**
 * Author: Arthur Botelho
 * Description: Persistent Segment Tree. Call "init" to get the root!
 * Time: O(\log N)
 * Status: tested at CSES
 */

template<class I, class S> struct PersistentSeg{
	using T = typename S::T; 
	I n; vector<int> lc, rc; vector<T> val;
	int new_node(int l, int r, T x){
		int res = sz(lc);
		lc.pb(l); rc.pb(r); val.pb(x);
		return res;
	}
	int new_node(int l, int r){return new_node(l, r, S::op(val[l], val[r]));}
	PersistentSeg(){ new_node(0,0,S::id); }
	int init(I s){return n = s, new_node(0,0,S::id);}
	int update(T x, I p, int root){return update(x, p, root, 0, n);}
	int update(T x, I p, int i, I lx, I rx){
		if (rx-lx==1)return new_node(0,0,x);
		I mx = lx + (rx - lx) / 2;
		if (p < mx)return new_node(update(x, p, lc[i], lx, mx), rc[i]);
		else return new_node(lc[i], update(x, p, rc[i], mx, rx));
	}
	T query(I l, I r, int root){return query(l, r+1, root, 0, n);}
	T query(I l, I r, int i, I lx, I rx){
		if (r <= lx or rx <= l)return S::id;
		if (l <= lx and rx <= r)return val[i];
		I mx = (lx+(rx-lx)/2);
		return S::op(query(l, r, lc[i], lx, mx), query(l, r, rc[i], mx, rx));
	}
};