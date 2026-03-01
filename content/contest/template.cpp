#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define eb emplace_back
#define debug(x...) cout<<"["#x"]: ",[](auto...$){((cout<<$<<"; "),...);}(x),cout<<endl
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
template<class T> auto& operator<<(ostream& o, vector<T> v){
rep(i,0,sz(v)){o << v[i]; if (i<sz(v)-1)o << " ";} return o;}

constexpr int oo = (((unsigned int)-1) >> 1);

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
}
