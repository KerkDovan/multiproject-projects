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

	const int MODULO = 1000 * 1000 * 1000 + 7;
	int field = 50;
	int special = 5;
	ull dp_mem[41][21][21][21]; // count, white total, white special, black special
	ull dp_res[41];

	ull dp(int cnt, int wt, int ws, int bs) {
		if (cnt == 0)
			return 1;
		if (~dp_mem[cnt][wt][ws][bs])
			return dp_mem[cnt][wt][ws][bs];

		int bt = cnt - wt,
			wu = wt - ws,
			bu = bt - bs,
			free_s = field - cnt,
			free_u = max(free_s - special, 0);
		ull result = 0;

		if (bu > 0) result += free_u * dp(cnt - 1, wt, ws, bs) % MODULO;		// black usual
		if (wu > 0) result += free_u * dp(cnt - 1, wt - 1, ws, bs) % MODULO;	// white usual
		if (ws > 0) result += free_s * dp(cnt - 1, wt, ws - 1, bs) % MODULO;	// white special
		if (bs > 0) result += free_s * dp(cnt - 1, wt, ws, bs - 1) % MODULO;	// black special
		
		return dp_mem[cnt][wt][ws][bs] = result;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		memset(dp_mem, -1, sizeof(dp_mem));
		memset(dp_res, 0, sizeof(dp_res));
		for (int i = 0; i <= 20; ++i)
			for (int j = 0; j <= 20; ++j)
				for (int k = 0; k <= 20; ++k)
						(dp_res[40] += dp(40, i, j, k)) %= MODULO;

		int cnt;
		while (cin >> cnt)
			cout << dp_res[cnt] << '\n';

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
