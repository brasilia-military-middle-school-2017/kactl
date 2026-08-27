/**
 * Author: Arthur Botelho
 * Description: SOS DP. Calculates sum over subsets and supersets
 * Time: O(N \log N).
 * Memory: O(N).
 */
#pragma once

pair<vi, vi> sos(int l, int n, vi& a){ // n = 1 << l
	auto sub = a;
	auto sup = a;
	rep(b,0,l)rep(i,0,n)
		if (i & (1 << b))sub[i] += sub[i^(1<<b)];
		else sup[i] += sup[i|(1<<b)];
	return {sub, sup};
}
