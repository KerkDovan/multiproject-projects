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

	vector<int> colors;
	vector<vector<size_t>> graph;
	vector<bool> visited;

	int getClusterColor(size_t id) {
		int col = colors[id];
		queue<size_t> que;
		que.emplace(id);
		visited[id] = true;
		while (!que.empty()) {
			size_t cur = que.front();
			que.pop();
			for (size_t nxt : graph[cur]) {
				if (visited[nxt] || colors[nxt] != col)
					continue;
				visited[nxt] = true;
				que.emplace(nxt);
			}
		}
		return col;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t cnt;
		while (cin >> cnt) {
			colors.assign(cnt, {});
			graph.assign(cnt, {});
			visited.assign(cnt, false);
			for (size_t i = 0; i < cnt; ++i)
				cin >> colors[i];
			for (size_t i = 0; i < cnt - 1; ++i) {
				size_t id1, id2;
				cin >> id1 >> id2;
				graph[id1 - 1].emplace_back(id2 - 1);
				graph[id2 - 1].emplace_back(id1 - 1);
			}
			size_t cols[2] = { 0, 0 };
			for (size_t i = 0; i < cnt; ++i)
				if (!visited[i])
					++cols[getClusterColor(i)];
			cout << min(cols[0], cols[1]) << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
