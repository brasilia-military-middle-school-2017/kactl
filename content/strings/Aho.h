/**
 * Author: Arthur Botelho
 * Description: Aho-Corasick. G is the graph type (usually array<int, 26> or map<char, int>)
 *  and C is the graph index type. nb is the vertex of the next existing suffix in the trie,
 *  and rnb is the next suffix that is an input string. Remember that rnb tree has depth sqrt.
 *  term marks if is input string. add function retuns the index of vertex for that string, the
 *  mapping between vertices and string, including repetitions, is done by the user, not the API.
 *  0 is the initial state and also the link tree root.
 * Time: O(N * 26) build, where N is the sum of sizes of strings
 * Memory: O(N * |G|))
 * Status: not yet tested
 */

template<class C, class G> struct Aho {
    vector<G> trie, aut;
    vector<int> nb, rnb;
    vector<bool> term; //reserve 1 + sum of |s|
    Aho(): trie(1), aut(1), nb(1), rnb(1), term(1) {}
    int new_node(){
		trie.eb(); aut.eb(); nb.eb(); rnb.eb(); term.eb();
        return sz(trie)-1;
    }
    template<class S> int add(S& str){
        int v = 0;
        for(C c : str)
            if (trie[v][c])v = trie[v][c];
            else v = trie[v][c] = new_node();
        return term[v] = 1, v;
    }
    void build(){
        queue<int> bfs; bfs.push(0);
        while(not bfs.empty()){
            int v = bfs.front(), u = nb[v]; 
            rnb[v] = term[u] ? u : rnb[u]; bfs.pop();
            for(C c = 0; c < 26; c++){ // iterate trie edges
                int f = trie[v][c], uf = aut[u][c];
                if (f)aut[v][c] = f, nb[f] = uf, bfs.push(f);
                else aut[v][c] = uf;
            }
        }
    }
};
