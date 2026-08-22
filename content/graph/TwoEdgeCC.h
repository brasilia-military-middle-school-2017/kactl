/**
 * Author: Ruan Petrus and ChatGPT
 * Description: Finds all two edge connected components in an undirected graph (comp).
 * Edge u-v is a bridge if comp[u] != comp[v]. Can return the tree.
 * Time: O(E + V)
 * Status: tested at CSES
 */
#pragma once

struct TwoEdgeCC {
	const vector<vi>& g;
	const vector<pii>& ed;
	vi tin,st,comp;
	int tim=0,cc=0;
	TwoEdgeCC(const vector<vi>& G,const vector<pii>& E):
		g(G),ed(E),tin(sz(G)),comp(sz(G)){
		rep(v,0,sz(g))if(!tin[v])dfs(v,-1);
	}
	int dfs(int v,int pe){
		int low=tin[v]=++tim,si=sz(st); st.pb(v);
		for(int e:g[v])if(e!=pe){
			auto [a,b]=ed[e]; int u=a^b^v;
			if(tin[u])low=min(low,tin[u]);
			else low=min(low,dfs(u,e));
		}
		if(low==tin[v]){
			while(sz(st)>si)comp[st.back()]=cc,st.pop_back();
			cc++;
		}
		return low;
	}
	vector<vi> tree() const {
		vector<vi> t(cc);
		for(auto [u,v]:ed)if(comp[u]!=comp[v])
			t[comp[u]].pb(comp[v]),t[comp[v]].pb(comp[u]);
		return t;
	}
};
