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

	ull dp_mem[20][11][11];

	ull dp(int length, int base, int digit) {
		ull& result = dp_mem[length][base][digit];
		if (~result)
			return result;
		if (length == 1)
			return result = 1;

		result = 0;
		if (digit != 0)
			result += dp(length - 1, base, 0);
		for (int i = 1; i < base; ++i)
			result += dp(length - 1, base, i);

		return result;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		memset(dp_mem, -1, sizeof(dp_mem));

		int len, base;
		while (cin >> len >> base) {
			cout << dp(len + 1, base, 0) << '\n';
		}
		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif