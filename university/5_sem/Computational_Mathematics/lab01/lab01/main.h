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

	struct IntervalByIntervalMethod {
		virtual pair<double, double> operator () (double, double, const char*) const = 0;
	};

	struct IntervalByDichotomyMethod : public IntervalByIntervalMethod {
		pair<double, double> operator () (double a, double b, const char*) const {
			double tmp = (a + b) / 2.0;
			return make_pair(tmp, tmp);
		}
	};

	struct IntervalByChordsMethod : public IntervalByIntervalMethod {
		pair<double, double> operator () (double a, double b, const char* expr) const {
			double fa = EvalPolStr(expr, a);
			double fb = EvalPolStr(expr, b);
			double tmp = a - (b - a) * fa / (fb - fa) ;
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

	double findRootByIntervalMethod(
		const char* expr, 
		double a, 
		double b, 
		double eps, 
		const IntervalByIntervalMethod& method
	) {
		while (fabs(b - a) >= eps && fabs(EvalPolStr(expr, (b + a) / 2.0)) >= eps) {
			if (b < a)
				swap(a, b);
			double c, d;
			tie(d, c) = method(a, b, expr);
			double ev_a, ev_b;
			ev_a = EvalPolStr(expr, a);
			ev_b = EvalPolStr(expr, d);
			if (ev_a * ev_b <= 0.0 && fabs(b - d) > eps)
				b = d;
			else
				a = c;
		}
		return round((b + a) / (2.0 * eps)) * eps;
	}

	struct NextStepByIterationsMethod {
		// Начальное приближение
		virtual double operator () (double a, double b, const char* expr) const = 0;
		// Следующее приближение (со сдвигом границ для комбинированного метода)
		virtual tuple<double, double, double>
			operator () (double a, double b, double x, const char* expr) const = 0;
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
			double da = EvalPolStr(expr, a, 1);
			if (isnan(da))
				da = a;
			double db = EvalPolStr(expr, b, 1);
			if (isnan(db))
				db = b;
			return make_tuple(a, b, x - rx / max(da, db));
		}
	};

	struct NextStepByCombinedMethod : public NextStepByIterationsMethod {
		double operator () (double a, double b, const char*) const {
			return (a + b) / 2.0;
		}
		tuple<double, double, double>
			operator () (double a, double b, double, const char* expr) const {
			double ax = a - EvalPolStr(expr, a, 0) / EvalPolStr(expr, a, 1);
			if (isnan(ax))
				ax = a;
			double bx = b - EvalPolStr(expr, b, 0) / EvalPolStr(expr, b, 1);
			if (isnan(bx))
				bx = b;
			double c = IntervalByChordsMethod()(a, b, expr).first;
			if (isnan(c))
				c = (ax + bx) / 2.0;
			return EvalPolStr(expr, a, 0) * EvalPolStr(expr, a, 2) > 0 ?
				make_tuple(ax, c, (ax + c) / 2.0) :
				make_tuple(c, bx, (c + bx) / 2.0);
		}
	};

	double findRootByIterationsMethod(
		const char* expr,
		double a,
		double b,
		double eps,
		const NextStepByIterationsMethod& method
	) {
		double curx = method(a, b, expr), prevx;
		do {
			prevx = curx;
			tie(a, b, curx) = method(a, b, curx, expr);
		} while (fabs(curx - prevx) > eps);
		return curx;
	}

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		cout << scientific;

		size_t testNumber = 0;

		int methodType;
		while (cin >> methodType >> ws) {
			cout << ++testNumber << ". ";
			Error = 0;
			string expr;
			getline(cin, expr);
			char* polStatement = CreatePolStr(expr.c_str(), 0);
			double a, b, eps;
			cin >> a >> b >> eps;
			if (Error) {
				cout << "Error: " << Error << '\n';
				continue;
			}
			double root = 0.0;
			switch (methodType) {
			case 1:
				// Метод дихотомии
				cout << "Dychotomy method:\n";
				root = findRootByIntervalMethod(polStatement, a, b, eps, IntervalByDichotomyMethod());
				break;
			case 2:
				// Метод хорд
				cout << "Chords method:\n";
				root = findRootByIntervalMethod(polStatement, a, b, eps, IntervalByChordsMethod());
				break;
			case 3:
				// Метод Ньютона
				cout << "Newton method:\n";
				root = findRootByIterationsMethod(polStatement, a, b, eps, NextStepByNewtonMethod());
				break;
			case 4:
				// Комбинированный метод
				cout << "Combined method:\n";
				root = findRootByIterationsMethod(polStatement, a, b, eps, NextStepByCombinedMethod());
				break;
			case 5:
				// Метод итераций
				cout << "Iterations method:\n";
				root = findRootByIterationsMethod(polStatement, a, b, eps, NextStepByMethodOfIterations());
				break;
			case 6:
				// Метод золотого сечения
				cout << "Golden section method:\n";
				root = findRootByIntervalMethod(polStatement, a, b, eps, IntervalByGoldenSectionMethod());
				break;
			}
			cout << "Expression: " << expr << '\n';
			if (Error)
				cout << "Error: " << Error << '\n';
			else
				cout << "Answer: " << root << '\n';
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