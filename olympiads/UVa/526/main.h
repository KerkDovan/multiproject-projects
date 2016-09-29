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

	string line[2] = { "", "" };
	vector<vector<int>> dp_mem;

	int dp(size_t n1, size_t n2) {
		if (!~n1 || !~n2)
			return 0;
		if (~dp_mem[n1][n2])
			return dp_mem[n1][n2];
		if (line[0][n1] == line[1][n2])
			return dp_mem[n1][n2] = dp(n1 - 1, n2 - 1) + 1;
		return dp_mem[n1][n2] = max(dp(n1 - 1, n2), dp(n1, n2 - 1));
	}

	template<class _Ty>
	bool in_list(const initializer_list<_Ty>& list, const _Ty& what) {
		for (const auto& el : list)
			if (el == what)
				return true;
		return false;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		bool not_first_test = false;
		while (getline(cin, line[0]), getline(cin, line[1]), line[0] != "") {
			if (not_first_test)
				cout << '\n';

			only_multiproject(
				cout << line[0] << '\n' << line[1] << '\n';
			)

			size_t n1 = line[0].size(), n2 = line[1].size();
			dp_mem.resize(n1, vector<int>(n2, -1));
			cout << (--n1, --n2, max(n1, n2) - dp(n1, n2) + 1) << '\n';
			vector<pair<size_t, size_t>> path;

			while (~n1 && ~n2) {
				if (line[0][n1] == line[1][n2] && (path.empty()
					|| n1 != path.back().first && n2 != path.back().second)) {
					path.emplace_back(n1, n2);
				}
				if (n1 && n2 && dp_mem[n1 - 1][n2] >= dp_mem[n1][n2 - 1] 
					&& ~dp_mem[n1 - 1][n2])
					--n1;
				else if (n1 && n2 && ~dp_mem[n1][n2 - 1])
					--n2;
				else
					--n1, --n2;
			}

			n1 = line[0].size() - 1;
			n2 = line[1].size() - 1;
			size_t p = 0;
			size_t cmd = 0;
			queue<size_t> todo[2];
			while (p < path.size() || path.empty()) {
				while (path.size() && p != path.size() && ~n1 && ~n2
					&& path[p].first == n1 && path[p].second == n2)
					++p, --n1, --n2;
				if (!~n1 && !~n2)
					break;

				while (~n1 && (p < path.size() && n1 != path[p].first || p >= path.size()))
					todo[0].push(n1--);
				while (~n2 && (p < path.size() && n2 != path[p].second || p >= path.size()))
					todo[1].push(n2--);

				while (!todo[0].empty() && !todo[1].empty()) {
					cout << ++cmd << " Replace " << todo[0].front() + 1 << ',' << line[1][todo[1].front()] << '\n';
					todo[0].pop();
					todo[1].pop();
				}
				while (!todo[0].empty()) {
					cout << ++cmd << " Delete " << todo[0].front() + 1 << '\n';
					todo[0].pop();
				}
				while (!todo[1].empty()) {
					cout << ++cmd << " Insert " << n1 + 2 << ',' << line[1][todo[1].front()] << '\n';
					todo[1].pop();
				}

				if (path.empty())
					break;

				++p;
				--n1;
				--n2;
			}

			not_first_test = true;
			dp_mem.clear();
			line[0] = "";
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif