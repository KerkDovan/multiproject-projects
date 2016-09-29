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

	vector<tuple<ull, ull, ull>> precounted;

	inline bool isPiphagor(ull a, ull b, ull c) {
		return a == b + c;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		precounted.emplace_back(3, 4, 5);
		precounted.emplace_back(4, 3, 5);
		precounted.emplace_back(5, 3, 4);
		precounted.emplace_back(12, 5, 13);
		precounted.emplace_back(13, 5, 12);
		precounted.emplace_back(17, 144, 145);
		precounted.emplace_back(144, 17, 145);
		precounted.emplace_back(145, 17, 144);
		precounted.emplace_back(67, 2244, 2245);
		precounted.emplace_back(2244, 67, 2245);
		precounted.emplace_back(2245, 67, 2244);

		ull a;
		while (cin >> a) {
			if (a == 1) {
				cout << -1;
			}
			else {
				bool solved = false;
				for (auto t : precounted) {
					if (a % get<0>(t) == 0) {
						ull d = a / get<0>(t);
						cout << d * get<1>(t) << ' ' << d * get<2>(t);
						solved = true;
						break;
					}
				}
				if (a ^ 1)
					cout << -1;
				else if (!solved) {

					for (ull i = 7; i < a; i += 2) {
						if (isPiphagor(a * a, i * i, a * a - i * i)) {

						}
					}

					if (!solved)
						cout << -1;
				}
			}
			cout << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif