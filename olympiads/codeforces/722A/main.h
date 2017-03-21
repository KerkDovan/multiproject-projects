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

#endif

// Changeable code continues here. 

	using namespace std;

	typedef long long ll;
	typedef unsigned long long ull;

	inline bool correct_h(int type, int h) {
		if (type == 12)
			return h >= 1 && h <= 12;
		else
			return h >= 0 && h <= 23;
	}

	inline bool correct_m(int m) {
		return m >= 0 && m <= 59;
	}

	ostream& print_two(ostream& os, int n) {
		if (n % 100 < 10)
			os << 0 << (n % 10);
		else
			os << (n % 100);
		return os;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		//srand(time(NULL));
		//for (int i = 0; i < 100; ++i) {
		//	int type, h, m;
		//	do {
		//		type = rand() % 2 ? 12 : 24;
		//		h = rand() % 100;
		//		m = rand() % 100;
		//	} while (correct_h(type, h) && correct_m(m));
		//	cout << type << '\n';
		//	print_two(cout, h) << ':';
		//	print_two(cout, m) << '\n';
		//}

		int type, h, m;
		char c;
		while (cin >> type >> h >> c >> m) {
			//only_multiproject(
			//cout << type << ' ';
			//print_two(cout, h) << ':';
			//print_two(cout, m) << ' ';
			//)
			if (!correct_m(m))
				m %= 10;
			if (!correct_h(type, h)) {
				if (type == 12) {
					if (h > 12) {
						if (h < 20)
							h = 12;
						else
							h %= 10;
					}
					if (h == 0)
						h = 1;
				}
				else {
					if (h < 30)
						h = 23;
					else
						h = 10 + h % 10;
				}
			}
			print_two(print_two(cout, h) << c, m) << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif