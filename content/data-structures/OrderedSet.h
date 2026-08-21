/**
 * Author: Arthur Botelho
 * Description: ordered/indexed set and multiset. Bad constant factor, works only in Linux.
 * All erase/find/search functions assume the target exists.
 * Time: O(\log N) operations
 * Memory: O(N)
 * Status: stress-tested
*/

#include<bits/extc++.h> //include it before any defines
using namespace __gnu_pbds;
template<class T, class B = null_type> using ordered_set = tree<T, B, less<T>, rb_tree_tag,  tree_order_statistics_node_update>;

template<class T>
struct ordered_multiset{
	ordered_set<pair<T, int>> o; int c;
	ordered_multiset():c(0){}
	unsigned order_of_key(T x){return o.order_of_key({x, -1});}
	const T* find_by_order(int p){return &(*o.find_by_order(p)).first;}
	void insert(T x){o.insert({x, c++});}
	void erase(T x){o.erase(o.lower_bound({x, 0}));}
	unsigned size(){return o.size();}
	const T* lower_bound(T x){return &(*o.lower_bound({x, 0})).first;}
	const T* upper_bound(T x){return &(*o.upper_bound({x, c})).first;}
};