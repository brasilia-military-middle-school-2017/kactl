/**
 * Author: Arthur Botelho
 * Description: Spec for Seg Beats. It's similar to other data structures.
 * Time: varies
 * Status: ok
 */

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
