/**
 * Author: Ruan Petrus
 * Date: 2026-02-23
 * License: CC0
 * Source: Folklore
 * Description: Finds all biconnected components in an undirected graph.
 *  In a biconnected component there
 *  are at least two internally disjoint paths between any two nodes a cycle
 *  exists through them. Note that a node can be in several components. 
 *  Every edge is in a single component. Nodes without edges will
 *  not be in any components
 * Time: O(E + V)
 * Status: tested in yosup
 */
#pragma once

vector<pair<int, int>> edges; // edges
vector<vector<pair<int, int>>> g; // [b, edge idx]
vi tin, st, art;
int dfstime = 0;
vector<vi> bcc;
int dfs(int a, int p) {
	int top = tin[a] = ++dfstime;
	bool child = (p != -1);
	for (auto [b, e]: g[a]) {
		if (tin[b]) {
			top = min(top, tin[b]);
			if (tin[b] < tin[a]) st.pb(e);
		}
		else {
			int si = sz(st);
			int up = dfs(b, e);
			top = min(top, up);
			if (up > tin[a]) { /*e is a bridge */}
			if (up >= tin[a]) {
				st.pb(e);
				bcc.eb(st.begin() + si, st.end());
				st.resize(si);
				art[a] += child;
				child = true;
			}
			else if (up < tin[a]) st.pb(e);
		}
	}
	return top;
}
void bicomps() {
	int n = sz(g);
	tin.assign(n, 0), art.assign(n, 0);
	rep(i,0,n) if (!tin[i]) dfs(i, -1);
}
vi comp;
vector<vi> tree;
void build_tree() { // Optional
	int n = sz(g);
	comp.resize(n), tree.resize(n + sz(bcc));
	rep(i, 0, sz(bcc)) {
		for (int eid: bcc[i]) {
			auto [a, b] = edges[eid];
			if (art[a] && (empty(tree[a]) || tree[a].back() != n+i)) tree[a].pb(n+i), tree[n+i].pb(a);
			if (art[b] && (empty(tree[b]) || tree[b].back() != n+i)) tree[b].pb(n+i), tree[n+i].pb(b);
			comp[a] = comp[b] = n + i;
		}
	}
	rep(i, 0, n) if (art[i]) comp[i] = i;
}
