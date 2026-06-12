/**
 * Author: ??
 * Date: 2026-03-02
 * Description: n / i has the same value for l <= i <= r
 * Time: $\sqrt{n}$
 * Status: Works
 */
#pragma once

void dt(int n){for(int l=1,r;l<=n;l=r+1) r = n / (n / l);}
