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
#include <tuple>
#include <vector>

#include "libs/PolStr.h"

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
#define breakpoint_counter_init(...)
#define breakpoint_when(...)
#define breakpoint_counters_clear
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

	const double GOLDEN_SECTION = 1.618033988749895;

	inline double round_by(double number, double eps) {
		return round(number / eps) * eps;
	}

	inline double max_der(double a, double b, const char* expr) {
		if (a > b)
			swap(a, b);
		double step = (a + b) / 1000.0;
		double result = EvalPolStr(expr, b, 1);
		while (a < b) {
			result = max(result, EvalPolStr(expr, a, 1));
			a += step;
		}
		return result;
	}

	struct IntervalByIntervalMethod {
		virtual pair<double, double> operator () (double, double, const char*) const = 0;
	};

	struct IntervalByDichotomyMethod : public IntervalByIntervalMethod {
		pair<double, double> operator () (double a, double b, const char*) const {
			double tmp = (a + b) / 2.0;
			return make_pair(tmp, tmp);
		}
	};

	struct IntervalByGoldenSectionMethod : public IntervalByIntervalMethod {
		pair<double, double> operator () (double a, double b, const char*) const {
			double d = a + (b - a) / GOLDEN_SECTION;
			double c = a + (b - a) / (GOLDEN_SECTION * GOLDEN_SECTION);
			return make_pair(d, c);
		}
	};

	tuple<double, double, double> findRootByIntervalMethod( // < x*, epsx* , epsy* >
		const char* expr,
		double a,
		double b,
		double epsx,
		double epsy,
		const IntervalByIntervalMethod& method
	) {
		while (fabs(b - a) / 2 >= epsx || fabs(EvalPolStr(expr, (b + a) / 2.0)) >= epsy) {
			if (b < a)
				swap(a, b);
			double c, d;
			tie(d, c) = method(a, b, expr);
			double ev_a, ev_d;
			ev_a = EvalPolStr(expr, a);
			ev_d = EvalPolStr(expr, d);
			if (ev_a * ev_d <= 0.0/* && fabs(b - d) > eps*/)
				b = d;
			else
				a = c;
		}
		double res = round((b + a) / (2.0 * epsx)) * epsx;
		return make_tuple(
			res, 
			fabs(b - a) / 2, 
			fabs(EvalPolStr(expr, res)));
	}

	struct NextStepByIterationsMethod {
		// Начальное приближение
		virtual double operator () (double a, double b, const char* expr) const = 0;
		// Следующее приближение (со сдвигом границ для комбинированного метода)
		virtual tuple<double, double, double>
			operator () (double a, double b, double x, const char* expr) const = 0;
	};

	struct NextStepByChordsMethod : public NextStepByIterationsMethod {
		double operator () (double a, double b, const char*) const {
			return (a + b) / 2.0;
		}
		tuple<double, double, double> 
			operator () (double a, double b, double, const char* expr) const
		{
			double fa = EvalPolStr(expr, a);
			double fb = EvalPolStr(expr, b);
			double tmp = a - (b - a) * fa / (fb - fa);
			return EvalPolStr(expr, a) * EvalPolStr(expr, tmp) <= 0.0 ?
				make_tuple(a, tmp, tmp) :
				make_tuple(tmp, b, tmp);
		}
	};

	struct NextStepByNewtonMethod : public NextStepByIterationsMethod {
		double operator () (double a, double b, const char* expr) const {
			return EvalPolStr(expr, a, 0) * EvalPolStr(expr, a, 2) > 0 ? a : b;
		}
		tuple<double, double, double>
			operator () (double a, double b, double x, const char* expr) const
		{
			return make_tuple(a, b,
				x - EvalPolStr(expr, x, 0) / EvalPolStr(expr, x, 1));
		}
	};

	struct NextStepByMethodOfIterations : public NextStepByIterationsMethod {
		double operator () (double a, double b, const char*) const {
			return (a + b) / 2.0;
		}
		tuple<double, double, double>
			operator () (double a, double b, double x, const char* expr) const
		{
			double rx = EvalPolStr(expr, x, 0);
			return make_tuple(a, b, x - rx / max_der(a, b, expr));
		}
	};

	struct NextStepByCombinedMethod : public NextStepByIterationsMethod {
		double operator () (double a, double b, const char*) const {
			return (a + b) / 2.0;
		}
		tuple<double, double, double>
			operator () (double a, double b, double, const char* expr) const {
			static NextStepByNewtonMethod mNewton;
			static NextStepByChordsMethod mChords;
			double ax = get<2>(mNewton(0, 0, a, expr));
			if (isnan(ax))
				ax = a;
			double bx = get<2>(mNewton(0, 0, b, expr));
			if (isnan(bx))
				bx = b;
			double c, d, unused;
			tie(c, d, unused) = mChords(a, b, 0, expr);
			if (fabs(c - a) < 1e-10)
				c = d;
			if (isnan(c))
				c = (ax + bx) / 2.0;
			return EvalPolStr(expr, a, 0) * EvalPolStr(expr, a, 2) > 0 ?
				make_tuple(ax, c, (ax + c) / 2.0) :
				make_tuple(c, bx, (c + bx) / 2.0);
		}
	};

	tuple<double, double, double> findRootByIterationsMethod( // < x*, epsx*, epsy* >
		const char* expr,
		double a,
		double b,
		double epsx,
		double epsy,
		const NextStepByIterationsMethod& method
	) {
		double curx = method(a, b, expr), prevx;
		do {
			prevx = curx;
			tie(a, b, curx) = method(a, b, curx, expr);
		} while (fabs(curx - prevx) > epsx || fabs(EvalPolStr(expr, curx)) > epsy);
		return make_tuple(
			curx,
			fabs(curx - prevx),
			fabs(EvalPolStr(expr, curx)));
	}

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t testNumber = 0;

		int methodType;
		while (cin >> methodType >> ws) {
			cout << ++testNumber << ". ";
			Error = 0;
			string expr;
			getline(cin, expr);
			char* polStatement = CreatePolStr(expr.c_str(), 0);
			double a, b, epsx, epsy;
			cin >> a >> b >> epsx >> epsy;
			double ach_x, ach_y;
			if (Error) {
				cout << "Error: " << Error << '\n';
				continue;
			}
			double root = 0.0;
			switch (methodType) {
			case 1:
				// Метод дихотомии
				cout << "Dychotomy method:\n";
				tie(root, ach_x, ach_y) = findRootByIntervalMethod(polStatement, a, b, epsx, epsy, IntervalByDichotomyMethod());
				break;
			case 2:
				// Метод хорд
				cout << "Chords method:\n";
				tie(root, ach_x, ach_y) = findRootByIterationsMethod(polStatement, a, b, epsx, epsy, NextStepByChordsMethod());
				break;
			case 3:
				// Метод Ньютона
				cout << "Newton method:\n";
				tie(root, ach_x, ach_y) = findRootByIterationsMethod(polStatement, a, b, epsx, epsy, NextStepByNewtonMethod());
				break;
			case 4:
				// Комбинированный метод
				cout << "Combined method:\n";
				tie(root, ach_x, ach_y) = findRootByIterationsMethod(polStatement, a, b, epsx, epsy, NextStepByCombinedMethod());
				break;
			case 5:
				// Метод итераций
				cout << "Iterations method:\n";
				tie(root, ach_x, ach_y) = findRootByIterationsMethod(polStatement, a, b, epsx, epsy, NextStepByMethodOfIterations());
				break;
			case 6:
				// Метод золотого сечения
				cout << "Golden section method:\n";
				tie(root, ach_x, ach_y) = findRootByIntervalMethod(polStatement, a, b, epsx, epsy, IntervalByGoldenSectionMethod());
				break;
			}
			cout << "Expression: " << expr << '\n';
			if (Error)
				cout << "Error: " << Error << '\n';
			else {
				cout << "x* = " << defaultfloat << round_by(root, epsx) << '\n';
				double fx = EvalPolStr(polStatement, root, 0);
				cout << "f(x*) = " << defaultfloat << round_by(fx, epsy) << '\n';
				cout << "eps* by x = " << scientific << ach_x << '\n';
				cout << "eps* by f(x) = " << scientific << ach_y << '\n';
			}
			cout << '\n';
			delete[] polStatement;
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif