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

	enum Color { clWhite = 0, clBlue, clRed, };

	ull dp_mem[46][3][3];

	ull dp(int len, Color cur, Color prev) {
		ull& result = dp_mem[len][cur][prev];
		if (~result)
			return result;
		if (len == 1)
			return result = cur != clBlue;

		result = 0;

		if (cur != clBlue)
			result += dp(len - 1, clBlue, cur)
				+ dp(len - 1, cur == clRed ? clWhite : clRed, cur);
		else
			result += dp(len - 1, prev == clRed ? clWhite : clRed, cur);

		return result;
	}

	ull fib_mem[46];

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		memset(dp_mem, -1, sizeof(dp_mem));

		fib_mem[0] = 0;
		fib_mem[1] = 1;
		for (int i = 2; i < 46; ++i)
			fib_mem[i] = fib_mem[i - 2] + fib_mem[i - 1];

		int cnt;
		while (cin >> cnt) {
			//cout << fib_mem[cnt] * 2 << '\n';
			cout << dp(cnt, clRed, clBlue) + dp(cnt, clWhite, clBlue) << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif