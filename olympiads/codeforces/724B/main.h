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

	struct MultiprojectDebug {
		template<class _Ty> friend MultiprojectDebug&
		operator << (MultiprojectDebug& db, const _Ty&) { return db; }
	} debug;

#endif

// Changeable code continues here. 

	using namespace std;

	typedef long long ll;
	typedef unsigned long long ull;

	int maxdiff(const vector<vector<int>>& m, size_t k, size_t l) {
		int result = 0;
		for (size_t i = 0; i < m.size(); ++i) {
			int tmp = 0;
			vector<int> t = m[i];
			sort(t.begin(), t.end());
			for (size_t j = 0; j < m[i].size(); ++j)
				tmp += m[i][j] != t[j] && j != k && j != l;
			result = max(result, tmp);
		}
		return result;
	}

	bool trythis(vector<vector<int>> m, size_t k, size_t l, bool before) {
		if (before) {
			for (size_t i = 0; i < m.size(); ++i)
				swap(m[i][k], m[i][l]);
			return maxdiff(m, -1, -1) <= 2;
		}
		else
			return maxdiff(m, k, l) <= 2;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int n, m;
		while (cin >> n >> m) {
			vector<vector<int>> matrix(n, vector<int>(m));
			for (auto& line : matrix)
				for (int& el : line)
					cin >> el;
			bool yes = false;
			for (size_t k = 0; k < m && !yes; ++k)
				for (size_t l = 0; l < m && !yes; ++l)
					for (size_t b = 0; b < 2; ++b)
						yes = trythis(matrix, k, l, b);
			cout << (yes ? "YES\n" : "NO\n");
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
