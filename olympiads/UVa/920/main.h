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
		double x, y;
		friend double operator * (const Point& a, const Point& b) {
			return a.x * b.y - a.y * b.x;
		}
	};

	double getXUsingLineAndY(double x1, double y1, double x2, double y2, double y) {
		return (y - y1) * (x2 - x1) / (y2 - y1) + x1;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t testCount;
		cin >> testCount;
		for (size_t testNumber = 0; testNumber < testCount; ++testNumber) {
			size_t pCount;
			cin >> pCount;
			map<double, double, greater<double>> points;
			double total = 0.0, prevHstX = 0.0, prevHstY = 0.0;
			for (size_t i = 0; i < pCount; ++i) {
				double x, y;
				cin >> x >> y;
				points.emplace(x, y);
				prevHstX = max(prevHstX, x);
			}
			for (auto nxt = points.begin(), cur = nxt++; nxt != points.end(); ++nxt, ++cur) {
				if (nxt->second < prevHstY)
					continue;
				double dx, dy;
				if (cur->second < prevHstY) {
					dx = getXUsingLineAndY(nxt->first, nxt->second, cur->first, cur->second, prevHstY) - nxt->first;
					dy = nxt->second - prevHstY;
				}
				else {
					dx = cur->first - nxt->first;
					dy = nxt->second - cur->second;
				}
				total += hypot(dx, dy);
				if (nxt->second >= prevHstY) {
					prevHstY = nxt->second;
					prevHstX = nxt->first;
				}
			}
			cout << fixed << setprecision(2) << total << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
