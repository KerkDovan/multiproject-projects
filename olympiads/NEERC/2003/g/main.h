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
#include <functional>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string.h>
#include <tuple>
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

	

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		vector<vector<pair<int, int>>> sums(200 * 200 + 1); // <<a, b>[]>[sum]
		for (int i = 1; i <= 200; ++i)
			for (int j = i; j <= 200; ++j)
				sums[i + j].emplace_back(i, j);

		function<int(int, int)> turns[2] = {
			[](int a, int b) { return a + b; },
			[](int a, int b) { return a * b; },
		};

		set<pair<int, int>> result;
		set<pair<int, int>> possible;
		bitset<200 * 200 + 1> visited;
		set<pair<int, int>> once;

		int n, m;
		while (cin >> n >> m) {
			result.clear();
			for (int sum = 2; sum <= n * 2; ++sum) {
				possible.clear();
				for (const auto& p : sums[sum])
					possible.insert(p);
				for (int i = 0; i <= m && possible.size(); ++i) {
					visited.reset();
					for (const auto& p : possible)
						once.insert(p);
					for (const auto& p : possible) {
						int tmp = turns[i & 1](p.first, p.second);
						if (visited[tmp])
							once.erase(p);
						visited[tmp] = true;
					}
					if (i < m) {
						for (const auto& p : once)
							possible.erase(p);
						once.clear();
					}
				}
				for (const auto& p : once)
					result.insert(p);
			}
			cout << result.size() << '\n';
			for (const auto& p : result)
				cout << p.first << ' ' << p.second << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif