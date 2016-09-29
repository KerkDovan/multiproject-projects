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

	inline int gcd(int a, int b) {
		while (b) {
			a %= b;
			swap(a, b);
		}
		return a;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int n;
		while (cin >> n >> ws) {
			while (n--) {
				string line;
				getline(cin, line);
				line += ' ';
				vector<int> numbers;
				int num = 0;
				for (char c : line) {
					if (c >= '0' && c <= '9')
						num = num * 10 + c - '0';
					else if (num > 0) {
						numbers.push_back(num);
						num = 0;
					}
				}
				int g = -1;
				for (size_t i = 0; i < numbers.size(); ++i)
					for (size_t j = 0; j < numbers.size(); ++j)
						if (i != j)
							g = max(g, gcd(numbers[i], numbers[j]));
				cout << g << '\n';
			}
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif