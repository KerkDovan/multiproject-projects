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

	const int MAXCOUNT = 100001;

	int citiesCount;
	int roadsCount;
	int stocksCount;
	vector<vector<pair<int, int>>> roads;
	bitset<MAXCOUNT> stocks;

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> citiesCount >> roadsCount >> stocksCount) {
			roads.clear();
			roads.resize(citiesCount + 1);
			only_multiproject(
			for (int i = 0; i <= citiesCount; ++i)
				roads[i] = vector<pair<int, int>>();
			stocks.reset();
			)
			for (int i = 0; i < roadsCount; ++i) {
				int a, b, l;
				cin >> a >> b >> l;
				roads[a].emplace_back(b, l);
				roads[b].emplace_back(a, l);
			}
			for (int i = 0; i < stocksCount; ++i) {
				int stock;
				cin >> stock;
				stocks[stock] = true;
			}

			int minPath = 1 << 30;
			for (int i = 0; i < citiesCount; ++i) {
				for (auto& road : roads[i]) {
					if (stocks[i] == stocks[road.first])
						continue;
					minPath = min(minPath, road.second);
				}
			}

			cout << (minPath == 1 << 30 ? -1 : minPath) << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif