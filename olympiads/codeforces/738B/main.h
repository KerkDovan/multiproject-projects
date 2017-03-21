// Changeable code starts here. 

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <algorithm>
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

#define stringify(str) stringify2(str)
#define stringify2(str) #str

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
#define freopen_in(filename) freopen(filename, "r", stdin)
#define freopen_out(filename) freopen(filename, "w", stdout)
#define close_files

	struct MultiprojectDebug {
		template<class _Ty> friend MultiprojectDebug&
		operator << (MultiprojectDebug& db, const _Ty&) { return db; }
	} debug;

#endif

// Changeable code continues here. 

	using namespace std;

	typedef long long ll;
	typedef unsigned long long ull;

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t h, w;
		while (cin >> h >> w) {
			vector<vector<int>> right(h), down(w), left(h), up(w);
			for (size_t y = 0; y < h; ++y) {
				for (size_t x = 0; x < w; ++x) {
					int actor;
					cin >> actor;
					if (actor) {
						right[y].emplace_back(x);
						left[y].emplace_back(x);
						up[x].emplace_back(y);
						down[x].emplace_back(y);
					}
				}
			}
			for (size_t y = 0; y < h; ++y) {
				right[y].emplace_back(-1);
				sort(right[y].begin(), right[y].end());
				left[y].emplace_back(w);
				sort(left[y].begin(), left[y].end(), greater<int>());
			}
			for (size_t x = 0; x < w; ++x) {
				down[x].emplace_back(-1);
				sort(down[x].begin(), down[x].end());
				up[x].emplace_back(h);
				sort(up[x].begin(), up[x].end(), greater<int>());
			}
			int result = 0;
			// Right direction
			for (size_t y = 0; y < h; ++y) {
				auto cur = right[y].begin(), prev = cur++;
				for (; cur != right[y].end(); prev = cur++) {
					result += *cur - *prev - 1;
				}
			}
			// Left direction
			for (size_t y = 0; y < h; ++y) {
				auto cur = left[y].begin(), prev = cur++;
				for (; cur != left[y].end(); prev = cur++) {
					result += *prev - *cur - 1;
				}
			}
			// Down direction
			for (size_t x = 0; x < w; ++x) {
				auto cur = down[x].begin(), prev = cur++;
				for (; cur != down[x].end(); prev = cur++) {
					result += *cur - *prev - 1;
				}
			}
			// Up direction
			for (size_t x = 0; x < w; ++x) {
				auto cur = up[x].begin(), prev = cur++;
				for (; cur != up[x].end(); prev = cur++) {
					result += *prev - *cur - 1;
				}
			}
			cout << result << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
