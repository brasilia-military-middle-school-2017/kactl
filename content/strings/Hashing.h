/**
 * Author: Ruan Petrus
 * Description: String hashing (multiple mods and $2^{32}$)
 * Time: O(1) query, O(n) build
 * Memory: O(n)
 * Status: tested
 */
#pragma once

typedef uint64_t ull;
template<int M, class B> struct A {
	int x; B b; A(int x=0) : x(x), b(x) {}
	A(int x, B b) : x(x), b(b) {}
	A operator+(A o) const {int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
	A operator-(A o) const {int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
	A operator*(A o) const { return {(int)((ll)x*o.x % M), b*o.b}; }
	explicit operator ull() const { return x ^ (ull) b << 21; }
};
typedef A<1000000007, A<1000000009, unsigned>> H;
static int C = 9548; // initialize to a number less than MOD or random
struct HashInterval {
	int n; vector<H> ha, pw;
	template<typename S>
	HashInterval(const S & str) : n(sz(str)), ha(n+1), pw(n+1) {
		pw[0] = 1;
		rep(i,0,n)
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H query(int a, int b) { return ha[b+1] - ha[a] * pw[b-a+1]; }
	H queryI(int a, int b) { return query(n - b - 1, n - a - 1); }
};
