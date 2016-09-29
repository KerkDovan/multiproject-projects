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

	const double EPS = 1e-4;
	const double INF = 1e10;

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		cout << fixed << setprecision(4);

		size_t cnt;
		vector<double> arr;
		while (cin >> cnt) {
			arr.clear();
			arr.resize(cnt);
			double max_val = -INF;
			int max_id;
			double prdct = 1.0;
			bool z = true, fz = false;
			for (size_t i = 0; i < cnt; ++i) {
				cin >> arr[i];
				if (arr[i] > max_val) {
					max_val = arr[i];
					max_id = i;
				}
				if (z) {
					if (fabs(arr[i]) < EPS) {
						if (fz)
							z = false;
						else
							fz = true;
					}
					else if (fz)
						prdct *= arr[i];
				}
			}
			cout << max_id + 1 << '\n';
			cout << prdct << '\n';
			for (size_t i = 0; i < cnt; i += 2) {
				if (i)
					cout << ' ';
				cout << arr[i];
			}
			for (size_t i = 1; i < cnt; i += 2) {
				cout << ' ' << arr[i];
			}
			cout << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif