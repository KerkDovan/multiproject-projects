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

	typedef long long ll;
	typedef unsigned long long ull;

	

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t students;
		while (cin >> students) {
			// Reading data
			vector<size_t> messages(students);
			size_t sum = 0;
			for (size_t& student : messages) {
				cin >> student;
				sum += student;
			}

			// Checking for "Impossible" answer
			if (sum < students - 1 || messages[0] == 0) {
				cout << "-1\n";
				only_multiproject(cout << '\n');
				continue;
			}
			
			// Auxiliary variables
			multimap<size_t, size_t, greater<size_t>> sorted; // <messages[i], i>
			for (size_t i = 1; i < students; ++i)
				sorted.emplace(messages[i], i);
			queue<size_t> que;
			que.emplace(0);

			// Computing
			cout << students - 1 << '\n';
			while (!que.empty()) {
				size_t cur = que.front();
				que.pop();
				while (messages[cur] > 0 && !sorted.empty()) {
					size_t p = sorted.begin()->second;
					sorted.erase(sorted.begin());
					que.emplace(p);
					cout << cur + 1 << ' ' << p + 1 << '\n';
					--messages[cur];
				}
			}
			only_multiproject(cout << '\n');
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
