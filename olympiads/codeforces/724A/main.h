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

	

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		map<string, int> days = {
			{ "monday", 0 },
			{ "tuesday", 1 },
			{ "wednesday", 2 },
			{ "thursday", 3 },
			{ "friday", 4 },
			{ "saturday", 5 },
			{ "sunday", 6 },
		};

		int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		int tmp_result[7][12]; // [first day of the year][month]

		for (int i = 0; i < 7; ++i) {
			int day = i;
			for (int j = 0; j < 12; ++j) {
				tmp_result[i][j] = day;
				day = (day + month[j]) % 7;
			}
		}

		set<pair<int, int>> result;

		for (int i = 0; i < 7; ++i)
			for (int j = 0; j < 11; ++j)
				result.emplace(tmp_result[i][j], tmp_result[i][j + 1]);

		string s1, s2;
		while (cin >> s1 >> s2) {
			if (result.find(make_pair(days[s1], days[s2])) != result.end())
				cout << "YES\n";
			else
				cout << "NO\n";
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
