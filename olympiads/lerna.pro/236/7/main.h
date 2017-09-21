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

	vector<vector<pair<size_t, ull>>> vertices;

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t n, m, u, v;
		while (cin >> n >> m >> u >> v) {
			vertices.assign(n, vector<pair<size_t, ull>>());
			for (size_t i = 0; i < m; ++i) {
				size_t a, b;
				ull c;
				cin >> a >> b >> c;
				vertices[a - 1].emplace_back(b - 1, c);
				vertices[b - 1].emplace_back(a - c, c);
			}

			vector<bool> visited(n, false);
			map<ull, size_t> spent; // <cost till here, id of here>
			size_t cur = u;
			ull cost;
			spent.emplace(cur, 0);
			for (size_t i = 0; i < n; ++i) {
				if (cur == i)
					continue;
				spent.emplace(i, 1000 * 1000 * 1000 * 1000 * 1000 * 1000);
			}

			// code below is incorrect
			while (cur != v) {
				cur = spent.begin()->second;
				cost = spent.begin()->first;
				for (auto nxt : vertices[cur]) {
					if (spent[nxt.first] > cost + nxt.second) {
						spent[nxt.first] = cost + nxt.second;

					}
				}
			}

		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
