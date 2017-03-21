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

	struct Piles {
		unsigned get(unsigned id) const { return (data >> id * 3) & 0x7; }
		void set(unsigned id, unsigned value) { id *= 3, data = ((data & ~(0x7 << id)) | value << id); }
		bool operator == (const Piles& rhs) const { return data == rhs.data; }
		bool operator < (const Piles& rhs) const { return data < rhs.data; }
		unsigned data = 0;
	};

	struct Cards {
		int data[9][4];
		vector<Piles> operator () (const Piles& piles) const {
			vector<int> top(9, -1);
			for (unsigned i = 0; i < 9; ++i) {
				unsigned sz = piles.get(i);
				if (sz == 0)
					continue;
				top[i] = data[i][sz - 1] % 10;
			}
			vector<Piles> result;
			for (unsigned i = 0; i < 9; ++i) {
				for (unsigned j = i + 1; j < 9; ++j) {
					if (top[i] != top[j])
						continue;
					Piles tmp = piles;
					tmp.set(i, tmp.get(i) - 1);
					tmp.set(j, tmp.get(j) - 1);
					result.emplace_back(tmp);
				}
			}
			return result;
		}
	};

	inline int cardToInt(char rank, char suit) {
		static map<char, int> RANKS = {{'6',0},{'7',1},{'8',2},{'9',3},
			{'T',4},{'J',5},{'Q',6},{'K',7},{'A',8}};
		static map<char, int> SUITS = {{'S',0},{'C',1},{'D',2},{'H',3}};
		return SUITS[suit] * 10 + RANKS[rank];
	}

	Cards cards;
	map<Piles, double> dp_mem;

	double dp(const Piles& piles) {
		if (piles == Piles())
			return 1.0;
		if (found_own(dp_mem, piles))
			return dp_mem[piles];
		auto turns = cards(piles);
		if (turns.empty())
			return dp_mem[piles] = 0.0;
		double result = 0.0;
		for (auto turn : turns)
			result += dp(turn);
		result /= (double)turns.size();
		return dp_mem[piles] = result;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		cout << setprecision(6) << fixed;

		char rank, suit;
		while (cin >> rank >> suit) {
			cards.data[0][0] = cardToInt(rank, suit);
			Piles piles;
			for (unsigned i = 0; i < 9; ++i) {
				for (unsigned j = 0; j < 4; ++j) {
					if (i == 0 && j == 0)
						continue;
					cin >> rank >> suit;
					cards.data[i][j] = cardToInt(rank, suit);
				}
				piles.set(i, 4);
			}
			cout << dp(piles) << "\n";
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
