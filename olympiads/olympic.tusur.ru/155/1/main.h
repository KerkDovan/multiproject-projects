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

	struct Vertex {
		Vertex() {}
		Vertex(size_t to, double mult) : to(to), mult(mult) {}
		size_t to;
		double mult;
	};

	vector<vector<Vertex>> graph;
	vector<int> color;
	vector<bool> answer;

	bool dfs(size_t id, double weight) {
		bool result = false;
		for (const Vertex& v : graph[id]) {
			switch (color[v.to]) {
			case 2:
				if (weight * v.mult > 1.0) {
					answer[id] = answer[v.to] = true;
					return true;
				}
				else
					return false;
			case 1:
				return false;
			}
			color[v.to] = 1;
			if (dfs(v.to, weight * v.mult))
				result = answer[id] = true;
			color[v.to] = 0;
			if (result)
				return true;
		}
		return false;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t n, m;
		while (cin >> n >> m) {
			graph.assign(n, {});
			for (size_t i = 0; i < m; ++i) {
				size_t a, b;
				string c;
				double d;
				cin >> a >> b >> c >> d;
				graph[a - 1].emplace_back(b - 1, c == "mult" ? d : 1.0 / d);
			}
			color.assign(n, 0);
			answer.assign(n, 0);

			for (size_t i = 0; i < n; ++i) {
				if (answer[i])
					continue;
				color[i] = 2;
				dfs(i, 1.0);
				color[i] = 0;
			}

			size_t cnt = 0;
			for (bool b : answer)
				cnt += (size_t)b;
			cout << cnt << '\n';

			bool printed = false;
			for (size_t i = 0; i < n; ++i) {
				if (answer[i]) {
					if (printed)
						cout << ' ';
					cout << i + 1;
					printed = true;
				}
			}
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
