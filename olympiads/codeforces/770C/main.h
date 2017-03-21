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

	enum Colors { clWhite = 0, clGray, clBlack };

	vector<vector<size_t>> from, to;
	vector<size_t> primaries;
	vector<bool> needed;
	vector<char> color;
	stack<size_t> order;

	void dfs1(size_t id) {
		needed[id] = true;
		for (size_t next : to[id])
			if (!needed[next])
				dfs1(next);
	}

	bool dfs2(size_t id) {
		if (color[id] == clGray)
			return false;
		if (color[id] == clBlack)
			return true;
		color[id] = clGray;
		bool possible = true;
		for (size_t next : from[id]) {
			possible &= dfs2(next);
			if (!possible)
				return false;
		}
		color[id] = clBlack;
		order.push(id);
		return possible;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t n, k;
		while (cin >> n >> k) {

			from.assign(n + 1, {});
			to.assign(n + 1, {});
			primaries.assign(k, 0);
			needed.assign(n + 1, false);
			color.assign(n + 1, clWhite);
			while (!order.empty())
				order.pop();

			for (size_t& tmp : primaries)
				cin >> tmp;

			for (size_t i = 1; i <= n; ++i) {
				size_t cnt, tmp;
				cin >> cnt;
				for (size_t j = 0; j < cnt; ++j) {
					cin >> tmp;
					from[tmp].emplace_back(i);
					to[i].emplace_back(tmp);
				}
			}

			breakpoint_when_offset(kek, 3, 1);

			for (size_t tmp : primaries)
				dfs1(tmp);
			size_t needed_count = 0;
			for (bool b : needed)
				needed_count += (size_t)b;

			bool possible = true;
			for (size_t i = 1; i <= n && possible; ++i) {
				if (color[i] == clWhite)
					possible &= dfs2(i);
			}

			if (!possible) {
				cout << "-1\n";
				continue;
			}

			cout << needed_count << '\n';
			bool space = false;
			while (!order.empty()) {
				if (!needed[order.top()]) {
					order.pop();
					continue;
				}
				if (space)
					cout << ' ';
				space = true;
				cout << order.top();
				order.pop();
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
