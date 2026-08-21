/**
 * Author: Arthur Botelho
 * Description: KMP automaton
 * Time: O(N) build, O(N+M) sequential querying
 * Memory: O(N)
 * Status: tested
*/

struct KMP {
	string P; int n; vector<int> nb;
	KMP(string& p) : P(p), n((int)P.size()), nb(n+1) {
		for(int k = 1; k < n; k++) nb[k+1] = nxt(nb[k], P[k]);
	}
	int nxt(int i, char c){
		for(; i; i = nb[i])if (i < n and P[i]==c)return i+1;
		return P[0]==c;
	}
	vector<vector<int>> dfa;
    void build_dfa(){ // uses a-z
		dfa.assign(n+1, vector<int>(26));
        dfa[0][P[0]-'a'] = 1; 
        for(int k = 1; k <= n; k++)
            for(int c = 0; c < 26; c++)
                if (k < n and P[k] == 'a'+c) dfa[k][c] = k+1;
                else dfa[k][c] = dfa[nb[k]][c];
    }
};