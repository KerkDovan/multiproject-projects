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

	map<int, pair<int, int>> waves; // <m, <f, w>>
	map<int, int> after_cd; // <m, after_cd_m>
	
	map<int, int> dp_mem;

	int dp(int wave) {
		if (~dp_mem[wave])
			return dp_mem[wave];
		if (!~after_cd[wave])
			return dp_mem[wave] = waves[wave].first;
		return dp_mem[wave] = max(waves[wave].first + dp(after_cd[wave]), 
			dp(waves.upper_bound(wave)->first));
	}

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("j.in");
		freopen_out("j.out");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int count;
		while (cin >> count) {
			waves.clear();
			waves.emplace(-1, make_pair(0, 0));
			dp_mem.clear();
			dp_mem.emplace(-1, -1);
			int m, f, w;
			for (int i = 0; i < count; ++i) {
				cin >> m >> f >> w;
				waves.emplace(m, make_pair(f, w));
				dp_mem.emplace(m, -1);
			}
			auto b = waves.begin();
			++b;
			after_cd.clear();
			after_cd.emplace(-1, b->first);
			for (auto iter = waves.begin(); iter != waves.end(); ++iter) {
				auto after_cd_m = waves.lower_bound(iter->first + iter->second.second);
				if (after_cd_m != waves.end())
					after_cd.emplace(iter->first, after_cd_m->first);
			}
			b = waves.end();
			--b;
			after_cd.emplace_hint(after_cd.end(), make_pair(b->first, -1));

			for (auto iter = waves.begin(); iter != waves.end(); ++iter)
				dp(iter->first);

			cout << dp(-1) << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif