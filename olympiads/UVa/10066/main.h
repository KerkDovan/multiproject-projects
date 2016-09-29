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

	vector<int> t[2];
	vector<vector<int>> dp_mem;

	int dp(int n1, int n2) {
		if (!~n1 || !~n2)
			return 0;
		if (~dp_mem[n1][n2])
			return dp_mem[n1][n2];
		if (t[0][n1] == t[1][n2])
			return dp_mem[n1][n2] = dp(n1 - 1, n2 - 1) + 1;
		return dp_mem[n1][n2] = max(dp(n1 - 1, n2), dp(n1, n2 - 1));
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int test = 0, h[2] = { 0, 0 };
		while (cin >> h[0] >> h[1], h[0] || h[1]) {
			for (int i = 0; i < 2; ++i) {
				t[i].resize(h[i]);
				for (int j = 0; j < h[i]; ++j)
					cin >> t[i][j];
			}
			dp_mem.resize(h[0], vector<int>(h[1], -1));
			cout << "Twin Towers #" << ++test << "\nNumber of Tiles : "
				<< dp(h[0] - 1, h[1] - 1) << "\n\n";
			dp_mem.clear();
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif