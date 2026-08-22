/**
 * Author: Ruan Petrus
 * Date: 2019-10-29
 * License: Unknown
 * Source: https://cp-algorithms.com/geometry/minkowski.html
 * Description: Calculates the Minkowski sum of two convex Polygons in ccw order
 * Time: $O(N+M)$
 * Status: stress-tested, Submitted on https://codeforces.com/gym/106252/problem/G
 */
#pragma once

#include "Point.h"

template<typename P>
vector<P> minkowski(vector<P> p, vector<P> q){
	auto comp = [](auto a, auto b) {
			return make_pair(a.y, a.x) < make_pair(b.y, b.x);
	};
    rotate(p.begin(), min_element(all(p), comp), p.end());
    rotate(q.begin(), min_element(all(q), comp), q.end());
    p.pb(p[0]); p.pb(p[1]);
    q.pb(q[0]); q.pb(q[1]);
    vector<P> result;
    int i = 0, j = 0;
    while(i < sz(p) - 2 || j < sz(q) - 2){
        result.pb(p[i] + q[j]);
        auto cross = (p[i + 1] - p[i]).cross(q[j + 1] - q[j]);
        if(cross >= 0 && i < sz(p) - 2) i++;
        if(cross <= 0 && j < sz(q) - 2) j++;
    }
    return result;
}

