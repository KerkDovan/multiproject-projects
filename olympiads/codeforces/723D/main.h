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

	const int di[] = { -1, 0, 1, 0 };
	const int dj[] = { 0, 1, 0, -1 };

	size_t n, m;
	vector<string> world;
	vector<vector<bool>> visited;

	size_t determine_lake(size_t y, size_t x) {
		size_t result = 0;
		bool is_ocean = false;
		queue<pair<size_t, size_t>> que;
		que.emplace(y, x);
		while (!que.empty()) {
			size_t i, j;
			tie(i, j) = que.front();
			++result;
			visited[i][j] = true;
			que.pop();
			if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
				is_ocean = true;
			for (int t = 0; t < 4; ++t) {
				size_t ti = i + di[t], tj = j + dj[t];
				if (ti >= 0 && ti < n && tj >= 0 && tj < m) {
					if (!visited[ti][tj])
						que.emplace(ti, tj);
				}
			}
		}
		return is_ocean ? 0 : result;
	}

	void remove_lake(size_t y, size_t x) {
		queue<pair<size_t, size_t>> que;
		que.emplace(y, x);
		while (!que.empty()) {
			size_t i, j;
			tie(i, j) = que.front();
			world[i][j] = '*';
			que.pop();
			for (int t = 0; t < 4; ++t) {
				size_t ti = i + di[t], tj = j + dj[t];
				if (ti >= 0 && ti < n && tj >= 0 && tj < m) {
					if (world[ti][tj] == '.')
						que.emplace(ti, tj);
				}
			}
		}
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t k;
		while (cin >> n >> m >> k >> ws) {
			world.assign(n, "");
			for (string& line : world)
				getline(cin, line);
			multimap<size_t, pair<size_t, size_t>> lakes;
			visited.assign(n, vector<bool>(m, false));
			for (size_t i = 0; i < n; ++i) {
				for (size_t j = 0; j < m; ++j)
					if (world[i][j] == '*')
						visited[i][j] = true;
			}
			size_t cnt = 0;
			for (size_t i = 0; i < n; ++i) {
				for (size_t j = 0; j < m; ++j) {
					if (!visited[i][j]) {
						size_t sz = determine_lake(i, j);
						if (sz) {
							lakes.emplace(sz, make_pair(i, j));
							++cnt;
						}
					}
				}
			}
			size_t to_remove = 0;
			while (cnt != k) {
				auto iter = lakes.begin();
				to_remove += iter->first;
				remove_lake(iter->second.first, iter->second.second);
				lakes.erase(iter);
				--cnt;
			}
			cout << to_remove << '\n';
			for (const string& line : world)
				cout << line << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif