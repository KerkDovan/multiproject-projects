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

	const int INF = 1 << 30;

	int cnt;
	vector<int> wgts;
	int dp_mem[20000];

	inline int max_t(int a, int b, int c) {
		return max(max(a, b), c);
	}

	inline int min_t(int a, int b, int c) {
		return min(min(a, b), c);
	}

	int dp(int pos, bool three) {
		if (pos == -1)
			return 0;
		if (pos - 1 - three < 0)
			return INF;
		if (~dp_mem[pos * 2 + three])
			return dp_mem[pos * 2 + three];


		int disunity = min(dp(pos - 2 - three, false), dp(pos - 2 - three, true));
		if (disunity == INF)
			return dp_mem[pos * 2 + three] = INF;


		if (three)
			disunity += max_t(wgts[pos], wgts[pos - 1], wgts[pos - 2])
			- min_t(wgts[pos], wgts[pos - 1], wgts[pos - 2]);
		else
			disunity += max(wgts[pos], wgts[pos - 1]) - min(wgts[pos], wgts[pos - 1]);


		return dp_mem[pos * 2 + three] = disunity;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> cnt) {
			wgts.clear();
			wgts.resize(cnt);
			for (int i = 0; i < cnt; ++i)
				cin >> wgts[i];
			sort(wgts.begin(), wgts.end());
			memset(dp_mem, -1, sizeof(int) * 2 * cnt);
			cout << min(dp(cnt - 1, false), dp(cnt - 1, true)) << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif