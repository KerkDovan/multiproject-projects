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

		int n, c;
		while (cin >> n >> c) {
			vector<int> p(n), s(n);
			set<int> r; // remaining
			for (int i = 0; i < n; ++i)
				cin >> p[i];
			for (int i = 0; i < n; ++i) {
				cin >> s[i];
				if (s[i] != 0)
					r.emplace(i);
			}
			ull sum = 0;
			set<int>::iterator iter;
			for (int i = n - 1; i != -1; --i) {
				int j = i;
				while (true) {
					iter = r.upper_bound(j);
					if (iter != r.end())
						j = *iter;
					if (p[i] == 0 || iter == r.end() || j == i)
						break;
					int t = min({ p[i], s[j], c });
					p[i] -= t;
					s[j] -= t;
					if (s[j] == 0)
						r.erase(j);
					sum += t;
				}
				if (p[i] != 0) {
					int t = min(p[i], s[i]);
					p[i] -= t;
					s[i] -= t;
					if (s[i] == 0)
						r.erase(i);
					sum += t;
				}
			}
			cout << sum << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
