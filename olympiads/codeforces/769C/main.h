// Changeable code starts here. 

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <functional>
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

#define stringify(...) stringify2(__VA_ARGS__)
#define stringify2(...) #__VA_ARGS__

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
#ifdef _MULTIPROJECT_PROJECT_CONFIG_H_
#define freopen_in(filename) freopen("project\\" ## filename, "r", stdin)
#define freopen_out(filename) freopen("project\\" ## filename, "w", stdout)
#else
#define freopen_in(filename) freopen(filename, "r", stdin)
#define freopen_out(filename) freopen(filename, "w", stdout)
#endif
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

	char get_direction(const vector<vector<char>>& field, size_t x, size_t y) {
		if (field[x][y + 1] != '*')
			return 'D';
		if (field[x - 1][y] != '*')
			return 'L';
		if (field[x + 1][y] != '*')
			return 'R';
		if (field[x][y - 1] != '*')
			return 'U';
		return 'N';
	}

	char invert_direction(char dir) {
		switch (dir) {
		case 'D': return 'U';
		case 'L': return 'R';
		case 'R': return 'L';
		case 'U': return 'D';
		}
		return 'N';
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t h, w, k;
		while (cin >> h >> w >> k) {
			// Reading data
			size_t x, y;
			vector<vector<char>> field(w + 2, vector<char>(h + 2, '*'));
			for (size_t i = 1; i <= h; ++i) {
				for (size_t j = 1; j <= w; ++j) {
					cin >> field[j][i];
					if (field[j][i] == 'X')
						x = j, y = i;
				}
			}
			if (k % 2 == 1 || get_direction(field, x, y) == 'N') {
				cout << "IMPOSSIBLE\n";
				continue;
			}

			// Auxiliary data
			string path = "";

			// Computations
			for (size_t i = 0; i < k / 2; ++i) {
				char dir = get_direction(field, x, y);
				switch (dir) {
				case 'D': ++y; break;
				case 'L': --x; break;
				case 'R': ++x; break;
				case 'U': --y; break;
				default: break;
				}
				path += dir;
			}
			for (size_t i = path.size() - 1; i != (size_t)-1; --i)
				path += invert_direction(path[i]);

			// Output
			cout << path << '\n';

		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
