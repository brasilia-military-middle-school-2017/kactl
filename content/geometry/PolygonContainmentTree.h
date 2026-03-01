/**
 * Author: Arthur Botelho
 * Description: building tree of polygon containment
 * Time: O(N \log N)
 * Memory: O(N)
 * Status: tested
*/

struct P { ll x, y; };

int current_x;
struct Segment {
	int idx; P p1, p2; bool is_upper;
	Segment(P p, P q, int i): idx(i), p1(p), p2(q), is_upper(p2.x < p1.x) { if (is_upper)swap(p1, p2); }
	ld get_y(ll x) const { return (ld) (p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x) + p1.y; }
	tuple<ld, bool, int> get_comp() const { return {get_y(current_x), is_upper, p2.x}; }
	bool operator<(const Segment & o) const { return get_comp() < o.get_comp(); }
};
 
vector<int> build(vector<vector<P>>& polygons) {
	int n = sz(polygons);
	vector<tuple<int, int, int, Segment>> edges; // polygon edges
	rep(idx, 0, n) {
		const auto & v = polygons[idx];
		rep(i, 0, sz(v)) {
			int j = (i + 1) % sz(v);
			if (v[i].x == v[j].x)continue; // ignores vertical edges
			Segment seg = Segment(v[i], v[j], idx);
			edges.eb(seg.p1.x, 0, -seg.p1.y, seg);
			edges.eb(seg.p2.x, 1, -seg.p2.y, seg);
		}
	}
	sort(edges.begin(), edges.end());
	set<Segment> s;
	vector pai(n+1, n), vis(n, 0);
	for (auto [l, t, y, seg]: edges) {
		current_x = l;
		int i = seg.idx;
		if (t == 0) {
			if (not vis[i]) {
				vis[i] = true;
				auto it = s.upper_bound(seg);
				if (it == s.end())pai[i] = n;
				else if (it->is_upper)pai[i] = it->idx;
				else pai[i] = pai[it->idx];
			}
			s.insert(seg);
		}
		else s.erase(seg);
	}
	return pai;
}
