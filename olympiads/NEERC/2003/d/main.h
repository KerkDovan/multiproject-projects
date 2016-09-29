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

	ull asize, psize, qsize;

	inline ull qdiff(ull a, ull b) {
		return (psize + (psize << a)) >> b;
	}

	inline ull poff(ull a, ull b) {
		return psize * (asize - 1);
	}

	inline ull qoff(ull a, ull b) {
		return (poff(a, b) + (poff(a, b) << a)) >> b;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> asize >> psize >> qsize) {
			static const ull inf = (ull)1 << (ull)60;
			ull mink = inf, mina, minb;
			for (ull i = 31; i != -1; --i) {
				for (ull j = 31; j != -1; --j) {
					ull tmpdiff = qdiff(i, j);
					ull tmpoff = qoff(i, j);
					if (tmpdiff >= qsize && tmpoff <= mink) {
						mink = tmpoff;
						mina = i;
						minb = j;
					}
				}
			}
			cout << mink + qsize << ' ' << mina << ' ' << minb << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif