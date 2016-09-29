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

	struct Predicate {
		int modulo;
		bool operator () (int a, int b) {
			if (a % modulo == b % modulo) {
				if (a & 1 && !(b & 1))
					return true;
				else if (!(a & 1) && b & 1)
					return false;
				else if (a & 1 && b & 1)
					return a > b;
				else
					return a < b;
			}
			return a % modulo < b % modulo;
		}
	};

	int main() {
#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int n, m;
		while (cin >> n >> m, n || m) {
			vector<int> arr(n);
			for (int i = 0; i < n; ++i)
				cin >> arr[i];
			sort(arr.begin(), arr.end(), Predicate{ m });
			cout << n << ' ' << m << '\n';
			for (int el : arr)
				cout << el << '\n';
		}
		cout << "0 0\n";

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif