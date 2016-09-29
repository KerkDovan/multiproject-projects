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
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string.h>
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

#define breakpoint_if(...)
#define breakpoint
#define only_multiproject(...)
#define debug_output(...)
#define freopen_in(filename) freopen(filename, "r", stdin)
#define freopen_out(filename) freopen(filename, "w", stdout)
#define close_files

#endif

// Changeable code continues here. 

	using namespace std;

	typedef long long ll;
	typedef unsigned long long ull;

	const double EPS = 1e-6;

	struct Point {
		double x, y;
		Point operator + (const Point& p) const { return { x + p.x, y + p.y }; }
		Point operator - (const Point& p) const { return { x - p.x, y - p.y }; }
		Point operator * (double m) const { return { x * m, y * m }; }
		double operator * (const Point& p) const { return x * p.y - y * p.x; }
		double operator % (const Point& p) const { return x * p.x + y * p.y; }
		Point rotate() const { return { -y, x }; }
		Point rotate(double cosa, double sina) const { return *this * cosa + rotate() * sina; }
		Point rotate(double angle) const { return rotate(cos(angle), sin(angle)); }
		double angle_to(const Point& to) const { return atan2(*this * to, *this % to); }
	};

	Point center(const Point& a, const Point& b, const Point& c) {
		return { (a.x + b.x + c.x) / 3.0, (a.y + b.y + c.y) / 3.0 };
	}

	bool line_intersection(Point A, Point B, Point C, Point D, Point& O) {
		double s1 = (C - A) * (D - A);
		double s2 = (D - B) * (C - B);
		double s = s1 + s2;
		if (fabs(s) <= EPS)
			return false;
		O = A + (B - A) * (s1 / s);
		return true;
	}

	double area(const Point& a, const Point& b, const Point& c) {
		return (c - a) * (b - a);
	}

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("i.in");
		freopen_out("i.out");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		Point a, b, c, p;
		int testCount;
		cin >> testCount;
		for (int test = 0; test < testCount; ++test) {
			int test_num;
			cin >> test_num;
			cout << test_num << ' ';
			cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
			double an_a = (b - a).angle_to(c - a);
			double an_b = (c - b).angle_to(a - b);
			double an_c = (a - c).angle_to(b - c);
			double left = 0.0, right = min({ an_a, an_b, an_c });
			Point a1 = a, b1 = b, c1 = c;
			while (true) {

			}
			p = center(a1, b1, c1);
			cout << p.x << ' ' << p.y << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif