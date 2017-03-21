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

	typedef long long ll;
	typedef unsigned long long ull;

	size_t cnt, pairs;
	vector<vector<size_t>> friends;
	vector<bool> visited;
	vector<bool> marked;

	bool bfs(size_t id) {
		size_t result = 0;
		size_t comp_size = 0;
		queue<size_t> que;
		que.push(id);
		while (!que.empty()) {
			size_t cur = que.front();
			que.pop();
			visited[cur] = true;
			++comp_size;
			for (size_t nxt : friends[cur]) {
				if (!visited[nxt]) {
					if (!marked[nxt])
						que.push(nxt);
					marked[nxt] = true;
					++result;
				}
			}
		}
		return 2 * result == (comp_size - 1) * comp_size;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> cnt >> pairs) {

			friends.assign(cnt, vector<size_t>());
			visited.assign(cnt, false);
			marked.assign(cnt, false);

			for (size_t i = 0; i < pairs; ++i) {
				size_t a, b;
				cin >> a >> b;
				--a, --b;
				friends[a].push_back(b);
				friends[b].push_back(a);
			}

			bool nice = true;
			for (size_t i = 0; i < cnt; ++i) {
				if (visited[i])
					continue;
				if (!bfs(i)) {
					nice = false;
					break;
				}
			}

			cout << (nice ? "YES" : "NO") << '\n';

		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
