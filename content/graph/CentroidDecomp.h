/**
 * Author: Arthur Botelho and ChatGPT
 * Description: Centroid decomposition. process(c,p,dead) is called before
 * removing centroid c; p is its parent in the centroid tree. Use const auto \& dead.
 * Time: O(N \log N + process calls).
 * Memory: O(N).
 */
#pragma once

template<class F>
void centroidDecomp(const vector<vi>& g, F process, int root){
	int n=sz(g); vi sub(n); vector<char> dead(n);
	vector<pii> ord; ord.reserve(n);
	auto dfs=[&](auto&& go, int r, int cp)->void {
		ord.clear(); ord.pb({r,-1});
		rep(i,0,sz(ord)){
			auto [v, p] = ord[i]; sub[v] = 1;
			for(int f : g[v])if (f != p && !dead[f])ord.pb({f,v});
		}
		for(int i=sz(ord);i--;){
			auto [v, p] = ord[i];
			if(p >= 0)sub[p] += sub[v];
		}
		int s = sz(ord), c = r, p = -1;
		for(;;){
			int nx=-1;
			for(int f : g[c]) if(f != p && !dead[f] && 2*sub[f] > s){nx=f; break;}
			if(nx < 0)break;
			p=c; c=nx;
		}
		process(c, cp, dead); dead[c] = 1;
		for(int f : g[c])if (!dead[f]) go(go, f, c);
	};
	dfs(dfs, root, -1);
}
