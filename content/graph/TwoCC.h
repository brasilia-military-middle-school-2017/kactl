/**
 * Author: Ruan Petrus
 * Date: 02-23-2026
 * Description: Finds all two edge connected components in an undirected graph.
 * Time: O(E + V)
 * Status: tested in yosup
 */
#pragma once

vector<vector<pair<int, int>>> g;
vector<pair<int, int>> edges;
vi tin, st, bridges;
int dfstime = 0;
vector<vi> twocc;
int dfs(int a, int p) {
  int top = tin[a] = ++dfstime;
  int si = st.size();
  st.pb(a);
  for (auto [b, e]: g[a]) if (e != p) {
    if (tin[b]) top = min(top, tin[b]);
    else {
      int up = dfs(b, e);
      top = min(top, up);
      if (up > tin[a]) bridges.pb(e);
    }
  }
  if (top == tin[a]) {
    twocc.eb(st.begin() + si, st.end());
    st.resize(si);
  }
  return top;
}
void twocomps() {
	int n = sz(g);
  tin.assign(n, 0);
	rep(i, 0, n) if (!tin[i]) dfs(i, -1);
}
vi comp;
vector<vi> tree;
void build_tree() { // Optional
	int n = sz(g);
  tree.resize(sz(twocc)); comp.resize(n);
  rep(i, 0, sz(twocc))
    for (int a: twocc[i]) comp[a] = i;

  for (int eid: bridges) {
    auto [a, b] = edges[eid];
    tree[comp[a]].pb(comp[b]), tree[comp[b]].pb(comp[a]);
  }
}
