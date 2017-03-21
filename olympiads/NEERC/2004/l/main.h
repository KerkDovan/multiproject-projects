﻿// Changeable code starts here. 

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
	
	const size_t answer[11][11][11] = {
		{ // answer[0]:
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[0][0]
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[0][1]
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[0][2]
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[0][3]
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[0][4]
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[0][5]
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[0][6]
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[0][7]
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[0][8]
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[0][9]
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[0][10]
		},
		{ // answer[1]:
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[1][0]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[1][1]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[1][2]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[1][3]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[1][4]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[1][5]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[1][6]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[1][7]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[1][8]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[1][9]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[1][10]
		},
		{ // answer[2]:
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[2][0]
			{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[2][1]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[2][2]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[2][3]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[2][4]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[2][5]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[2][6]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[2][7]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[2][8]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[2][9]
			{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[2][10]
		},
		{ // answer[3]:
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[3][0]
			{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, }, // answer[3][1]
			{ 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, }, // answer[3][2]
			{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, }, // answer[3][3]
			{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, }, // answer[3][4]
			{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, }, // answer[3][5]
			{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, }, // answer[3][6]
			{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, }, // answer[3][7]
			{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, }, // answer[3][8]
			{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, }, // answer[3][9]
			{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, }, // answer[3][10]
		},
		{ // answer[4]:
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[4][0]
			{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, }, // answer[4][1]
			{ 0, 0, 1, 4, 5, 5, 5, 5, 5, 5, 5, }, // answer[4][2]
			{ 0, 0, 4, 4, 5, 5, 5, 5, 5, 5, 5, }, // answer[4][3]
			{ 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, }, // answer[4][4]
			{ 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, }, // answer[4][5]
			{ 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, }, // answer[4][6]
			{ 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, }, // answer[4][7]
			{ 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, }, // answer[4][8]
			{ 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, }, // answer[4][9]
			{ 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, }, // answer[4][10]
		},
		{ // answer[5]:
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[5][0]
			{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, }, // answer[5][1]
			{ 0, 0, 0, 2, 5, 6, 6, 6, 6, 6, 6, }, // answer[5][2]
			{ 0, 0, 2, 8, 11, 12, 12, 12, 12, 12, 12, }, // answer[5][3]
			{ 0, 0, 5, 11, 11, 12, 12, 12, 12, 12, 12, }, // answer[5][4]
			{ 0, 1, 6, 12, 12, 12, 12, 12, 12, 12, 12, }, // answer[5][5]
			{ 0, 1, 6, 12, 12, 12, 12, 12, 12, 12, 12, }, // answer[5][6]
			{ 0, 1, 6, 12, 12, 12, 12, 12, 12, 12, 12, }, // answer[5][7]
			{ 0, 1, 6, 12, 12, 12, 12, 12, 12, 12, 12, }, // answer[5][8]
			{ 0, 1, 6, 12, 12, 12, 12, 12, 12, 12, 12, }, // answer[5][9]
			{ 0, 1, 6, 12, 12, 12, 12, 12, 12, 12, 12, }, // answer[5][10]
		},
		{ // answer[6]:
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[6][0]
			{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, }, // answer[6][1]
			{ 0, 0, 0, 1, 7, 12, 13, 13, 13, 13, 13, }, // answer[6][2]
			{ 0, 0, 1, 8, 29, 34, 35, 35, 35, 35, 35, }, // answer[6][3]
			{ 0, 0, 7, 29, 29, 34, 35, 35, 35, 35, 35, }, // answer[6][4]
			{ 0, 0, 12, 34, 34, 34, 35, 35, 35, 35, 35, }, // answer[6][5]
			{ 0, 1, 13, 35, 35, 35, 35, 35, 35, 35, 35, }, // answer[6][6]
			{ 0, 1, 13, 35, 35, 35, 35, 35, 35, 35, 35, }, // answer[6][7]
			{ 0, 1, 13, 35, 35, 35, 35, 35, 35, 35, 35, }, // answer[6][8]
			{ 0, 1, 13, 35, 35, 35, 35, 35, 35, 35, 35, }, // answer[6][9]
			{ 0, 1, 13, 35, 35, 35, 35, 35, 35, 35, 35, }, // answer[6][10]
		},
		{ // answer[7]:
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[7][0]
			{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, }, // answer[7][1]
			{ 0, 0, 0, 0, 2, 13, 18, 19, 19, 19, 19, }, // answer[7][2]
			{ 0, 0, 0, 7, 48, 84, 89, 90, 90, 90, 90, }, // answer[7][3]
			{ 0, 0, 2, 48, 66, 102, 107, 108, 108, 108, 108, }, // answer[7][4]
			{ 0, 0, 13, 84, 102, 102, 107, 108, 108, 108, 108, }, // answer[7][5]
			{ 0, 0, 18, 89, 107, 107, 107, 108, 108, 108, 108, }, // answer[7][6]
			{ 0, 1, 19, 90, 108, 108, 108, 108, 108, 108, 108, }, // answer[7][7]
			{ 0, 1, 19, 90, 108, 108, 108, 108, 108, 108, 108, }, // answer[7][8]
			{ 0, 1, 19, 90, 108, 108, 108, 108, 108, 108, 108, }, // answer[7][9]
			{ 0, 1, 19, 90, 108, 108, 108, 108, 108, 108, 108, }, // answer[7][10]
		},
		{ // answer[8]:
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[8][0]
			{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, }, // answer[8][1]
			{ 0, 0, 0, 0, 1, 11, 30, 37, 38, 38, 38, }, // answer[8][2]
			{ 0, 0, 0, 3, 63, 169, 223, 230, 231, 231, 231, }, // answer[8][3]
			{ 0, 0, 1, 63, 140, 307, 361, 368, 369, 369, 369, }, // answer[8][4]
			{ 0, 0, 11, 169, 307, 307, 361, 368, 369, 369, 369, }, // answer[8][5]
			{ 0, 0, 30, 223, 361, 361, 361, 368, 369, 369, 369, }, // answer[8][6]
			{ 0, 0, 37, 230, 368, 368, 368, 368, 369, 369, 369, }, // answer[8][7]
			{ 0, 1, 38, 231, 369, 369, 369, 369, 369, 369, 369, }, // answer[8][8]
			{ 0, 1, 38, 231, 369, 369, 369, 369, 369, 369, 369, }, // answer[8][9]
			{ 0, 1, 38, 231, 369, 369, 369, 369, 369, 369, 369, }, // answer[8][10]
		},
		{ // answer[9]:
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[9][0]
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, }, // answer[9][1]
			{ 0, 0, 0, 0, 0, 3, 25, 53, 60, 61, 61, }, // answer[9][2]
			{ 0, 0, 0, 1, 43, 256, 466, 543, 550, 551, 551, }, // answer[9][3]
			{ 0, 0, 0, 43, 224, 820, 1127, 1204, 1211, 1212, 1212, }, // answer[9][4]
			{ 0, 0, 3, 256, 820, 893, 1200, 1277, 1284, 1285, 1285, }, // answer[9][5]
			{ 0, 0, 25, 466, 1127, 1200, 1200, 1277, 1284, 1285, 1285, }, // answer[9][6]
			{ 0, 0, 53, 543, 1204, 1277, 1277, 1277, 1284, 1285, 1285, }, // answer[9][7]
			{ 0, 0, 60, 550, 1211, 1284, 1284, 1284, 1284, 1285, 1285, }, // answer[9][8]
			{ 0, 1, 61, 551, 1212, 1285, 1285, 1285, 1285, 1285, 1285, }, // answer[9][9]
			{ 0, 1, 61, 551, 1212, 1285, 1285, 1285, 1285, 1285, 1285, }, // answer[9][10]
		},
		{ // answer[10]:
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, // answer[10][0]
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, }, // answer[10][1]
			{ 0, 0, 0, 0, 0, 1, 16, 68, 108, 117, 118, }, // answer[10][2]
			{ 0, 0, 0, 0, 21, 277, 842, 1226, 1329, 1338, 1339, }, // answer[10][3]
			{ 0, 0, 0, 21, 287, 1847, 3234, 3773, 3876, 3885, 3886, }, // answer[10][4]
			{ 0, 0, 1, 277, 1847, 2376, 4003, 4542, 4645, 4654, 4655, }, // answer[10][5]
			{ 0, 0, 16, 842, 3234, 4003, 4003, 4542, 4645, 4654, 4655, }, // answer[10][6]
			{ 0, 0, 68, 1226, 3773, 4542, 4542, 4542, 4645, 4654, 4655, }, // answer[10][7]
			{ 0, 0, 108, 1329, 3876, 4645, 4645, 4645, 4645, 4654, 4655, }, // answer[10][8]
			{ 0, 0, 117, 1338, 3885, 4654, 4654, 4654, 4654, 4654, 4655, }, // answer[10][9]
			{ 0, 1, 118, 1339, 3886, 4655, 4655, 4655, 4655, 4655, 4655, }, // answer[10][10]
		},
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int n, w, h;
		while (cin >> n >> w >> h)
			cout << answer[n][w][h] << '\n';

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif