/**
 * Author: ChatGPT
 * Description: Benchmarks common C++ operations during the warm-up session.
 * Usage: Change TEST and the parameters below. TEST: 0=integer,
 * 1=double, 2=sequential array, 3=dependent array, 4=recursion.
 */

constexpr int TEST = 0;

constexpr long long N = 100000000;
constexpr int ARRAY_LOG = 20;
constexpr int REC_DEPTH = 100;
constexpr int REC_RUNS = 100000;

using ull = unsigned long long;

__attribute__((noinline))
ull recurse(int depth, ull x) {
	volatile ull y = x + depth;
	if (!depth) return y;
	ull ans = recurse(depth - 1, y);
	return ans + (y & 1);
}

volatile ull sink_int;
volatile double sink_double;

void test() {
	const size_t A = 1ULL << ARRAY_LOG;
	const size_t MASK = A - 1;

	vector<ull> a;

	if (TEST == 2) {
		a.resize(A);
		iota(a.begin(), a.end(), 1);
	}
	if (TEST == 3) {
		a.resize(A);
		for (size_t i = 0; i < A; i++) a[i] = (5 * i + 1) & MASK;
	}

	auto start = chrono::steady_clock::now();

	if (TEST == 0) {
		ull x = 123456789;
		for (long long i = 0; i < N; i++) {
			x ^= x << 7;
			x ^= x >> 9;
			x += i;
		}
		sink_int = x;
	}
	else if (TEST == 1) {
		double x = 1.000001;
		for (long long i = 0; i < N; i++) x = x * 1.0000001 + 0.0000001;
		sink_double = x;
	}
	else if (TEST == 2) {
		ull x = 0;
		for (long long i = 0; i < N; i++)x += a[i & MASK];
		sink_int = x;
	}
	else if (TEST == 3) {
		ull x = 0;
		size_t pos = 0;
		for (long long i = 0; i < N; i++) {
			pos = a[pos];
			x += pos;
		}
		sink_int = x;
	}
	else if (TEST == 4) {
		ull x = 0;
		for (int i = 0; i < REC_RUNS; i++)x += recurse(REC_DEPTH, i);
		sink_int = x;
	}

	auto end = chrono::steady_clock::now();
	double sec = chrono::duration<double>(end - start).count();
	long long ops = TEST == 4 ? 1LL * REC_RUNS * (REC_DEPTH + 1): N;
	cerr << fixed << setprecision(3);
	cerr << sec << " s, " << sec * 1e9 / ops << " ns/op\n";
	if (TEST == 1) cout << sink_double << '\n';
	else cout << sink_int << '\n';
}