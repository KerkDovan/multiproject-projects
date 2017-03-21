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

	const size_t SIDE = 51;
	const size_t SIZE = SIDE * SIDE;

	typedef bitset<SIZE> Field;

	Field soldiers, walls, destinations;
	set<pair<int, int>> visited;
	size_t w, h;

	inline Field moveBy(Field fld, int dx, int dy) {
		dy < 0 ? fld <<= -dy * SIDE : fld >>= dy * SIDE;
		dx < 0 ? fld <<= -dx : fld >>= dx;
		return fld;
	}

	bool tryGoToDest(int dx, int dy) {
		if (visited.find(make_pair(dx, dy)) != visited.end())
			return false;
		visited.emplace(dx, dy);
		Field tmp = moveBy(soldiers, dx, dy);
		if ((tmp & destinations) == destinations)
			return true;
		if (moveBy(tmp, -dx, -dy) != soldiers || (tmp & walls).any())
			return false;
		static const int DX[4] = { 0, 1, 0, -1 };
		static const int DY[4] = { 1, 0, -1, 0 };
		for (int dir = 0; dir < 4; ++dir) {
			if (tryGoToDest(dx + DX[dir], dy + DY[dir]))
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

		while (cin >> h >> w) {
			soldiers.reset();
			walls.set();
			destinations.reset();
			visited.clear();
			for (size_t y = 0; y < h; ++y)
				for (size_t x = 0; x < w; ++x)
					walls[y * SIDE + x] = false;
			for (size_t y = 0; y < h; ++y) {
				for (size_t x = 0; x < w; ++x) {
					char c;
					cin >> c;
					Field& fld = c == 'x' ? soldiers : 
						c == '#' ? walls : destinations;
					if (c != '.')
						fld[y * SIDE + x] = true;
				}
			}
			cout << (tryGoToDest(0, 0) ? "YES\n" : "NO\n");
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
