/**
 * Author: Arthur Botelho
 * Description: Multidimensional Psum
 * Requires Abelian Group (op, inv, id)
 * Time: O(2^D)
 * Memory: O(N^D)
 * Status: stress-tested
 */
#pragma once

#define MAs template<class... As>
template<int D, class S> struct MPsum{ 
	using T = typename S::T;
	int n; vector<Psum<D-1, S>> v;
	MAs MPsum(int s, As... ds):n(s+1),v(n,Psum<D-1, S>(ds...)){}
	MAs void set(T x, int p, As... ps){v[p+1].set(x, ps...);}
	void push(Psum& p){rep(i, 1, n)v[i].push(p.v[i]);}
	void init(){rep(i, 1, n)v[i].init(),v[i].push(v[i-1]);}
	MAs T query(int l, int r, As... ps){
		return S::op(v[r+1].query(ps...),S::inv(v[l].query(ps...)));
	}
};
template<class S> struct MPsum<0, S>{ 
	using T = typename S::T;
	T val=S::id;
	void set(T x){val=x;}
	void push(MPsum& a){val=S::op(a.val,val);}
	void init(){}
	T query(){return val;}
};
