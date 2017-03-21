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

	struct Func {
		struct EvalType {
			virtual double x(size_t i) const = 0;
			virtual double y(size_t i) const = 0;
		};
		struct Table : public EvalType {
			vector<Point> values;
			double x(size_t i) const override { return values[i].x; }
			double y(size_t i) const override { return values[i].y; }
		};
		struct Analytical : public EvalType {
			string pol_func;
			double x0, h;
			double x(size_t i) const override { return x0 + i * h; }
			double y(size_t i) const override { return EvalPolStr(pol_func.c_str(), x0 + i * h); }
		};
		Func(const vector<Point>& vals) {
			eval = new Table();
			dynamic_cast<Table*>(eval)->values = vals;
			count = vals.size();
		}
		Func(const string& pf, double x0, double h, size_t cnt) {
			eval = new Analytical();
			auto p = dynamic_cast<Analytical*>(eval);
			p->pol_func = pf;
			p->x0 = x0;
			p->h = h;
			count = cnt;
		}
		~Func() {
			delete eval;
		}
		EvalType* eval;
		size_t count;
		double x(size_t i) const { return (*eval).x(i); }
		double y(size_t i) const { return (*eval).y(i); }
		void insertPoints() {
			auto p = dynamic_cast<Analytical*>(eval);
			double b = p->x0 + count * p->h;
			count = max((size_t)(count * 1.5), count + 1);
			p->h = (b - p->x0) / count;
		}
	};

	double integrateLeftRect(const Func& func) {
		double result = 0.0;
		for (size_t i = 0; i < func.count - 1; ++i)
			result += func.y(i) * (func.x(i + 1) - func.x(i));
		return result;
	}

	double integrateRightRect(const Func& func) {
		double result = 0.0;
		for (size_t i = 1; i < func.count; ++i)
			result += func.y(i) * (func.x(i) - func.x(i - 1));
		return result;
	}

	double integrateTrapezoidal(const Func& func) {
		double result = 0.0;
		for (size_t i = 0; i < func.count - 1; ++i)
			result += 0.5 * (func.y(i) + func.y(i + 1)) * (func.x(i + 1) - func.x(i));
		return result;
	}

	double integrateSimpson(const Func& func) {
		double result = 0.0;
		vector<double> h(func.count - 1);
		for (size_t i = 0; i < h.size(); ++i)
			h[i] = func.x(i + 1) - func.x(i);
		size_t cnt = func.count / 2 - 1;
		for (size_t i = 0; i < cnt; ++i) {
			size_t i2 = 2 * i, i21 = i2 + 1;
			double hp = h[i21] + h[i2], hm = 2.0 * h[i2] - h[i21];
			result += (hp / (6.0 * h[i21] * h[i2])) * (
				h[i21] * hm * func.y(i2) +
				hp * hp * func.y(i21) +
				h[i2] * hm * func.y(i2 + 2)
				);
		}
		return result;
	}

	const double EPS = 1e-9;

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		function<double(const Func&)> integrationRule[4] = {
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
			double x0, h;
			if (gridType != Irregular) {
				// gridType == Regular || gridType == Dynamical
				double b;
				cin >> x0 >> b;
				if (b < x0)
					swap(x0, b);
				h = (b - x0) / intervalsCount;
			}
			else { // gridType == Irregular
				grid.resize(pointsCount);
				for (Point& point : grid)
					cin >> point.x;
			}
			char functionDefinition;
			cin >> functionDefinition >> ws;
			string expression;
			char* polExpr = nullptr;
			if (functionDefinition == Table) {
				// functionDefinition == Table
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
				// gridType == Regular || gridType == Irregular
				Func func(grid);
				double integral = integrationRule[rule - 1](func);
				cout << integral << "\n";
			}
			else { // gridType == Dynamical
				if (polExpr == nullptr) {
					cout << flush;
					throw "If grid type is dynamical then function should be defined analytically";
				}
				double eps;
				cin >> eps;
				double cur, prev;
				Func func(polExpr, x0, h, intervalsCount);
				prev = integrationRule[rule - 1](func);
				func.insertPoints();
				cur = integrationRule[rule - 1](func);
				size_t step = 0;
				auto prec = [&]() { return fabs((cur - prev) / (fabs(cur) < EPS ? 1.0 : cur)); };
				while (prec() > eps) {
					func.insertPoints();
					prev = cur;
					cur = integrationRule[rule - 1](func);
					++step;
				}
				cout << cur << "\n" << step << "\n" << prec() << "\n";
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
