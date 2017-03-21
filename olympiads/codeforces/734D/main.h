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

	enum Directions {
		t = 0, rt, r, rb, b, lb, l, lt
	};

	char figures[8] = {
		'R', 'B', 'R', 'B', 'R', 'B', 'R', 'B',
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t cnt;
		while (cin >> cnt) {
			int x, y;
			cin >> x >> y;
			map<size_t, char> coords[8];
			for (size_t i = 0; i < cnt; ++i) {
				char f;
				int tx, ty;
				cin >> f >> tx >> ty;
				int dx = tx - x, dy = ty - y;
				if (dx == 0) { // by vert
					if (dy < 0) { // top
						coords[t].emplace(-dy, f);
					}
					else { // bottom
						coords[b].emplace(dy, f);
					}
				}
				else if (dy == 0) { // by horz
					if (dx < 0) { // left
						coords[l].emplace(-dx, f);
					}
					else { // right
						coords[r].emplace(dx, f);
					}
				}
				else if (abs(dx) == abs(dy)) { // by diag;
					if (dx < 0 && dy < 0) { // left top
						coords[lt].emplace(-dx, f);
					}
					else if (dx < 0 && dy > 0) { // left bottom
						coords[lb].emplace(dy, f);
					}
					else if (dx > 0 && dy < 0) { // right top
						coords[rt].emplace(dx, f);
					}
					else { // right bottom
						coords[rb].emplace(dx, f);
					}
				}
			}
			bool check = false;
			for (int i = 0; i < 8; ++i) {
				if (coords[i].empty())
					continue;
				char f = coords[i].begin()->second;
				check |= f == 'Q' || f == figures[i];
			}
			cout << (check ? "YES\n" : "NO\n");
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
