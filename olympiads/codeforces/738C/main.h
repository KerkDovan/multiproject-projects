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
#include <memory>
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
#define freopen_in(filename) freopen(filename, "r", stdin)
#define freopen_out(filename) freopen(filename, "w", stdout)
#define close_files

	struct MultiprojectDebug {
		template<class _Ty> friend MultiprojectDebug&
		operator << (MultiprojectDebug& db, const _Ty&) { return db; }
	} debug;

#endif

// Changeable code continues here. 

	using namespace std;

	typedef long long ll;
	typedef unsigned long long ull;

	struct Car {
		int cost, volume;
		bool operator < (const Car& rhs) const {
			return cost < rhs.cost || cost == rhs.cost && volume >= rhs.volume;
		}
	};

	const int INF = 2 * 1000 * 1000 * 1000;

	set<int> stations;
	int t;

	int enough(const Car& car) {
		auto cur = stations.begin();
		int prev = 0;
		int time = 0;
		while (cur != stations.end()) {
			int dist = *cur - prev;
			if (dist > car.volume)
				return INF;
			int rest = car.volume - dist;
			int tmp = 2 * dist - min(rest, dist);
			time += tmp;
			prev = *cur;
			++cur;
		}
		return time <= t ? car.cost : INF;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int n, k, s;
		while (cin >> n >> k >> s >> t) {
			stations.clear();
			set<Car> cars;
			Car tmp;
			for (int i = 0; i < n; ++i) {
				cin >> tmp.cost >> tmp.volume;
				cars.emplace(tmp);
			}
			for (int i = 0; i < k; ++i) {
				int st;
				cin >> st;
				stations.emplace(st);
			}
			stations.emplace(s);
			int minC = INF;
			for (const Car& car : cars) {
				minC = min(minC, enough(car));
				if (minC != INF)
					break;
			}
			if (minC == INF)
				minC = -1;
			cout << minC << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
