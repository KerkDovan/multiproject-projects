// Changeable code starts here. 

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string.h>
#include <tuple>
#include <vector>

#define stringify(...) stringify2(__VA_ARGS__)
#define stringify2(...) #__VA_ARGS__

// Changeable code stops here. 
	
#ifdef _LOCAL_MULTIPROJECT_

#include "multiproject.h"

namespace project {

	using namespace project::tools;
	using namespace project::tools::debugging;
	using namespace project::tools::debugging::format;

#else

#include <iostream>

#define breakpoint
#define breakpoint_if(...)
#define breakpoint_counters
#define breakpoint_counter(...)
#define breakpoint_counter_init(...)
#define breakpoint_counter_offset(...)
#define breakpoint_when(...)
#define breakpoint_when_offset(...)
#define breakpoint_counters_clear
#define only_multiproject(...)
#define debug_output(...)
#ifdef _MULTIPROJECT_PROJECT_CONFIG_H_
#define freopen_in(filename) freopen("project\\" ## filename, "r", stdin)
#define freopen_out(filename) freopen("project\\" ## filename, "w", stdout)
#else
#define freopen_in(filename) freopen(filename, "r", stdin)
#define freopen_out(filename) freopen(filename, "w", stdout)
#endif
#define close_files

	struct MultiprojectDebug {
		template<class _Ty> friend MultiprojectDebug&
		operator << (MultiprojectDebug& db, const _Ty&) { return db; }
	} debug;

#endif

// Changeable code continues here. 

	using namespace std;
#ifdef MYLIB
	using namespace MyLib;
#endif // MYLIB

	typedef long long ll;
	typedef unsigned long long ull;

	const size_t MAX_BITS_COUNT = 1500;

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		// Generating sequence
		vector<bool> seq = { 0, 1, 1, 0, 1, };
		for (size_t i = 0; i < MAX_BITS_COUNT; ++i) {
			for (size_t a = i - 2, b = i - 1; a + 2 > 1; a -= 2, b -= 1) {
				if (seq[a] == seq[b]) {
					bool to_change = true;
					for (size_t c = a + 1, d = b + 1; d < i; ++c, ++d) {
						if (seq[c] != seq[d]) {
							to_change = false;
							break;
						}
					}
					if (to_change) {
						seq.emplace_back(!seq[a]);
						break;
					}
				}
			}
			if (seq.size() == i)
				seq.emplace_back(0);
		}

		// Debugging checker
		//seq.clear();
		//seq = { 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, };
		//while (seq.size() < MAX_BITS_COUNT)
		//	seq.emplace_back(0);

		// Output for debug
		debug << "Count: " << seq.size() << '\n';
		for (bool b : seq)
			debug << b;
		debug << "\n\n";

		// Local checker
		// It's just dump brute, so it may TL in Debug. Use Release or comment this loop.
		for (size_t i = 0; i < MAX_BITS_COUNT; ++i) {
			for (size_t j = 1; i + j * 3 < MAX_BITS_COUNT; ++j) {
				size_t cnt = 0;
				for (size_t k = 0; k < j; ++k) {
					if (seq[i + k] != seq[i + j + k] || seq[i + k] != seq[i + 2 * j + k])
						break;
					++cnt;
				}
				if (cnt == j)
					debug << i << ' ' << j << '\n';
			}
		}

		// Outputting answer to the problem
		size_t n;
		while (cin >> n) {
			for (size_t i = 0; i < n; ++i)
				cout << (int)seq[i];
			cout << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
