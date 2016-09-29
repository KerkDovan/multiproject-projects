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

	double f1(double p, double v, double W) {
		return p * log(1.0 + v / W);
	}

	double f2(double v, double W) {
		return W * (exp(v) - 1.0);
	}

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("a.in");
		freopen_out("a.out");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int count;
		double W;
		while (cin >> count >> W) {
			string safety;
			double p, v;
			double max_h = 0.0;
			for (int i = 0; i < count; ++i) {
				cin >> safety >> p >> v;
				bool safe = safety == "safe";

				max_h = max(max_h, 0.0);
			}
			cout << '$' << fixed << setprecision(2) << max_h << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif