/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Dynamic CHT where you can add lines of the form ax+b, and query maximum values at points x. 
 * For doubles, use inf = 1/.0, floordiv(a,b) = a/b
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

ll floordiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b); 
}
struct Line {
	mutable ll a, b, p;
	bool operator<(const Line& o) const { return a < o.a; }
	bool operator<(ll x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
	bool isect(iterator i, iterator j) {
		if (j == end()) return i->p = oo, 0;
		if (i->a == j->a) i->p = i->b > j->b ? oo : -oo;
		else i->p = floordiv(j->b - i->b, i->a - j->a);
		return i->p >= j->p;
	}
	void add(ll a, ll b) {
		auto k = insert({a, b, 0}), j = k++, i = j;
		while (isect(j, k)) k = erase(k);
		if (i != begin() && isect(--i, j)) isect(i, j = erase(j));
		while ((j = i) != begin() && (--i)->p >= j->p)
			isect(i, erase(j));
	}
	ll query(ll x) {
		if (empty())return -oo;
		auto l = *lower_bound(x);
		return l.a * x + l.b;
	}
};
