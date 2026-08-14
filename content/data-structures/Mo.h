/**
 * Author: Simon Lindholm and Arthur Botelho
 * Description: Answer interval or tree path queries. Includes interval version without deletion.
 * If values are on tree edges, change \texttt{step} to add/remove the edge $(a, c)$ and remove the initial \texttt{add} call (but keep \texttt{in}).
 * Time: O(N \sqrt Q)
 * Status: stress-tested
 */
#pragma once

void add(int i, int end) { i+=end; }
void del(int i, int end) { i-=end; }
int calc() { return 0; }

vi mo(vector<pii> Q) {
	int L = 0, R = -1, blk = 450; // ~N/sqrt(Q)
	vi s(sz(Q)), res = s;
#define K(x) pii(x.first/blk, x.second ^ -(x.first/blk & 1))
	iota(all(s), 0);
	sort(all(s), [&](int i, int j){ return K(Q[i]) < K(Q[j]); });
	for (int qi : s) {
		auto [l, r] = Q[qi];
		while (L > l) add(--L, 0);
		while (R < r) add(++R, 1);
		while (L < l) del(L++, 0);
		while (R > r) del(R--, 1);
		res[qi] = calc();
	}
	return res;
}

vi moTree(vector<array<int, 2>> Q, vector<vi>& ed, int root=0){
	int N = sz(ed), pos[2] = {}, blk = 350; // ~N/sqrt(Q)
	vi s(sz(Q)), res = s, I(N), L(N), R(N), in(N), par(N);
	add(0, 0), in[0] = 1;
	auto dfs = [&](int x, int p, int dep, auto& f) -> void {
		par[x] = p;
		L[x] = N;
		if (dep) I[x] = N++;
		for (int y : ed[x]) if (y != p) f(y, x, !dep, f);
		if (!dep) I[x] = N++;
		R[x] = N;
	};
	dfs(root, -1, 0, dfs);
#define K(x) pii(I[x[0]] / blk, I[x[1]] ^ -(I[x[0]] / blk & 1))
	iota(all(s), 0);
	sort(all(s), [&](int a, int b){ return K(Q[a]) < K(Q[b]); });
	for (int qi : s) rep(end,0,2) {
		int &a = pos[end], b = Q[qi][end], i = 0;
#define step(c) { if (in[c]) { del(a, end); in[a] = 0; } \
                  else { add(c, end); in[c] = 1; } a = c; }
		while (!(L[b] <= L[a] && R[a] <= R[b]))
			I[i++] = b, b = par[b];
		while (a != b) step(par[a]);
		while (i--) step(I[i]);
		if (end) res[qi] = calc();
	}
	return res;
}

vector<int> mo_no_deletion(vector<pii>& qs, int n){
	int q = sz(qs), sq = (int)sqrt(q)+1, blk = (n+sq+1)/sq;
	vector<vi> o((n+blk-1)/blk);
	rep(i,0,q)o[qs[i].first/blk].pb(i);
	for(auto& vq : o)sort(all(vq), [&](int i, int j){return qs[i].second < qs[j].second;});
	vector<int> ans(q);
	rep(i,0,sz(o)){
		auto& vq = o[i];
		int l = blk*i + blk, r = l-1;
		// prepare to answer queries
		for(int qi : vq){
			auto [ql, qr] = qs[qi];
			if (qr <= l){ //if it does not extrapolate
				rep(j,ql,qr+1)add(j, 1); //solving manually
				continue;
			}
			while(r < qr)add(++r, 1);
			int ml = l; //we will move l manually
			// prepare checkpoint
			while(ml > ql)add(--ml, 0);
			ans[qi] = calc();
			// revert checkpoint: discard changes made by moving l
		}
	}
	return ans;
}
