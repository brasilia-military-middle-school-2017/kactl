/**
 * Author: ChatGPT
 * Description: Immediate dominators from root. idom[root]=root and
 * idom[v]=-1 if v is unreachable. tree() builds the dominator tree on demand.
 * Time: O((N+M) log N)
 * Memory: O(N+M)
 * Status: randomized against brute force
 */
#pragma once

struct DominatorTree {
	vi idom;
	DominatorTree(const vector<vi>& g, int root) {
		int n=sz(g); vi id(n,-1), rev, par;
		{ // DFS
			vector<pii> st={{root,0}};
			id[root]=0; rev.pb(root); par.pb(-1);
			while(sz(st)) {
				auto &[u,i]=st.back();
				if(i==sz(g[u])) { st.pop_back(); continue; }
				int v=g[u][i++];
				if(id[v]<0)id[v]=sz(rev),rev.pb(v),par.pb(id[u]),st.pb({v,0});
			}
		}
		int N=sz(rev); vi off(N+1);
		rep(i,0,N)for(int v : g[rev[i]])off[id[v]+1]++;
		rep(i,1,N+1)off[i]+=off[i-1];
		vi pre(off[N]);
		rep(i,0,N)for(int v : g[rev[i]])pre[off[id[v]]++]=i;
		for(int i=N;i;i--)off[i]=off[i-1];
		off[0]=0;
		fill(all(id),-1); // reused as bucket heads
		vi sd(N),dom(N,-1),dsu(N),lab(N),st;
		iota(all(sd),0); iota(all(dsu),0); iota(all(lab),0);
		st.reserve(N);
		auto fnd = [&](int v) {
			if(dsu[v]==v) return v;
			st.clear(); int x=v;
			while(dsu[x]!=x) st.pb(x),x=dsu[x];
			int a=st.back();
			for(int k=sz(st)-1;k--;) {
				int u=st[k],p=dsu[u];
				if(sd[lab[p]]<sd[lab[u]]) lab[u]=lab[p];
				dsu[u]=a;
			}
			return lab[v];
		};
		for(int u=N;u--;) {
			rep(e,off[u],off[u+1])sd[u]=min(sd[u],sd[fnd(pre[e])]);
			if(u) dom[u]=id[sd[u]],id[sd[u]]=u;
			for(int v=id[u];v>=0;) {
				int nx=dom[v],w=fnd(v);
				dom[v]=sd[w]==sd[v] ? sd[v] : w;
				v=nx;
			}
			if(u) dsu[u]=par[u];
		}
		rep(u,1,N)if(dom[u]!=sd[u])dom[u]=dom[dom[u]];
		fill(all(id),-1); id[root]=root;
		rep(u,1,N) id[rev[u]]=rev[dom[u]];
		idom=move(id);
	}
	vector<vi> tree() const {
		vector<vi> t(sz(idom));
		rep(v,0,sz(idom))if(idom[v]>=0 && idom[v]!=v)t[idom[v]].pb(v);
		return t;
	}
};