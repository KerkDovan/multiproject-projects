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

	const ull MAX_SUM = 7490;
	const vector<ull> coins = { 1, 5, 10, 25, 50 };
	vector<vector<ull>> dp_mem;

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		dp_mem.resize(coins.size(), vector<ull>(MAX_SUM, 0));
		dp_mem[0][0] = 1;

		for (size_t i = 0; i < MAX_SUM; ++i) {
			for (size_t j = 0; j < coins.size(); ++j) {
				for (size_t k = j; k < coins.size(); ++k) {
					if (i + coins[k] < MAX_SUM)
						dp_mem[k][i + coins[k]] += dp_mem[j][i];
				}
			}
		}

		//debug_output("", format_debug(dp_res, FormatVector<ull>("\ndp_mem[%i]\t == %e")));

		size_t n;
		while (cin >> n) {
			ull answer = 0;
			for (auto& i : dp_mem)
				answer += i[n];
			cout << answer << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif