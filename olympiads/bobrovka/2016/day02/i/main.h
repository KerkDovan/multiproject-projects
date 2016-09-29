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

	inline bool is_zero(double x) {
		return x <= 1e-7;
	}

	struct Point {
		double x, y;
		inline double dist_to(const Point& p) const {
			return hypot(p.x - x, p.y - y);
		}
	};

	size_t t_count;
	vector<Point> towers;
	vector<vector<double>> distances;

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("i.in");
		freopen_out("i.out");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> t_count) {
			towers.resize(t_count);
			for (size_t i = 0; i < t_count; ++i)
				cin >> towers[i].x >> towers[i].y;

			distances.resize(t_count, vector<double>(t_count));
			for (size_t i = 0; i < t_count; ++i)
				for (size_t j = i; j < t_count; ++j)
					distances[i][j] = distances[j][i] = towers[i].dist_to(towers[j]);

			queue<size_t> que;
			bitset<5000> visited(0);
			vector<set<size_t>> areas;
			while (visited.count() != t_count) {
				areas.push_back(set<size_t>());
				for (size_t i = 0; i < t_count; ++i) {
					if (!visited[i]) {
						que.push(i);
						visited[i] = true;
						areas.back().insert(i);
						break;
					}
				}
				while (!que.empty()) {
					size_t cur = que.front();
					que.pop();
					for (size_t i = 0; i < t_count; ++i) {
						if (!visited[i] && distances[cur][i] <= 2.0) {
							que.push(i);
							visited[i] = true;
							areas.back().insert(i);
						}
					}
				}
			}
			sort(areas.begin(), areas.end(),
				[&](const set<size_t>& a, const set<size_t>& b) {
				return a.size() > b.size();
			}
			);
			size_t cnt = 0, a = -1, b;
			for (size_t i = 0; i < areas.size(); ++i) {
				for (size_t j = 0; j < areas.size(); ++j) {
					for (size_t k : areas[i]) {
						for (size_t l : areas[j]) {
							if (distances[k][l] <= 4.0) {
								cnt = areas[i].size() + areas[j].size() + 1;
								a = i;
								b = j;
							}
							if (cnt)
								break;
						}
						if (cnt)
							break;
					}
					if (cnt)
						break;
				}
				if (cnt)
					break;
			}

			if (~a) {
				set<size_t> common;
				for (size_t i : areas[a]) {
					for (size_t j : areas[b]) {
						if (distances[i][j] <= 4.0) {
							common.insert(i);
							common.insert(j);
						}
					}
				}

				bool found = false;
				for (size_t i = 0; i < areas.size(); ++i) {
					if (i == a || i == b)
						continue;
					for (size_t j : common) {
						for (size_t k : areas[i]) {
							if (distances[k][j] <= 4.0) {
								cnt += areas[i].size();
								found = true;
								break;
							}
						}
						if (found)
							break;
					}
					if (found)
						break;
				}
			}
			else
				cnt = areas[0].size() + 1;

			cout << cnt << '\n';

		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif