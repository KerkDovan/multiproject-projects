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

	const char FIGURES[ ][3][4] = {
		{
			"###",
			".#.",
			".#.",
		}, {
			".#.",
			"###",
			".#.",
		}, {
			".##",
			"##.",
			".#.",
		}, {
			".##",
			".#.",
			"##.",
		}, {
			"##.",
			".#.",
			".##",
		}, {
			"#..",
			"#..",
			"###",
		}, {
			"##.",
			".##",
			".#.",
		}, {
			"#..",
			"##.",
			".##",
		},
	};

	int pieceCount = 0;
	array<int, 32> pieces;

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
		for (const auto figure: FIGURES) {
			char f[2][3][3];
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					f[0][i][j] = figure[i][j];
			for (int r = 0; r < 4; r++) {
				int mask = 0x0;
				for (int i = 0, k = 0; i < 3; i++)
					for (int j = 0; j < 3; j++, k++)
						mask |= (f[r & 0x1][i][j] == '#') << k;
				pieces[pieceCount++] = mask;
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						f[!(r & 0x1)][i][j] = f[r & 0x1][j][2 - i];
			}
		}
		sort(pieces.begin(), pieces.begin() + pieceCount);
		pieceCount = unique(pieces.begin(), pieces.begin() + pieceCount) - pieces.begin();
		for (int i = 0; i < pieceCount; i++)
			cout << pieces[i] << '\n';

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif