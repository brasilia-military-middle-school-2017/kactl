/**
 * Author: duduFreire/kctl
 * Date: 2026-02-23
 * Source: folklore
 * Description: Lazy treap. Its Spec is the same as LazySpec, except that update has the signature
 * update(K f, int n, S a), where n represents the range size.
 * Time: $O(\log N)$
 * Status: tested on Range Updates and Sums (CSES)
 */
#pragma once

#define TT template<typename S>
#define NN node<S>*
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
TT struct node {
	node *l=0, *r=0;	
	int y, c=1;
	typename S::S val, acc;
	typename S::K lz;
	bool hlz=0;
	node(typename S::S aval) :  y(uniform_int_distribution<int>(0,(int)1e9)(rng)), val(aval), acc(aval) {}
	void rc();
};
TT int cnt(S n) {return n ? n-> c : 0;}
TT void prop(NN t) {
	if (!t or !t->hlz) return;	
	t->hlz=0;
	t->val = S::update(t->lz, 1, t->val);
	t->acc = S::update(t->lz, t->c, t->acc);
	if (t->l) t->l->lz = t->l->hlz ? S::compose(t->l->lz, t->lz) : t->lz, t->l->hlz=1;
	if (t->r) t->r->lz = t->r->hlz ? S::compose(t->r->lz, t->lz) : t->lz, t->r->hlz=1;
}
TT void node<S>::rc() {
	c = cnt(l) + cnt(r) + 1;
	prop(l); prop(r);
	acc = S::op(S::op(l ? l->acc : S::id(), val), r ? r->acc : S::id());
}
TT pair<NN,NN> split(NN t, int k) {
	if (k == 0) return {0, t};
	if (cnt(t->l) >= k) {
		prop(t->l);
		auto [l, r] = split(t->l, k);
		t->l = r;
		t->rc();
		return {l, t};
	}
	prop(t->r);
	auto [l,r] = split(t->r, k - cnt(t->l) - 1);
	t->r = l;
	t->rc();
	return {t, r};
}
TT auto merge(NN l, NN r) {
	if (!l) return r;
	if (!r) return l;
	if (l->y < r->y) return prop(l->r), l->r = merge(l->r, r), l->rc(), l;
	return prop(r->l), r->l = merge(l, r->l), r->rc(), r;
}
