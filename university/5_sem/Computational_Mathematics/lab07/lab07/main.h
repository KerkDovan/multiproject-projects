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

#define stringify(...) stringify2(__VA_ARGS__)
#define stringify2(...) #__VA_ARGS__

// Changeable code stops here. 
	
#ifdef _LOCAL_MULTIPROJECT_

#include "multiproject.h"

#include "PolStr.h"

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

	enum Rule {
		LeftRectanglesRule = 1, RightRectanglesRule = 2, TrapezoidalRule = 3, SimpsonsRule = 4,
	};

	enum GridType {
		Regular = 'r', Irregular = 'i', Dynamical = 'd',
	};

	enum FunctionDefinition {
		Table = 't', Analytical = 'a',
	};

	struct Point {
		double x, y;
	};

	double integrateLeftRect(const vector<Point>& grid) {
		double result = 0.0;
		for (size_t i = 0; i < grid.size() - 1; ++i)
			result += grid[i].y * (grid[i + 1].x - grid[i].x);
		return result;
	}

	double integrateRightRect(const vector<Point>& grid) {
		double result = 0.0;
		for (size_t i = 1; i < grid.size(); ++i)
			result += grid[i].y * (grid[i].x - grid[i - 1].x);
		return result;
	}

	double integrateTrapezoidal(const vector<Point>& grid) {
		double result = 0.0;
		for (size_t i = 0; i < grid.size() - 1; ++i)
			result += 0.5 * (grid[i].y + grid[i + 1].y) * (grid[i + 1].x - grid[i].x);
		return result;
	}

	double integrateSimpson(const vector<Point>& grid) {
		double result = 0.0;
		vector<double> h(grid.size() - 1);
		for (size_t i = 0; i < h.size(); ++i)
			h[i] = grid[i + 1].x - grid[i].x;
		size_t cnt = grid.size() / 2 - 1;
		for (size_t i = 0; i < cnt; ++i) {
			size_t i2 = 2 * i, i21 = i2 + 1;
			double hp = h[i21] + h[i2], hm = 2.0 * h[i2] - h[i21];
			result += (hp / (6.0 * h[i21] * h[i2])) * (
				h[i21] * hm * grid[i2].y +
				hp * hp * grid[i21].y +
				h[i2] * hm * grid[i2 + 2].y
				);
		}
		return result;
	}

	void addNewPoints(vector<Point>& dest, const vector<Point>& src, const char* polExpr) {
		if (src.size() < 2)
			throw "Source does not have enough points";
		dest.clear();
		dest.reserve(src.size() * 2 - 1);
		dest.emplace_back(src[0]);
		for (size_t i = 1; i < src.size(); ++i) {
			double x = (src[i].x + src[i - 1].x) / 2.0;
			double y = EvalPolStr(polExpr, x, 0);
			dest.emplace_back(Point{ x, y });
			dest.emplace_back(src[i]);
		}
	}

	const double EPS = 1e-9;

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		function<double(const vector<Point>&)> integrationRule[4] = {
			&integrateLeftRect,
			&integrateRightRect,
			&integrateTrapezoidal,
			&integrateSimpson,
		};

		size_t test = 0;
		size_t rule;
		char gridType;
		size_t intervalsCount;
		while (cin >> rule >> gridType >> intervalsCount) {
			cout << "----Test #" << ++test << "----\n";
			size_t pointsCount = intervalsCount + 1;
			vector<Point> grid;
			grid.resize(pointsCount);
			if (gridType != Irregular) {
				double a, b, d;
				cin >> a >> b;
				if (b < a)
					swap(a, b);
				d = b - a;
				grid[0] = { a, 0.0 };
				for (size_t i = 1; i < intervalsCount; ++i)
					grid[i] = { grid[i - 1].x + d, 0.0 };
				grid.back() = { b, 0.0 };
			}
			else { // gridType == Irregular
				for (Point& point : grid)
					cin >> point.x;
			}
			char functionDefinition;
			cin >> functionDefinition >> ws;
			string expression;
			char* polExpr = nullptr;
			if (functionDefinition == Table) {
				for (Point& point : grid)
					cin >> point.y;
			}
			else { // functionDefinition == Analytical
				getline(cin, expression);
				polExpr = CreatePolStr(expression.c_str(), 0);
				for (Point& point : grid)
					point.y = EvalPolStr(polExpr, point.x, 0);
			}
			if (gridType != Dynamical) {
				double integral = integrationRule[rule - 1](grid);
				cout << integral << "\n";
			}
			else { // gridType == Dynamical
				if (polExpr == nullptr)
					throw "If grid type is dynamical then function should be defined analytically";
				double eps;
				cin >> eps;
				double cur, prev;
				prev = integrationRule[rule - 1](grid);
				vector<Point> curGrid;
				addNewPoints(curGrid, grid, polExpr);
				cur = integrationRule[rule - 1](curGrid);
				size_t step = 0;
				while (fabs((cur - prev) / (fabs(cur) < EPS ? 1.0 : cur)) > eps) {
					swap(curGrid, grid);
					addNewPoints(curGrid, grid, polExpr);
					prev = cur;
					cur = integrationRule[rule - 1](curGrid);
					++step;
				}
				cout << cur << "\n" << step << "\n" <<
					fabs((cur - prev) / (fabs(cur) < EPS ? 1.0 : cur)) << "\n";
			}
			delete[] polExpr;
			cout << "\n";
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
