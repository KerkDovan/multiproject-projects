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

	struct Point {
		double x, y;
		Point() {}
		Point(double x, double y) : x(x), y(y) {}
		friend istream& operator >> (istream& lhs, Point& rhs) {
			return lhs >> rhs.x >> rhs.y;
		}
	};

	struct Line {
		double a, b;
		Line(const Point& p1, const Point& p2) {
			a = (p2.y - p1.y) / (p2.x - p1.x);
			b = p1.y - a * p1.x;
		}
		inline double operator () (double x) {
			return a * x + b;
		}
	};

	inline double get_vertline_and_circle_intersection(double x, const Point& c, double r) {
		double tx = x - c.x;
		double result = sqrt(r * r - tx * tx) + c.y;
		if (isnan(result))
			result = -fabs(x - c.x);
		return result;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		Point a, b, c, d;
		double l;
		while (cin >> a >> b >> c >> d >> l) {

			//breakpoint_when_offset(kek, 2, 1);

			if (d.x > b.x)
				a = b, b = c;
			Line line(a, b);
			double x1 = a.x, x2 = b.x;

			while (x2 - x1 > 1e-6) {
				const double dx3 = (x2 - x1) / 3.0;
				double tx, ty;

				tx = x1 + dx3;
				ty = line(tx);
				double ty1 = get_vertline_and_circle_intersection(d.x, Point(tx, ty), l);

				tx = x2 - dx3;
				ty = line(tx);
				double ty2 = get_vertline_and_circle_intersection(d.x, Point(tx, ty), l);

				if (ty1 > ty2)
					x2 -= dx3;
				else
					x1 += dx3;
			}

			double ty = get_vertline_and_circle_intersection(d.x, Point(x1, line(x1)), l);
			if (ty >= d.y)
				cout << fixed << setprecision(5) << 0.0;
			else
				cout << fixed << setprecision(5) << d.y - ty;
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
