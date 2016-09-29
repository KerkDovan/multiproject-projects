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

	const int UNDEFINED = -2;
	const int IMPOSSIBLE = -1;

	int linesCount;
	vector<int> energies;
	vector<vector<string>> strings;
	vector<vector<int>> dp_mem;

	int dp(int cur, bool reversed) {
		if (cur == linesCount - 1)
			return reversed ? energies[cur] : 0;
		int& result = dp_mem[cur][reversed];
		if (result != UNDEFINED)
			return result;
		result = 1 << 30;
		for (int rev = 0; rev != 2; ++rev) {
			int nxt_res;
			if (strings[cur][reversed] < strings[cur + 1][rev]) {
				nxt_res = dp(cur + 1, rev == 1);
				if (nxt_res != IMPOSSIBLE)
					result = min(result, nxt_res);
			}
		}
		if (result == 1 << 30)
			return result = IMPOSSIBLE;
		return result += reversed ? energies[cur] : 0;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> linesCount) {
			++linesCount;
			energies.assign(linesCount, 0);
			strings.assign(linesCount, vector<string>(2));
			dp_mem.assign(linesCount, vector<int>(2));
			for (int i = 0; i < linesCount; ++i)
				dp_mem[i][0] = dp_mem[i][1] = UNDEFINED;
			for (int i = 1; i < linesCount; ++i)
				cin >> energies[i];
			for (int i = 1; i < linesCount; ++i) {
				cin >> strings[i][0];
				strings[i][1] = strings[i][0];
				reverse(strings[i][1].begin(), strings[i][1].end());
			}
			cout << dp(0, 0) << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif