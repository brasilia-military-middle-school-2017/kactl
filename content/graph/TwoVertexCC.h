/**
 * Author: Ruan Petrus and ChatGPT
 * Description: Vertex-biconnected components of an undirected graph.
 * comp[e] is the component of edge e; art[v] tells if v is an
 * articulation point. Bridges form singleton-edge components.
 * Handles parallel edges; assumes no self-loops.
 * Time: O(N+M)
 * Memory: O(N+M)
 * Status: stress-tested
 */
#pragma once

struct TwoVertexCC {
	const vector<vi>& g;
	const vector<pii>& ed;
	vi tin,st,comp;
	vector<char> art;
	int tim=0,cc=0;
	TwoVertexCC(const vector<vi>& G,const vector<pii>& E):
		g(G),ed(E),tin(sz(G)),comp(sz(E),-1),art(sz(G)){
		st.reserve(sz(E));
		rep(v,0,sz(g))if(!tin[v])dfs(v,-1);
	}
	int dfs(int v,int pe){
		int low=tin[v]=++tim,ch=0;
		for(int e:g[v])if(e!=pe){
			auto [a,b]=ed[e]; int u=a^b^v;
			if(tin[u]){
				if(tin[u]<tin[v])st.pb(e),low=min(low,tin[u]);
			}
			else{
				ch++; st.pb(e);
				int up=dfs(u,e); low=min(low,up);
				if(up>=tin[v]){
					if(pe!=-1)art[v]=1;
					for(;;){
						int x=st.back(); st.pop_back();
						comp[x]=cc;
						if(x==e)break;
					}
					cc++;
				}
			}
		}
		if(pe==-1)art[v]=ch>1;
		return low;
	}
	pair<vector<vi>,vi> blockCut() const {
		int n=sz(g),k=cc;
		vi id(n,-1),seen(cc,-1); //-1 if isolated
		rep(v,0,n)
			if(art[v])id[v]=k++; // articulation points' id is their separate component
			else if(sz(g[v]))id[v]=comp[g[v][0]];
		vector<vi> t(k);
		rep(v,0,n)if(art[v])for(int e:g[v]){
			int c=comp[e];
			if(seen[c]!=v){
				seen[c]=v;
				t[id[v]].pb(c);
				t[c].pb(id[v]);
			}
		}
		return {t,id}; // tree of components, mapping from node to id in tree
	}
};