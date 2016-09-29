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

	const size_t MAXDAYSCOUNT = 101;

	size_t daysCount;
	struct {
		bitset<2 * MAXDAYSCOUNT> _data;
		inline bool contest(size_t day) { return _data[(day << 1) + 0]; }
		inline bool sport(size_t day) { return _data[(day << 1) + 1]; }
	} activities;
	
	size_t dp_mem[MAXDAYSCOUNT][3];

	size_t dp(size_t cur, short activity) {
		if (cur == daysCount)
			return (size_t)(activity == 2);
		size_t& result = dp_mem[cur][activity];
		if (~result)
			return result;
		if (activity == 0) { // contest
			if (activities.sport(cur + 1))
				result = min(result, dp(cur + 1, 1));
		}
		else if (activity == 1) { // sport
			if (activities.contest(cur + 1))
				result = min(result, dp(cur + 1, 0));
		}
		else { // doing nothing
			if (activities.contest(cur + 1))
				result = min(result, dp(cur + 1, 0));
			if (activities.sport(cur + 1))
				result = min(result, dp(cur + 1, 1));
		}
		result = min(result, dp(cur + 1, 2)) + (size_t)(activity == 2);
		return result;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> daysCount) {
			activities._data.reset();
			for (size_t i = 1; i <= daysCount; ++i) {
				short activity;
				cin >> activity;
				activities._data[(i << 1) + 0] = (activity & 1) != 0;
				activities._data[(i << 1) + 1] = (activity & 2) != 0;
			}
			memset(dp_mem, -1, sizeof(dp_mem));
			cout << dp(0, 2) - 1 << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif