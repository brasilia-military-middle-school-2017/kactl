/**
 * Author: Arthur Botelho and ChatGPT
 * Description: Small-to-large. While out(v) is called,
 * the maintained state contains exactly the subtree of v.
 * add(v) inserts v and del(v) undoes it. Root is configurable.
 * Time: O(N log N * (add + del) + N * (out)).
 * Memory: O(N).
 * Status: randomized against brute force
 */
#pragma once

template<class A,class D,class Q>
void smallToLarge(const vector<vi>& g, A add, D del, Q out, int r){
	int n=sz(g);
	vi sub(n, 1), pos(n, -1), pre, st={r};
	pre.reserve(n); st.reserve(n); pos[r]=r; // pos starts as parent vector
	while(sz(st)){
		int v = st.back(); st.pop_back(); pre.pb(v);
		for(int f : g[v])if (f != pos[v])pos[f] = v, st.pb(f);
	}
	for(int i = n; i-->1; sub[pos[pre[i]]] += sub[pre[i]]);
	rep(i,0,n)pos[pre[i]] = i;
	auto heavy = [&](int v){
		int b = -1;
		for(int f : g[v])if (pos[f] > pos[v] && (b < 0 || sub[f] > sub[b]))b=f;
		return b;
	};
	st.clear(); st.pb(2*r+1); // 2*v + keep, ~ if out
	while(sz(st)){
		int z = st.back(); st.pop_back();
		if(z >= 0){
			int v = z/2, b = heavy(v); st.pb(~z);
			if(b >= 0)st.pb(2*b+1);
			for(int f : g[v])if (pos[f] > pos[v] && f != b)st.pb(2*f);
		}
		else{
			z=~z; int v=z/2, keep = z%2, b = heavy(v); 
			add(v);
			for(int f : g[v])if (pos[f] > pos[v] && f != b)
				rep(i,pos[f],pos[f]+sub[f])add(pre[i]);
			out(v);
			if(!keep)rep(i,pos[v],pos[v]+sub[v])del(pre[i]);
		}
	}
}
