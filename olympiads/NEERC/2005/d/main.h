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

	struct Card {
		char rank, suit;
	};

	struct Pile {
		Card cards[4];
		Card operator [] (int i) const { return cards[i]; }
		Card& operator [] (int i) { return cards[i]; }
		friend istream& operator >> (istream& is, Pile& pile) {
			string str; is >> ws; getline(is, str);
			for (int i = 0; i < 4 * (!str.empty()); ++i)
				pile.cards[i] = { str[i * 3], str[i * 3 + 1] };
			return is;
		}
	};

	struct Turn {
	public:
		int getCount(int id) const {
			int shift = id * 3;
			return (cnts & (7 << shift)) >> shift;
		}
		void setCount(int id, int cnt) {
			int shift = id * 3, mask = 7 << shift;
			cnts &= ~mask;
			cnts |= mask & (cnt << shift);
		}
		bool win() const { return cnts != 0; }
	private:
		int cnts;
	};

	struct Game {
		Pile piles[9];
		vector<pair<int, int>> getSimilar(const Turn& turn) const {
			vector<pair<int, int>> result;
			for (int i = 0; i < 9; ++i) {
				int ci = turn.getCount(i);
				if (!ci) continue;
				for (int j = i + 1; j < 9; ++j) {
					int cj = turn.getCount(j);
					if (!cj) continue;
					if (ci && cj && piles[i][ci - 1].rank == piles[j][cj - 1].rank)
						result.emplace_back(i, j);
				}
			}
			return result;
		}
	};

	double getProbability(const Game& game, const Turn& turn) {
		if (turn.win())
			return 1.0;
		auto similar = game.getSimilar(turn);
		if (similar.empty())
			return 0.0;
		double result = 0.0;
		for (const auto& p : similar) {
			Turn t = turn;
			t.setCount(p.first, t.getCount(p.first) - 1);
			t.setCount(p.second, t.getCount(p.second) - 1);
			result += getProbability(game, t);
		}
		return result / (double)similar.size();
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		Turn gameStart;
		for (int i = 0; i < 9; ++i)
			gameStart.setCount(i, 4);
		Game game;
		while (cin >> game.piles[0]) {
			for (int i = 1; i < 9; ++i)
				cin >> game.piles[i];
			cout << fixed << setprecision(6) << getProbability(game, gameStart) << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
