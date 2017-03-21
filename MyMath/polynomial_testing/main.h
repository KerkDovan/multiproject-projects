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
#include "MyMath\experimental.hpp"

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
	using namespace MyMath::experimental;

	typedef long long ll;
	typedef unsigned long long ull;

	const double NINF = -1e9;
	const double PINF = 1e9;
	const double EPS = 1e-9;

	string toString(double x) {
		string result = to_string(x);
		size_t tz = 0;
		for (auto iter = result.rbegin(); iter != result.rend(); ++iter) {
			if (*iter != '0') {
				if (*iter == '.')
					++tz;
				break;
			}
			++tz;
		}
		result.resize(result.size() - tz);
		return result == "-0" ? "0" : result;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
		
		size_t cnt;
		while (cin >> cnt) {
			cout << "====================================\n\n";
			vector<double> coeffs(cnt);
			for (double& coeff : coeffs)
				cin >> coeff;
			Polynomial<double> p0(coeffs.begin(), coeffs.end());
			vector<Polynomial<double>> p(p0.size());
			for (size_t i = 0; i < p.size(); ++i) {
				p[i] = p0.getDerivative(i);
				cout << p[i].toString(toString) << "\n";
				cout << "roots = { ";
				auto roots = getRoots(p[i], NINF, PINF, EPS, fabs);
				for (auto root : roots)
					cout << root << ", ";
				cout << "}\n\n";
			}
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