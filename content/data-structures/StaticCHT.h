/**
 * Author: Bruno Monteiro
 * Description: static CHT - add must be ordered by slope (a), queries by x.
 * Time: amortized $O(1)$.
 * Status: tested at CSES
 */
#pragma once

struct CHT {
	int it; vector<ll> a, b;
	CHT():it(0){}
	ll eval(int i, ll x){return a[i]*x + b[i];}
	bool useless(){
		int sz = a.size();
		int r = sz-1, m = sz-2, l = sz-3;
#warning careful with overflow!
		return (b[l] - b[r])*(a[m] - a[l]) <=
			(b[l] - b[m])*(a[r] - a[l]);
	}
	void add(ll A, ll B){
		if(sz(a) && A==a.back()){
		    if(B<=b.back())return;
    		a.pop_back(); b.pop_back();
		}
		a.push_back(A); b.push_back(B);
		while (!a.empty()){
			if ((a.size() < 3) || !useless()) break;
			a.erase(a.end() - 2);
			b.erase(b.end() - 2);
		}
		it = min(it, int(a.size()) - 1);
	}
	ll query(ll x){
		if (sz(a) == 0)return -oo;
		while (it+1 < a.size()){
			if (eval(it+1, x) >= eval(it, x)) it++;
			else break;
		}
		return eval(it, x);
	}
};