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

	const size_t SIDE = 500;
	const size_t SIZE = SIDE * SIDE;

	typedef bitset<SIZE> field;

	field rows[SIDE] = {};

	bool isRect(const field& f, size_t cnt) {
		if (f.count() != cnt)
			return false;
		size_t maxx = 0, maxy = 0;
		for (size_t i = 0; i < SIDE; ++i) {
			for (size_t j = 0; j < SIDE; ++j) {
				if (f[i * SIDE + j]) {
					maxy = max(maxy, i);
					maxx = max(maxx, j);
				}
			}
		}
		field tmp;
		for (size_t i = 0; i <= maxy; ++i) {
			tmp = rows[maxx] << i * SIDE;
			if ((f & tmp) != tmp)
				return false;
		}
		return true;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		/*
		
			SOLUTION IS INCORRECT. 
		
		*/

		rows[0] = 0;
		rows[0][0] = 1;
		for (size_t i = 1; i < SIDE; ++i) {
			rows[i] = rows[i - 1];
			rows[i][i] = 1;
		}

		size_t n, m;
		while (cin >> n >> m) {
			field piece(0);
			size_t minx = SIZE + 1, miny = SIZE + 1;
			for (size_t i = 0; i < n; ++i) {
				for (size_t j = 0; j < m; ++j) {
					char c;
					cin >> c;
					if (c == 'X') {
						piece[i * SIDE + j] = 1;
						minx = min(minx, j);
						miny = min(miny, i);
					}
				}
			}
			piece = (piece >> minx) >> (SIDE * miny);
			size_t cnt = piece.count() * 2;
			bool found = 0;
			for (size_t i = 1; !found && i <= m; ++i) {
				field piece2 = piece | (piece << i);
				found |= isRect(piece2, cnt);
			}
			for (size_t i = 1; !found && i <= n; ++i) {
				field piece2 = piece | (piece << i * SIDE);
				found |= isRect(piece2, cnt);
			}
			cout << (found ? "YES\n" : "NO\n");
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
