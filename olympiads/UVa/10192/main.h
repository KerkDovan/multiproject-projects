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

	string s1, s2;

	vector<vector<int>> dp_mem;

	int dp(size_t n1, size_t n2) {
		if (n1 == -1 || n2 == -1)
			return 0;
		if (dp_mem[n1][n2] != -1)
			return dp_mem[n1][n2];
		if (s1[n1] == s2[n2])
			return dp_mem[n1][n2] = dp(n1 - 1, n2 - 1) + 1;
		return dp_mem[n1][n2] = max(dp(n1 - 1, n2), dp(n1, n2 - 1));
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t test = 0;
		while (getline(cin, s1), getline(cin, s2), s1 != "#") {
			dp_mem.resize(s1.size(), vector<int>(s2.size(), -1));
			cout << "Case #" << ++test << ": you can visit at most " 
				<< dp(s1.size() - 1, s2.size() - 1) << " cities.\n";
			s1 = s2 = "";
			dp_mem.clear();
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif