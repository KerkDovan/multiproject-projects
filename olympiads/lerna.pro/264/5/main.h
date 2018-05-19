// Changeable code starts here. 

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <functional>
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

#define stringify(...) stringify2(__VA_ARGS__)
#define stringify2(...) #__VA_ARGS__

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
#ifdef _MULTIPROJECT_PROJECT_CONFIG_H_
#define freopen_in(filename) freopen("project\\" ## filename, "r", stdin)
#define freopen_out(filename) freopen("project\\" ## filename, "w", stdout)
#else
#define freopen_in(filename) freopen(filename, "r", stdin)
#define freopen_out(filename) freopen(filename, "w", stdout)
#endif
#define close_files

	struct MultiprojectDebug {
		template<class _Ty> friend MultiprojectDebug&
		operator << (MultiprojectDebug& db, const _Ty&) { return db; }
	} debug;

#endif

// Changeable code continues here. 

	using namespace std;
#ifdef MYLIB
	using namespace MyLib;
#endif // MYLIB

	typedef long long ll;
	typedef unsigned long long ull;

	

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t n;
		int s, f;
		while (cin >> n >> s >> f) {
			vector<pair<int, int>> drinks;
			pair<int, int> max_pos = { 0, -1 };
			int max_neg = 0;
			for (size_t i = 0; i < n; ++i) {
				int a, b;
				cin >> a >> b;
				if (a - b > 0) {
					if (a > max_pos.second || a == max_pos.second && a - b < max_pos.first) {
						if (max_pos.second != -1)
							drinks.emplace_back(max_pos);
						max_pos = { a - b, a };
					}
					else
						drinks.emplace_back(a - b, a);
				}
				else
					max_neg = max(max_neg, a);
			}

			sort(drinks.begin(), drinks.end(), [](const auto& a, const auto& b) {
				if (a.first > b.first)
					return true;
				if (a.first == b.first)
					return a.second < b.second;
				return false;
			});

			int cnt = 0, sum = s;
			auto iter = drinks.begin();
			while (
				iter != drinks.end() &&
				sum + max_neg < f &&
				sum + max_pos.second < f &&
				sum + max_pos.first + max_neg < f
			) {
				if (sum + iter->second >= f) {
					sum += iter->second;
					++cnt;
					break;
				}
				sum += iter->first;
				++cnt;
				++iter;
			}
			if (sum < f) {
				if (sum + max_neg >= f) {
					sum += max_neg;
				}
				else if (sum + max_pos.second >= f) {
					sum += max_pos.second;
				}
				else {
					sum += max_pos.first + max_neg;
					++cnt;
				}
				++cnt;
			}

			cout << (sum < f ? -1 : cnt) << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
