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

	const double EPS = 1e-1;

	inline bool equal(double a, double b) {
		return fabs(a - b) <= EPS;
	}

	inline bool zero(double a) {
		return equal(a, 0.0);
	}

	struct Point {
		Point() {}
		Point(double x, double y) : x(x), y(y) {}
		double x;
		double y;
		friend Point operator - (const Point& a, const Point& b) {
			return Point(a.x - b.x, a.y - b.y);
		}
		friend istream& operator >> (istream& is, Point& p) {
			return is >> p.x >> p.y;
		}
		friend bool operator == (const Point& a, const Point& b) {
			return zero(fabs(a.x - b.x)) && zero(fabs(a.y - b.y));
		}
	};

	inline double dist(const Point& p) {
		return hypot(p.x, p.y);
	}

	inline double sqr(double x) {
		return x * x;
	}

	double area(const Point& _a, const Point& _b, const Point& _c) {
		double a, b, c;
		a = dist(_b - _c);
		b = dist(_c - _a);
		c = dist(_a - _b);
		double sina = sqrt(1 - sqr((a * a + b * b - c * c) / (2.0 * a * b)));
		return a * b * sina / 2.0;
	}

	bool onEdge(const Point& a, const Point& b, const Point& c, const Point& d) {
		if (a == d || b == d || c == d)
			return true;
		if (equal(dist(a - b), dist(a - d) + dist(b - d)) ||
			equal(dist(a - c), dist(a - d) + dist(c - d)) ||
			equal(dist(b - c), dist(b - d) + dist(c - d)))
			return true;
		return false;
	}

	//bool byLeft(const Point& a, const Point& b, const Point& c) {
	//	double d = ((c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x));
	//	return d <= 0 || zero(d);
	//}
	//
	//bool inside(const Point& a, const Point& b, const Point& c, const Point& d) {
	//	return byLeft(a, b, d) && byLeft(b, c, d) && byLeft(c, a, d) ||
	//		byLeft(a, c, d) && byLeft(c, b, d) && byLeft(b, a, d);
	//}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		Point a, b, c, d;
		while (cin >> a >> b >> c >> d) {
			if (onEdge(a, b, c, d) || zero(area(a, b, c) - area(a, b, d) - area(a, c, d) - area(b, c, d)))
			//if (inside(a, b, c, d))
				cout << "In\n";
			else
				cout << "Out\n";
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif