/**
 * Author: Arthur Botelho
 * Description: Suffix automaton with parameterized transition table (can be array or map)
 * Time: O(n) build
 * Memory: O(n * |G|)
 * Status: tested at CSES and Codeforces
 */

template<class C, class G> struct Automaton{
	vector<G> dag; 
	vector<int> lnk, len, cnt;
	int last;
	template<class S> Automaton(S& str):
		dag(2),lnk(2,0),len(2,0),cnt(2,0),last(1){
		for(C& c : str)add(c); //can do .reserve(2*n+2)
	}
	int new_node(int l, int is_pref){
		dag.pb(G()); lnk.pb(0); len.pb(l); cnt.pb(is_pref); 
		return sz(dag)-1;
	}
	void add(C& c){
		int cur = new_node(len[last]+1, 1), p = last;
		while(p and not dag[p][c])dag[p][c] = cur, p = lnk[p];
		if (not p)lnk[cur] = 1;
		else {
			int q = dag[p][c];
			if (len[p]+1 == len[q])lnk[cur] = q;
			else{
				int clone = new_node(len[p]+1, 0);
				dag[clone] = dag[q];
				lnk[clone] = lnk[q];
				lnk[q] = lnk[cur] = clone;
				while(p and dag[p][c] == q)dag[p][c]=clone, p=lnk[p];
			}
		}
		last = cur;
	}
};
