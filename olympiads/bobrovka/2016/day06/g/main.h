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

	int dp_mem[31][30][30];

	int dp(int n, int m, int k) {
		if (~dp_mem[n][m][k])
			return dp_mem[n][m][k];
		dp_mem[n][m][k] = 0;
		for (int i = 1; i <= n; ++i) {
			if ((i - m) % k == 0)
				continue;
			dp_mem[n][m][k] += dp(n - i, m, k);
		}
		return dp_mem[n][m][k];
	}

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("g.in");
		freopen_out("g.out");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		memset(dp_mem, -1, sizeof(dp_mem));
		for (int i = 0; i < 30; ++i)
			fill_n(dp_mem[0][i], 30, 1);

		int testCount;
		cin >> testCount;
		while (testCount--) {
			int testNumber, n, m, k;
			cin >> testNumber >> n >> m >> k;
			cout << testNumber << ' ' << dp(n, m, k) << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif