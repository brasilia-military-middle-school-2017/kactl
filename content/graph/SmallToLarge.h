/**
 * Author: Arthur Botelho
 * Description: good small to large
 * Time: O(N \log N)
 * Status: tested on CSES Distinct Colors
 */
#pragma once

void small_to_large(vector<vector<int>> & g){
	int n = sz(g);
	int cans = 0;
	auto add = [&](int v){ cans += v; };
	auto del = [&](int v){ cans -= v; };
	vector ans(n, 0), big(n, -1), sub(n, 1), pos(n, 0), pre(0, 0);
	auto dfspre = [&](auto&& rec, int v, int p)->void {
		pos[v] = sz(pre); pre.push_back(v);
		for(int f : g[v])if (f != p){
			rec(rec, f, v);
			sub[v] += sub[f];
			if (big[v] == -1 or sub[f] > sub[big[v]])big[v] = f;
		}
	};
	dfspre(dfspre, 0, 0);
	auto dfs = [&](auto&& rec, int v, int p, int keep)->void {
		int b = big[v];
		for(int f : g[v])if (f != p and f != b)rec(rec, f, v, 0);
		if (b != -1)rec(rec, b, v, 1);
		add(v);
		for(int f : g[v])if (f != p and f != b)rep(i,pos[f],pos[f]+sub[f])add(pre[i]);
		ans[v] = cans;
		if (not keep)rep(i,pos[v],pos[v]+sub[v])del(pre[i]);
	};
	dfs(dfs, 0, 0, 1);
}
