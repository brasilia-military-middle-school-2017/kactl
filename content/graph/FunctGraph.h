/**
 * Author: ChatGPT
 * Description: Functional graph. head[v] is the cycle vertex reached by v,
 * comp[v] is its component/cycle index, cycles contains every directed cycle.
 * Time: O(N)
 * Memory: O(N)
 */
struct FunctGraph {
	int n; vi head, comp; vector<vi> cycles;
	FunctGraph(const vi& f):n(sz(f)),head(n,-1),comp(n,-1){
		vi deg(n), q; 
		for(int v : f)deg[v]++;
		q.reserve(n);
		rep(v,0,n)if (!deg[v])q.pb(v);
		rep(i,0,sz(q)){
			int v=q[i];
			if(!--deg[f[v]])q.pb(f[v]);
		}
		rep(v,0,n)if (deg[v] && head[v] < 0){
			int c=sz(cycles); vi cyc;
			for(int u = v; head[u] < 0; u = f[u])
				head[u] = u, comp[u] = c, cyc.pb(u);
			cycles.pb(move(cyc));
		}
		for(int i = sz(q); i--;){
			int v=q[i];
			head[v]=head[f[v]];
			comp[v]=comp[f[v]];
		}
	}
};
