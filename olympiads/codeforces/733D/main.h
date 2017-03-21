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

	struct Marble {
		size_t id;
		int a, b, c; // a <= b <= c
		Marble() {}
		Marble(size_t i, int x, int y, int z) {
			id = i;
			a = min({ x, y, z });
			c = max({ x, y, z });
			b = x ^ y ^ z ^ a ^ c;
		}
		int operator [] (size_t i) const {
			return i %= 3, i == 0 ? a : i == 1 ? b : c;
		}
	};

	int getVolume(const Marble& a) {
		return min({ a[0], a[1], a[2] });
	}

	int getVolume(const Marble& a, const Marble& b) {
		int result = -1;
		for (size_t i = 0; i < 3; ++i) {
			for (size_t j = 0; j < 3; ++j) {
				if (i == j)
					continue;
				for (size_t k = 0; k < 3; ++k) {
					for (size_t l = 0; l < 3; ++l) {
						if (k == l)
							continue;
						if (a[i] == b[k] && a[j] == b[l])
							result = max(result,
								min({ a[i], a[j],
								a[0 ^ 1 ^ 2 ^ i ^ j] +
								b[0 ^ 1 ^ 2 ^ k ^ l] }));
					}
				}
			}
		}
		return result;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t n;
		while (cin >> n) {
			vector<Marble> marbles(n);
			multimap<pair<int, int>, Marble*> sides;
			int maxVolume = 0;
			size_t goodMarble;
			for (size_t i = 0; i < n; ++i) {
				int a, b, c;
				cin >> a >> b >> c;
				marbles[i] = Marble(i + 1, a, b, c);
				sides.emplace(make_pair(marbles[i].a, marbles[i].b), &marbles[i]);
				sides.emplace(make_pair(marbles[i].b, marbles[i].c), &marbles[i]);
				sides.emplace(make_pair(marbles[i].a, marbles[i].c), &marbles[i]);
				int tmpVolume = getVolume(marbles[i]);
				if (tmpVolume > maxVolume) {
					maxVolume = tmpVolume;
					goodMarble = i + 1;
				}
			}
			pair<size_t, size_t> goodPair;
			bool pairExists = false;
			for (const auto& marble : marbles) {
				auto range = sides.equal_range(make_pair(marble.b, marble.c));
				for (auto iter = range.first; iter != range.second; ++iter) {
					if (iter->second->id == marble.id)
						continue;
					int tmpVolume = getVolume(marble, *iter->second);
					if (tmpVolume > maxVolume) {
						maxVolume = tmpVolume;
						goodPair = make_pair(iter->second->id, marble.id);
						pairExists = true;
					}
				}
			}
			if (pairExists)
				cout << "2\n" << goodPair.first << ' ' << goodPair.second << '\n';
			else
				cout << "1\n" << goodMarble << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
