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

		int n;
		while (cin >> n) {
			stack<int> stck; // 1
			queue<int> que; // 2
			priority_queue<int> pque; // 4
			int which = 7;
			int c, x;
			for (int i = 0; i < n; ++i) {
				cin >> c >> x;
				if (c == 1) {
					stck.push(x);
					que.push(x);
					pque.push(x);
				}
				else {
					if (stck.size()) {
						if (x != stck.top())
							which &= 2 | 4;
						stck.pop();
					}
					else
						which &= 2 | 4;

					if (que.size()) {
						if (x != que.front())
							which &= 1 | 4;
						que.pop();
					}
					else
						which &= 1 | 4;

					if (pque.size()) {
						if (x != pque.top())
							which &= 1 | 2;
						pque.pop();
					}
					else
						which &= 1 | 2;
				}
			}
			switch (which) {
			case 0: cout << "impossible\n"; break;
			case 1: cout << "stack\n"; break;
			case 2: cout << "queue\n"; break;
			case 4: cout << "priority queue\n"; break;
			default: cout << "not sure\n"; break;
			}
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif