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

	typedef long long ll;
	typedef unsigned long long ull;

	inline void buy(int n) {
		cout << "BUY ON DAY " << n << '\n';
	}

	inline void sell(int n) {
		cout << "SELL ON DAY " << n << '\n';
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int m, n, k;
		bool first_test = true;
		while (cin >> m >> n >> k) {
			if (!first_test)
				cout << '\n';
			else
				first_test = false;

			double pm = 0.0, pn = 0.0;
			double* ps = new double[n];

			for (int i = 0; i < n; ++i) {
				cin >> ps[i];
				if (i >= n - m)
					pm += ps[i];
				pn += ps[i];
			}
			pm /= m;
			pn /= n;

			bool bought = pm > pn ? (buy(n), true) : (sell(n), false);

			for (int i = n; i < k; ++i) {
				double p;
				cin >> p;
				pm = (pm * m + p - ps[(i - m) % n]) / m;
				pn = (pn * n + p - ps[(i - n) % n]) / n;
				ps[i % n] = p;
				if (bought != pm > pn)
					pm > pn ? buy(i + 1) : sell(i + 1), bought = !bought;
			}

			delete[] ps;
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
