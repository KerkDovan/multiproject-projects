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

	typedef long long ll;
	typedef unsigned long long ull;

	const int INF = 1000 * 1000;

	int n;
	vector<int> nails;
	vector<int> dp_mem;

	int dp(int i) {
		if (i == n)
			return 0;
		if (i >= n - 1)
			return INF;
		if (~dp_mem[i])
			return dp_mem[i];
		dp_mem[i] = dp(i + 2) + nails[i + 1] - nails[i];
		if (i < n - 2)
			dp_mem[i] = min(dp_mem[i], dp(i + 3) + nails[i + 2] - nails[i]);
		return dp_mem[i];
	}

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> n) {
			nails.assign(n, 0);
			dp_mem.assign(n, -1);
			for (int i = 0; i < n; ++i)
				cin >> nails[i];
			sort(nails.begin(), nails.end());
			cout << dp(0) << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
