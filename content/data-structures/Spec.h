/**
 * Author: Arthur Botelho
 * Description: Algebraic structures for RQDS. Includes Ruan's version.
 * Time: varies
 * Status: ok
 */

struct Group { //sum
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b){return a+b;}
	static T inv(T a){return -a;}
};

struct LazySpecRuan { //sum
	using S = int;
	using K = int;
	static S op(S a, S b) { return max(a, b); }
	static S update(K f, S a) { return f + a; }
	static K compose(const K f, const K g) { return f + g; }
	static S id() { return 0; }
};

struct LazySpecArthur { //set add sum
	using T = ll;
	using L = pair<int, ll>;
	static constexpr T id = 0;
	static T op(T a, T b){return a + b;}
	static T ch(T past, L upd, int lx, int rx){
		ll s = rx-lx;
		auto [t, x] = upd;
		if (t)return s*x;
		else return past+s*x;
	}
	static L cmp(L cur, L upd){
		auto [t1, x1] = cur;
		auto [t2, x2] = upd;
		if (t2)return upd;
		else return {t1, x1+x2};
	}
};

struct node{int max1,max2,maxc; ll sum;};
struct BeatsSpec{ //chmin sum
	using T = node; using L = int;
	static constexpr T id = node{-oo,-oo,0,0};
	static T op(T a, T b){
		node n;
		if (a.max1 > b.max1){
			n.max1 = a.max1;
			n.max2 = max(a.max2, b.max1);
			n.maxc = a.maxc;
		}
		else if (a.max1 == b.max1){
			n.max1 = a.max1;
			n.max2 = max(a.max2, b.max2);
			n.maxc = a.maxc+b.maxc;
		}
		else{
			n.max1 = b.max1;
			n.max2 = max(b.max2, a.max1);
			n.maxc = b.maxc;
		}
		n.sum=a.sum+b.sum;
		return n;
	}
	static T ch(T a, L b, int l, int r){
		if (a.max2 <= b)a.sum -= (ll)(a.max1-b)*a.maxc, a.max1 = b;
		return a;
	}
	static L cmp(L a, L b){return min(a,b);}
	static bool brk(L a, T b){return b.max1 <= a;}
	static bool tag(L a, T b){return b.max2 < a;}
};
