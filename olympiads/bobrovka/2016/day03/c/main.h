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

	ull dp_mem[33][33];

	ull dp(int tries, int eggs) {
		if (!eggs)
			return 0;
		if (~dp_mem[tries][eggs])
			return dp_mem[tries][eggs];
		ull& result = dp_mem[tries][eggs];
		if (tries == 1 && eggs >= tries)
			result = 1;
		else //if (tries > eggs)
			result = 1 + dp(tries - 1, eggs - 1) + dp(tries - 1, eggs);
		return result;
	}

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("c.in");
		freopen_out("c.out");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		memset(dp_mem, -1, sizeof(dp_mem));

		//for (int i = 1; i <= 32; ++i) {
		//	//cout << i << ":";
		//	for (int j = 1; j <= 32; ++j)
		//		//cout << "\t\t" << dp(i, j);
		//		dp(i, j);
		//	//cout << '\n';
		//}

		int testCount;
		cin >> testCount;
		for (int test = 0; test < testCount; ++test) {
			int floorsCount, eggsCount;
			cin >> floorsCount >> eggsCount;
			int left = 1, middle, right = 33;
			while (left < right) {
				middle = (left + right) >> 1;
				if (dp(middle, eggsCount) >= floorsCount)
					right = middle;
				else
					left = middle + 1;
			}
			if (left > 32)
				cout << "Impossible\n";
			else
				cout << left << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif