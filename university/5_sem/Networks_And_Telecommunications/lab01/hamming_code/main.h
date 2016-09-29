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

		ull number;
		while (cin >> number) {
			cout << number << '\n';
			vector<bool> hamming_code;
			string tmp;
			size_t max_i = 1;
			size_t i = 0;
			while (++i, number) {
				if ((i & (i - 1)) == 0) {
					hamming_code.push_back(0);
					tmp += 'X';
					max_i <<= 1;
				}
				else {
					hamming_code.push_back(number & 1);
					cout << (number & 1);
					tmp += (number & 1) + '0';
					number >>= 1;
				}
			}
			cout << '\n';
			cout << tmp << '\n';
			i = 1;
			while (i != max_i) {
				size_t cur = i - 1;
				bool sum = 0;
				while (cur < hamming_code.size()) {
					for (size_t j = 0; j < i && cur + j < hamming_code.size(); ++j)
						sum ^= hamming_code[cur + j];
					cur += i << 1;
				}
				hamming_code[i - 1] = sum;
				i <<= 1;
			}
			for (bool b : hamming_code)
				cout << b;
			cout << "\n\n";
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif