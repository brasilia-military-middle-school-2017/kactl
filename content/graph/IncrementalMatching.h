/**
 * Author: Ruan Petrus
 * Description: Incremental bipartite matching. Left vertices are activated
 * ONCE with activate(a); returns whether the maximum matching increases.
 * All edges of a must exist before it is activated.
 * Time: O(E) worst case per activation, usually much faster.
 * Memory: O(L+R+E).
 * Status: stress-tested; adversarial instances can be slow.
 */
#pragma once

struct IncrementalMatching {
	vi st,mt,d; vector<vi> g; int t=0;
	IncrementalMatching(int n, int m):st(n),mt(m,-1),d(n),g(n){}
	void add(int a,int b){g[a].pb(b);}
	bool dfs(int a){
		st[a]=-t;
		for(int b:g[a]){
			int c=mt[b]; if(c<0)return mt[b]=a,1;
			int nd=d[a]+1;
			if(st[c]!=t && st[c]!=-t)d[c]=nd,st[c]=t;
			else if(nd<d[c])d[c]=nd;
		}
		for(int b:g[a]){
			int c=mt[b];
			if(d[c]==d[a]+1 && st[c]!=-t && dfs(c))return mt[b]=a,1;
		}
		return 0;
	}
	bool activate(int a){st[a]=++t,d[a]=0;return dfs(a);}
};