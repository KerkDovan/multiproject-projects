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

	int side;
	int matrix[100][100];
	int sums[100][100];
	int dp_mem[100][100];

	int dp(int x, int y) {
		sums[x][y] = matrix[x][y]
			+ (x != 0 ? sums[x - 1][y] : 0)
			+ (y != 0 ? (sums[x][y - 1]
				- (x != 0 ? sums[x - 1][y - 1] : 0)
			) : 0);

		int max_sum = -1000 * 1000 * 1000;

		for (int i = 0; i <= y; ++i) {
			for (int j = 0; j <= x; ++j) {
				int tmp_sum = sums[x][y]
					- (j != 0 ? sums[j - 1][y] : 0)
					- (i != 0 ? (sums[x][i - 1]
						- (j != 0 ? sums[j - 1][i - 1] : 0)
					) : 0);
				max_sum = max(max_sum, tmp_sum);
			}
		}

		return dp_mem[x][y] = max_sum;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> side) {
			int max_sum = -1000 * 1000 * 1000;
			only_multiproject(memset(dp_mem, 0, sizeof(dp_mem)));
			for (int y = 0; y < side; ++y) {
				for (int x = 0; x < side; ++x) {
					cin >> matrix[x][y];
					max_sum = max(max_sum, dp(x, y));
				}
			}
			cout << max_sum << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif