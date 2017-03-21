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

	

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int sz;
		vector<vector<int> > m;
		while (cin >> sz) {
			m.assign(sz, vector<int>(sz));
			m[0][0] = 1;
			bool horz = true;
			bool dir = true;
			int cur = 0;
			int x = -1, y = 0;
			int tmp = sz;
			while (cur < sz * sz) {
				if (horz) {
					if (dir) {
						for (int i = 0; i < tmp; ++i) {
							++x;
							m[x][y] = ++cur;
						}
					}
					else {
						for (int i = 0; i < tmp; ++i) {
							--x;
							m[x][y] = ++cur;
						}
					}
					--tmp;
				}
				else {
					if (dir) {
						for (int i = 0; i < tmp; ++i) {
							++y;
							m[x][y] = ++cur;
						}
					}
					else {
						for (int i = 0; i < tmp; ++i) {
							--y;
							m[x][y] = ++cur;
						}
					}
					dir ^= true;
				}
				horz ^= true;
			}
			for (int i = 0; i < sz; ++i) {
				for (int j = 0; j < sz; ++j) {
					if (j)
						cout << ' ';
					cout << m[j][i];
				}
				cout << '\n';
			}
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif