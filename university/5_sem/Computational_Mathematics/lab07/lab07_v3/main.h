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

struct EvalTypeX {
	virtual double operator () (size_t) const = 0;
};
template<class X> struct EvalTypeY {
	virtual double operator () (size_t, const X &) const = 0;
};
template<class X> struct TableFunc : public EvalTypeY<X> {
	TableFunc() {}
	TableFunc(const vector<double>& vals) : values(vals) {}
	vector<double> values;
	double operator () (size_t i, const X&) const override { return values[i]; }
};
template<class X> struct AnalyticalFunc : public EvalTypeY<X> {
	AnalyticalFunc() {}
	AnalyticalFunc(string pol) : pol_func(pol) {}
	string pol_func;
	double operator () (size_t i, const X& x) const override { return EvalPolStr(pol_func.c_str(), x(i)); }
};
struct IrregularGrid : public EvalTypeX {
	IrregularGrid() {}
	IrregularGrid(const vector<double>& vals) : values(vals) {}
	vector<double> values;
	double operator () (size_t i) const override { return values[i]; }
};
struct RegularGrid : public EvalTypeX {
	RegularGrid() {}
	RegularGrid(double x, double dx) : x0(x), h(dx) {}
	double x0, h;
	double operator () (size_t i) const override { return x0 + i * h; }
};
template<class XType, template<class> class YType> struct Func
{
	typedef XType X;
	typedef YType<XType> Y;
	X my_x;
	Y my_y;
	size_t count;
	Func(const X& _x, const Y& _y, size_t _count) :
		my_x(_x), my_y(_y), count(_count) { }
	double x(size_t i) const { return my_x(i); }
	double y(size_t i) const { return my_y(i, my_x); }
};

void insertPoints(Func<RegularGrid, AnalyticalFunc>& func) {
	double b = func.my_x.x0 + func.count * func.my_x.h;
	func.count = max((size_t)(func.count * 1.5), func.count + 1);
	func.my_x.h = (b - func.my_x.x0) / func.count;
}

// Variants of EvalType
/*
struct EvalTypeX2 {
virtual double x(size_t) const = 0;
};
struct EvalTypeY2 {
virtual double y(size_t, const EvalTypeX2 *) const = 0;
};
struct TableFunc2 : public EvalTypeY2 {
vector<double> values;
double y(size_t i, const EvalTypeX2 *) const override { return values[i]; }
};
struct AnalyticalFunc2 : public EvalTypeY2 {
string pol_func;
double y(size_t i, const EvalTypeX2 *x) const override { return EvalPolStr(pol_func.c_str(), x->x(i)); }
};
struct IrregularGrid2 : public EvalTypeX2 {
vector<double> values;
double x(size_t i) const override { return values[i]; }
};
struct RegularGrid2 : public EvalTypeX2 {
double x0, h;
double x(size_t i) const override { return x0 + i * h; }
};
struct EvalType2
{
EvalTypeX2 *x;
EvalTypeY2 *y;
EvalType2(EvalTypeX2 *x, EvalTypeY2 *y)
{
this->x = x;
this->y = y;
x->x(0);
y->y(0, x);
}
};
EvalType2 e2{ new RegularGrid2(), new AnalyticalFunc2() };

struct EvalTypeXY3 {
virtual double x(size_t) const { throw "!!!"; }
virtual double y(size_t) const { throw "!!!"; }
};
struct TableFunc3 : public EvalTypeXY3 {
vector<double> values;
double y(size_t i) const override { return values[i]; }
};
struct AnalyticalFunc3 : public EvalTypeXY3 {
string pol_func;
double y(size_t i) const override { return EvalPolStr(pol_func.c_str(), x(i)); }
};
struct IrregularGrid3 : public EvalTypeXY3 {
vector<double> values;
double x(size_t i) const override { return values[i]; }
};
struct RegularGrid3 : public EvalTypeXY3 {
double x0, h;
double x(size_t i) const override { return x0 + i * h; }
};
struct EvalTypeIT3 : public IrregularGrid3, public TableFunc3
{
EvalTypeIT3()
{
IrregularGrid3::x(0);
TableFunc3::y(0);
}
};
EvalTypeIT3 e3;

struct EvalTypeX4 {
virtual double x(size_t) const = NULL;
};
struct EvalTypeY4 {
virtual double y(size_t, const EvalTypeX4 *) const = NULL;
};
struct TableFunc4 : public EvalTypeY4 {
vector<double> values;
double y(size_t i, const EvalTypeX4 *) const override { return values[i]; }
};
struct AnalyticalFunc3 : public EvalTypeY4 {
string pol_func;
double y(size_t i, const EvalTypeX4 *x) const override { return EvalPolStr(pol_func.c_str(), x->x(i)); }
};
struct IrregularGrid4 : public EvalTypeX4 {
vector<double> values;
double x(size_t i) const override { return values[i]; }
};
struct RegularGrid4 : public EvalTypeX4 {
double x0, h;
double x(size_t i) const override { return x0 + i * h; }
};
struct EvalTypeIT4 : public IrregularGrid4, public TableFunc4
{
EvalTypeIT4()
{
x(0);
y(0, this);
}
};
EvalTypeIT4 e4;
*/

// Old Func
/*
template<class EvalType>
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
*/

template<class Func>
double integrateLeftRect(const Func& func) {
	double result = 0.0;
	for (size_t i = 0; i < func.count - 1; ++i)
		result += func.y(i) * (func.x(i + 1) - func.x(i));
	return result;
}

template<class Func>
double integrateRightRect(const Func& func) {
	double result = 0.0;
	for (size_t i = 1; i < func.count; ++i)
		result += func.y(i) * (func.x(i) - func.x(i - 1));
	return result;
}

template<class Func>
double integrateTrapezoidal(const Func& func) {
	double result = 0.0;
	for (size_t i = 0; i < func.count - 1; ++i)
		result += 0.5 * (func.y(i) + func.y(i + 1)) * (func.x(i + 1) - func.x(i));
	return result;
}

template<class Func>
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

#define DefIntegrationRules(name, x, y) \
		function<double(const Func<x, y>&)> name[4] = { \
			&integrateLeftRect		<Func<x, y>>, \
			&integrateRightRect		<Func<x, y>>, \
			&integrateTrapezoidal	<Func<x, y>>, \
			&integrateSimpson		<Func<x, y>>, \
		}

	DefIntegrationRules(integrationRuleRT, RegularGrid, TableFunc);
	DefIntegrationRules(integrationRuleIT, IrregularGrid, TableFunc);
	DefIntegrationRules(integrationRuleRA, RegularGrid, AnalyticalFunc);
	DefIntegrationRules(integrationRuleIA, IrregularGrid, AnalyticalFunc);

#undef DefIntegrationRules

	size_t test = 0;
	size_t rule;
	char gridType;
	size_t intervalsCount;
	while (cin >> rule >> gridType >> intervalsCount) {
		cout << "----Test #" << ++test << "----\n";
		size_t pointsCount = intervalsCount + 1;
		vector<double> gridX, gridY;
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
			gridX.resize(pointsCount);
			for (double& x : gridX)
				cin >> x;
		}
		char functionDefinition;
		cin >> functionDefinition >> ws;
		string expression;
		char* polExpr = nullptr;
		if (functionDefinition == Table) {
			// functionDefinition == Table
			gridY.resize(pointsCount);
			for (double& y : gridY)
				cin >> y;
		}
		else { // functionDefinition == Analytical
			getline(cin, expression);
			polExpr = CreatePolStr(expression.c_str(), 0);
		}
		if (gridType != Dynamical) {
			// gridType == Regular || gridType == Irregular
			double integral;
			if (gridType == Regular) {
				if (functionDefinition == Table) {
					Func<RegularGrid, TableFunc> func(
						RegularGrid(x0, h), TableFunc<RegularGrid>(gridY), pointsCount);
					integral = integrationRuleRT[rule - 1](func);
				}
				else {
					Func<RegularGrid, AnalyticalFunc> func(
						RegularGrid(x0, h), AnalyticalFunc<RegularGrid>(polExpr), pointsCount);
					integral = integrationRuleRA[rule - 1](func);
				}
			}
			else {
				if (functionDefinition == Table) {
					Func<IrregularGrid, TableFunc> func(
						IrregularGrid(gridX), TableFunc<IrregularGrid>(gridY), pointsCount);
					integral = integrationRuleIT[rule - 1](func);
				}
				else {
					Func<IrregularGrid, AnalyticalFunc> func(
						IrregularGrid(gridX), AnalyticalFunc<IrregularGrid>(polExpr), pointsCount);
					integral = integrationRuleIA[rule - 1](func);
				}
			}
			cout << integral << "\n";
		}
		else { // gridType == Dynamical
			if (polExpr == nullptr) {
				cout << flush;
				throw "In case of dynamical grid the function should be defined analytically";
			}
			double eps;
			cin >> eps;
			double cur, prev;
			Func<RegularGrid, AnalyticalFunc> func(
				RegularGrid(x0, h), AnalyticalFunc<RegularGrid>(polExpr), intervalsCount);
			prev = integrationRuleRA[rule - 1](func);
			insertPoints(func);
			cur = integrationRuleRA[rule - 1](func);
			size_t step = 0;
			auto prec = [&]() { return fabs((cur - prev) / (fabs(cur) < EPS ? 1.0 : cur)); };
			while (prec() > eps) {
				insertPoints(func);
				prev = cur;
				cur = integrationRuleRA[rule - 1](func);
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
