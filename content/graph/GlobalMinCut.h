/**
 * Author: Simon Lindholm, modified by ChatGPT
 * Description: Stoer-Wagner global minimum cut of an undirected weighted
 * graph given by its adjacency matrix. Returns {cut, one side of the cut}.
 * Requires nonnegative weights and n >= 2.
 * Time: O(N^3)
 * Memory: O(N^2)
 * Status: stress-tested by GPT
 */
#pragma once

pair<ll,vi> globalMinCut(vector<vector<ll>> a) {
	int n=sz(a);
	vi v(n),vis(n),hd(n),tl(n),nx(n,-1); vector<ll> w(n);
	iota(all(v),0); iota(all(hd),0); tl=hd;
	ll best=LLONG_MAX; vi side;
	for(int k=n;k>1;k--) {
		rep(i,0,k) w[v[i]]=vis[v[i]]=0;
		int s = -1, t = -1, pt = -1;
		rep(it,0,k) {
			s = t; t = -1;
			rep(j,0,k) {
				int x=v[j];
				if(!vis[x] && (t<0 || w[x]>w[t]))t=x,pt=j;
			}
			if(it==k-1) break;
			vis[t]=1;
			rep(j,0,k) {
				int x=v[j];
				if(!vis[x]) w[x]+=a[t][x];
			}
		}
		if(w[t]<best) {
			best=w[t]; side.clear();
			for(int x=hd[t];x>=0;x=nx[x]) side.pb(x);
		}
		nx[tl[s]]=hd[t]; tl[s]=tl[t];
		rep(j,0,k) {
			int x=v[j];
			if(x!=s && x!=t)a[x][s]=a[s][x]+=a[t][x];
		}
		v[pt]=v[k-1];
	}
	return {best,side};
}
