﻿// Changeable code starts here. 

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

	typedef long long ll;
	typedef unsigned long long ull;



	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int n, k, cnt[2];
		while (cin >> n >> k >> cnt[0] >> cnt[1]) {
			vector<int> answer(n + 1, 0);
			int start_from = cnt[1] > cnt[0];
			int cur = start_from, total = 0;
			while (cur <= n && (cnt[0] > 0 || cnt[1] > 0)) {
				if (cur > start_from && answer[cur - 1] == 0)
					break;
				int tmp = min(k, cnt[cur & 1]);
				answer[cur] += tmp;
				cnt[cur & 1] -= tmp;
				total += tmp;
				++cur;
			}
			if (total < n || cnt[0] < 0 || cnt[1] < 0)
				cout << "NO";
			else {
				for (int i = start_from; i < cur + start_from; ++i) {
					char tea = i & 1 ? 'B' : 'G';
					for (int j = 0; j < answer[i]; ++j)
						cout << tea;
				}
			}
			cout << "\n";
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
