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

	size_t cnt, k;
	vector<size_t> soldiers;
	vector<bool> effectiveness;
	vector<bool> unq;

	string generate_name(size_t cur) {
		string result = "A";
		while (cur) {
			result += (char)((cur % 26) + 'a');
			cur /= 26;
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

		while (cin >> cnt >> k) {

			soldiers.assign(cnt, 0);
			effectiveness.assign(cnt - k + 1, false);
			unq.assign(cnt, false);

			for (size_t i = 0; i < cnt - k + 1; ++i) {
				string tmp;
				cin >> tmp;
				if (tmp == "YES")
					effectiveness[i] = true;
			}

			for (size_t i = 0; i < cnt; ++i)
				soldiers[i] = i;

			for (size_t i = 0; i < cnt - k + 1; ++i) {
				for (size_t j = 0; j < k; ++j)
					unq[i + j] = unq[i + j] || effectiveness[i];
			}

			size_t cur = 0;
			for (size_t i = 0; i < cnt; ) {
				while (i < cnt && unq[i] == false)
					soldiers[i++] = cur;
				if (i < cnt)
					soldiers[i++] = cur;
				while (i < cnt && unq[i] == true)
					cur = soldiers[i++];
			}

			for (size_t i = 0; i < cnt; ++i) {
				if (i)
					cout << ' ';
				cout << generate_name(soldiers[i]);
			}
			cout << '\n';

		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
