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
		pair<double, double> operator () (double a, double b, const char* statement) const {
			double fa = EvalPolStr(const_cast<char*>(statement), a);
			double fb = EvalPolStr(const_cast<char*>(statement), b);
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
		const char* statement, 
		double a, 
		double b, 
		double eps, 
		const IntervalByIntervalMethod& method
	) {
		char* polstr = const_cast<char*>(statement);
		while (fabs(b - a) >= eps && fabs(EvalPolStr(polstr, (b + a) / 2.0)) >= eps) {
			if (b < a)
				swap(a, b);
			double c, d;
			tie(d, c) = method(a, b, statement);
			double ev_a, ev_b;
			ev_a = EvalPolStr(polstr, a);
			ev_b = EvalPolStr(polstr, d);
			if (ev_a * ev_b <= 0.0 && fabs(b - d) > eps)
				b = d;
			else
				a = c;
		}
		return round((b + a) / (2.0 * eps)) * eps;
	}

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		cout << scientific;

		int methodType;
		while (cin >> methodType >> ws) {
			Error = 0;
			string statement;
			getline(cin, statement);
			char* polStatement = CreatePolStr(const_cast<char*>(statement.c_str()), 0);
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
				root = findRootByIntervalMethod(polStatement, a, b, eps, IntervalByDichotomyMethod());
				break;
			case 2:
				// Метод хорд
				root = findRootByIntervalMethod(polStatement, a, b, eps, IntervalByChordsMethod());
				break;
			case 3:
				// Метод Ньютона

				break;
			case 4:
				// Комбинированный метод

				break;
			case 5:
				// Метод итераций

				break;
			case 6:
				// Метод золотого сечения
				root = findRootByIntervalMethod(polStatement, a, b, eps, IntervalByGoldenSectionMethod());
				break;
			}
			if (Error)
				cout << "Error: " << Error << '\n';
			else
				cout << root << '\n';
			delete[] polStatement;
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif