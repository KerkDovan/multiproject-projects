// Changeable code starts here. 

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <algorithm>
#include <array>
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
#ifdef MYLIB
	using namespace MyLib;
#endif // MYLIB

	typedef long long ll;
	typedef unsigned long long ull;

	int main() {
		freopen_in("input.txt");
		freopen_out("output.txt");

		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t test_count;
		cin >> test_count;
		for (size_t test = 0; test < test_count; ++test) {
			size_t cnt;
			double len;
			cin >> cnt >> len;
			len *= 1e3; // km -> m

			priority_queue<pair<double, double>> extgshrs; // <a, t>

			for (size_t i = 0; i < cnt; ++i) {
				static double a, t;
				cin >> a >> t;
				extgshrs.push(make_pair(a, t * 1e-6)); // (m/sec, mcsec -> sec)
			}

			double s = len, t = 0.0, v = 0.0;
			for (size_t i = 0; i < cnt; ++i) {
				double ta, tt;
				tie(ta, tt) = extgshrs.top();
				extgshrs.pop();
				double ds = tt * (v + ta * tt * 0.5);
				if (ds > s) {
					t += (-v + sqrt(v * v + 2.0 * ta * s)) / ta;
					s = 0.0;
					break;
				}
				s -= ds;
				t += tt;
				v += ta * tt;
			}
			if (fabs(s) > 1e-10)
				t += s / v;
			
			cout << fixed << setprecision(10) << t << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
