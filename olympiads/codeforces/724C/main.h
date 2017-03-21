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

	struct Point {
		Point(int x = 0, int y = 0) : x(x), y(y) {}
		int x, y;
		friend Point operator - (const Point& lhs, const Point& rhs) {
			return{ rhs.x - lhs.x, rhs.y - lhs.y };
		}
		friend bool operator == (const Point& lhs, const Point& rhs) {
			return lhs.x == rhs.x &&  lhs.y == rhs.y;
		}
	};

	inline bool collinear(const Point& lhs, const Point& rhs) {
		return lhs.x * rhs.x >= 0 && lhs.y * rhs.y >= 0;
	}

	inline bool parallel(const Point& lhs, const Point& rhs) {
		return collinear(lhs, rhs) && lhs.x - rhs.x == lhs.y - rhs.y;
	}

	inline void toNextPoint(Point& cur, Point& dir, int w, int h) {
		int t;
		Point nxt;
		if (dir.x > 0) {
			if (dir.y > 0) {
				t = min(w - cur.x, h - cur.y);
				nxt = { cur.x + t, cur.y + t };
			}
			else {
				t = min(w - cur.y, cur.y);
				nxt = { cur.x + t, cur.y - t };
			}
		}
		else {
			if (dir.y > 0) {
				t = min(cur.x, h - cur.y);
				nxt = { cur.x - t, cur.y + t };
			}
			else {
				t = min(cur.x, cur.y);
				nxt = { cur.x - t, cur.y - t };
			}
		}
		cur = nxt;
		const Point a1 = { 0, 0 }, a2 = { 0, h }, a3 = { w, 0 }, a4 = { w, h };
		if (cur == a1 || cur == a2 || cur == a3 || cur == a4)
			dir = { 0,0 };
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int n, m, k;
		while (cin >> n >> m >> k) {
			vector<Point> sensors(k);
			for (Point& sensor : sensors)
				cin >> sensor.x >> sensor.y;
			vector<int> times(k, -1);
			Point cur(0, 0), dir(1, 1);
			set<pair<Point, Point>> visited;
			for (size_t i = 0; i < )
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
