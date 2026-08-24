/**
 * Author: ChatGPT
 * Description: Linear basis over xor. add(x) inserts x and returns whether
 * it was independent. can(x) checks if x can be formed. maxXor(x) returns
 * the maximum value obtainable by xoring x with a subset of the basis.
 * Time: O(B) per operation.
 * Memory: O(B).
 */
#pragma once

struct XorBasis {
	static constexpr int B=63;
	array<ll,B> b{};
	bool add(ll x){
		for(int i=B;i--;)if(x>>i&1){
			if(!b[i])return b[i]=x,1;
			x^=b[i];
		}
		return 0;
	}
	bool can(ll x) const {
		for(int i=B;i--;)if(x>>i&1)x^=b[i];
		return !x;
	}
	ll maxXor(ll x=0) const {
		for(int i=B;i--;)x=max(x,x^b[i]);
		return x;
	}
};