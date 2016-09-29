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

	vector<string> t[2];
	vector<vector<size_t>> dp_mem;

	int dp(size_t n1, size_t n2) {
		if (n1 == -1 || n2 == -1)
			return 0;
		if (~dp_mem[n1][n2])
			return dp_mem[n1][n2];
		if (t[0][n1] == t[1][n2])
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

		string tmp;
		bool cur = 0;
		while (cin >> tmp, tmp != "") {
			if (tmp == "#") {
				if (cur) {
					size_t n1 = t[0].size(), n2 = t[1].size();
					dp_mem.resize(n1, vector<size_t>(n2, -1));
					dp(--n1, --n2);
					stack<size_t> path;
					while (n1 != -1 && n2 != -1) {
						if (t[0][n1] == t[1][n2] && (path.empty() || path.top() != n1))
							path.push(n1);
						if (n1 && dp_mem[n1 - 1][n2] >= dp_mem[n1][n2 - 1]
							&& dp_mem[n1 - 1][n2] != -1)
							--n1;
						else if (n2 && dp_mem[n1][n2 - 1] != -1)
							--n2;
						else
							--n1, --n2;
					}
					while (path.size()) {
						cout << t[0][path.top()];
						path.pop();
						if (path.size())
							cout << ' ';
					}
					cout << '\n';
					t[0].clear();
					t[1].clear();
					dp_mem.clear();
				}
				cur = !cur;
			}
			else
				t[cur].push_back(tmp);
			tmp = "";
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif