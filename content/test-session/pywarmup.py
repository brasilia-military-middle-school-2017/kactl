"""
* Author: Notebook team
* Description: Benchmarks common Python operations during the warm-up session.
* Usage: Change TEST and the parameters below. TEST: 0=integer,
* 1=float, 2=sequential list, 3=dependent list, 4=recursion.
"""
import sys, time

TEST = 0
N = 10_000_000
ARRAY_LOG = 18
REC_DEPTH = 100
REC_RUNS = 10_000

def recurse(depth, x):
    y = x + depth
    if depth == 0: return y
    ans = recurse(depth - 1, y)
    return ans + (y & 1)

A = 1 << ARRAY_LOG
MASK = A - 1
a = None
if TEST == 2:
    a = list(range(A))
elif TEST == 3:
    a = [(5 * i + 1) & MASK for i in range(A)]
elif TEST == 4:
    sys.setrecursionlimit(max(1000, REC_DEPTH + 100))

start = time.perf_counter()

x = 0
if TEST == 0:
    x = 123456789
    for i in range(N):
        x ^= x << 7
        x ^= x >> 9
        x += i
        x &= 0xffffffffffffffff
elif TEST == 1:
    x = 1.000001
    for _ in range(N):
        x = x * 1.0000001 + 0.0000001
elif TEST == 2:
    for i in range(N): x += a[i & MASK]
elif TEST == 3:
    pos = 0
    for _ in range(N):
        pos = a[pos]
        x += pos
elif TEST == 4:
    for i in range(REC_RUNS): x += recurse(REC_DEPTH, i)

elapsed = time.perf_counter() - start
ops = REC_RUNS * (REC_DEPTH + 1) if TEST == 4 else N
print(x)
print(
    f"{elapsed:.3f} s, "
    f"{elapsed * 1e9 / ops:.1f} ns/op",
    file=sys.stderr,
)