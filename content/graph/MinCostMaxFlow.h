/**
 * Author: Stanford, Arthur Botelho and ChatGPT
 * Description: Min-cost max-flow with potentials. Reuses each Dijkstra
 * to push flow through the shortest-path subgraph. If initial costs can
 * be negative, call setpi(s) first. Negative cost cycles are unsupported.
 * Positive edge.flow values give the resulting flow.
 * Time: O(F E log V) worst case. O(VE) for setpi.
 * Status: stress-tested
 */
#pragma once

#include <bits/extc++.h>
struct MCMF {
	static constexpr ll INF=LLONG_MAX/4;
	struct edge { int to,rev; ll cap,cost,flow; };
	using PQ=__gnu_pbds::priority_queue<pair<ll,int>>;
	int n; vector<vector<edge>> ed; vector<ll> dist,pi;
	vi ptr; vector<char> on; vector<PQ::point_iterator> its;
	MCMF(int _n):n(_n),ed(n),dist(n),pi(n),ptr(n),on(n),its(n){}
	void addEdge(int a,int b,ll cap,ll cost){
		ed[a].pb({b,sz(ed[b]),cap,cost,0});
		ed[b].pb({a,sz(ed[a])-1,0,-cost,0});
	}
	ll rem(const edge& e){return e.cap-e.flow;}
	void setpi(int s){
		fill(all(pi),INF); pi[s]=0;
		rep(k,0,n){
			bool ch=0;
			rep(v,0,n)if(pi[v]<INF)for(auto& e:ed[v])
				if(rem(e)>0 && pi[e.to]>pi[v]+e.cost)
					pi[e.to]=pi[v]+e.cost,ch=1;
			if(!ch)return;
		}
		assert(0); // reachable negative cost cycle
	}
	bool path(int s,int t){
		fill(all(dist),INF); fill(all(ptr),0); dist[s]=0;
		PQ q; q.push({0,s});
		while(!q.empty()){
			int v=q.top().second; q.pop(); ll d=dist[v];
			for(auto& e:ed[v])if(rem(e)>0){
				ll nd=d+e.cost+pi[v]-pi[e.to];
				if(nd>=dist[e.to])continue;
				if(dist[e.to]==INF)its[e.to]=q.push({-nd,e.to});
				else q.modify(its[e.to],{-nd,e.to});
				dist[e.to]=nd;
			}
		}
		if(dist[t]==INF)return 0;
		rep(v,0,n)if(dist[v]<INF)pi[v]+=dist[v];
		return 1;
	}
	ll push(int v,int t,ll f){
		if(v==t)return f;
		on[v]=1; ll ret=0;
		for(int& i=ptr[v];i<sz(ed[v])&&f;i++){
			edge& e=ed[v][i];
			if(on[e.to] || rem(e)<=0 || e.cost+pi[v]-pi[e.to])continue;
			ll x=push(e.to,t,min(f,rem(e)));
			e.flow+=x; ed[e.to][e.rev].flow-=x;
			f-=x; ret+=x;
		}
		return on[v]=0, ret;
	}
	pair<ll,ll> maxflow(int s,int t){
		ll flow=0,cost=0;
		while(path(s,t))if (ll f=push(s,t,INF))
			flow+=f,cost+=f*(pi[t]-pi[s]);
		return {flow,cost};
	}
};