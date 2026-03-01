/**
 * Author: Ruan Petrus
 * Date: 2019-10-29
 * License: Unknown
 * Source: https://cp-algorithms.com/geometry/halfplane-intersection.html
 * Description: Calculates the halfplane intersection of Halfplanes, Halfplanes allow everything to the left. 
 * Cuidado com a precisao
 * Time: $O(N \log(N)$
 * Status: stress-tested, Submitted on https://codeforces.com/gym/104736/problem/H
 */
#pragma once

#include "Point.h"

const ld EPS = 1e-9, INF = 1e9;
typedef Point<ld> P;
struct HP {
    P p, pq;
	ld angle;
    HP() {}
    HP(P a, P b) : p(a), pq(b - a), angle(atan2(pq.y, pq.x)) {}

    bool out(const P & r) { return pq.cross(r - p) < -EPS; }
    bool operator<(const HP & e) const { return angle < e.angle; }
    friend P inter(const HP & s, const HP & t) {
        ld alpha = (t.p - s.p).cross(t.pq) / s.pq.cross(t.pq);
        return s.p + (s.pq * alpha);
    }
};
vector<P> hp_intersect(vector<HP> &H) {
    P box[4] = {
        P(INF, INF),
        P(-INF, INF),
        P(-INF, -INF),
        P(INF, -INF)
    };
    for(int i = 0; i < 4; i++) H.eb(box[i], box[(i+1) % 4]);
    sort(H.begin(), H.end());
    deque<HP> dq;
    int len = 0;
    rep(i, 0, sz(H)) {
        while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2])))
            dq.pop_back(), len--;
        while (len > 1 && H[i].out(inter(dq[0], dq[1])))
            dq.pop_front(), len--;
		// Special case check: Parallel half planes
        if (len > 0 && fabsl(H[i].pq.cross(dq[len-1].pq)) < EPS) {
            if (H[i].pq.dot(dq[len-1].pq) < 0.0) return {};
            if (H[i].out(dq[len-1].p))
                dq.pop_back(), len--;
            else continue;
        }
        dq.push_back(H[i]); len++;
    }
    while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2])))
        dq.pop_back(), len--;
    while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) 
		dq.pop_front(), len--;
    if (len < 3) return {};
    vector<P> ret(len);
	rep(i, 0, len-1) ret[i] = inter(dq[i], dq[i+1]);
    ret.back() = inter(dq[len-1], dq[0]);
    return ret;
}
