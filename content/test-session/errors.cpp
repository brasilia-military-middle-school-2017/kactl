/**
 * Author: ChatGPT
 * Description: Tests memory/stack limits and common runtime failures.
 * Usage: Change TEST and parameters. TEST: 0=vector allocation,
 * 1=local array, 2=finite recursion, 3=vector push_back,
 * 4=queue push, 5=out of bounds, 6=infinite recursion.
 */

constexpr int TEST = 0;
constexpr size_t HEAP_MB = 1024;
constexpr size_t STACK_MB = 128;
constexpr int REC_DEPTH = 10000;
constexpr size_t FRAME_KB = 1;
constexpr size_t BAD_INDEX = 1000000000ULL;
volatile long long sink;
volatile bool stop_recursion = false;

void touch(volatile unsigned char* a, size_t n) {
	for (size_t i = 0; i < n; i += 4096)a[i] = 1;
	if (n) a[n - 1] = 1;
}

void local_array_test() {
	volatile unsigned char a[STACK_MB * 1024 * 1024];
	touch(a, sizeof(a));
	sink = a[sizeof(a) - 1];
}

__attribute__((noinline))
long long finite_recursion(int depth) {
	volatile unsigned char frame[FRAME_KB * 1024];
	frame[0] = depth;
	frame[sizeof(frame) - 1] = depth;
	if (!depth)return frame[0];
	long long ans = finite_recursion(depth - 1);
	return ans + frame[depth % sizeof(frame)];
}

__attribute__((noinline))
void infinite_recursion(int depth) {
	volatile unsigned char frame[FRAME_KB * 1024];
	frame[0] = depth;
	frame[sizeof(frame) - 1] = depth;
	if (stop_recursion)return;
	infinite_recursion(depth + 1);
	sink += frame[depth % sizeof(frame)];
}

void test() {
	const size_t bytes = HEAP_MB * 1024ULL * 1024;
	const size_t ints = bytes / sizeof(int);

	if (TEST == 0) {
		vector<int> v(ints);
		sink = v.back();
	}
	else if (TEST == 1) local_array_test();
	else if (TEST == 2) sink = finite_recursion(REC_DEPTH);
	else if (TEST == 3) {
		vector<int> v;
		for (size_t i = 0; i < ints; i++) v.push_back(i);
		sink = v.back();
	}
	else if (TEST == 4) {
		queue<int> q;
		for (size_t i = 0; i < ints; i++) q.push(i);
		sink = q.back();
	}
	else if (TEST == 5) {
		int a[10] = {};
		volatile size_t index = BAD_INDEX;
		sink = a[index];
	}
	else if (TEST == 6) infinite_recursion(0);
	cout << sink << '\n';
}