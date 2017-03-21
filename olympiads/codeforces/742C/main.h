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

	int cnt;
	vector<int> nxt;
	vector<vector<int>> lens;

	int len(int from, int to) {
		int l = 1;
		int prev = from;
		for (int i = nxt[from]; i != to; prev = i, i = nxt[i], ++l)
			if (i == from || i == prev)
				return -1;
		return l;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> cnt) {
			nxt.assign(cnt, 0);
			lens.assign(cnt, vector<int>(cnt));
			for (int& i : nxt) {
				cin >> i;
				--i;
			}
			for (int i = 0; i < cnt; ++i)
				for (int j = 0; j < cnt; ++j)
					lens[i][j] = len(i, j);
			set<int> psbl;
			for (int i = 0; i < cnt; ++i)
				for (int j = 0; j < cnt; ++j)
					if (lens[i][j] == lens[j][i] && ~lens[i][j])
						psbl.emplace(lens[i][j]);
			int t = -1;
			for (int p : psbl) {
				for (int i = 0; i < cnt; ++i) {
					for (int j = 0; j < cnt; ++j) {
						if (p % lens[i][j] != 0) {
							t = -1;
							break;
						}
						t = p;
					}
				}
				if (~t)
					break;
			}
			cout << t << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
