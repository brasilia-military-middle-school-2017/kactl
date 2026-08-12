"""
* Author: Notebook team
* Description: Generates a large C++ file to test submission source-size limits.
* Usage: python3 SourceLimitGen.py 100000 > big.cpp
"""

import sys

N = int(sys.argv[1]) if len(sys.argv) > 1 else 100000

size = 0

def emit(s):
    global size
    sys.stdout.write(s)
    size += len(s.encode())

emit("#include <bits/stdc++.h>\n")
emit("using namespace std;\n")
emit(f"long long a[{N}];\n")
emit("int main() {\n")
for i in range(N): emit(f"a[{i}] = {i};\n")
emit(f"cout << a[{N - 1}] << '\\n';\n")
emit("}\n")

print(f"generated {size} bytes ({size / 1024:.1f} KiB)", file=sys.stderr)