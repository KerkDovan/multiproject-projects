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

	const size_t MAX_SIZE_OF_POLYOMINO = 10;
	
	struct Polyomino {
	public:
		static const size_t SIDE_SIZE = MAX_SIZE_OF_POLYOMINO * 2 + 1;

		Polyomino() : Polyomino(0) {}
		Polyomino(const bitset<SIDE_SIZE * SIDE_SIZE>& fig) : figure(fig) {}

		inline bool get(size_t x, size_t y) const {
			return figure[y * SIDE_SIZE + x];
		}
		inline void set(size_t x, size_t y, bool value) {
			figure.set(y * SIDE_SIZE + x, value);
		}

		inline bool fitInRect(size_t w, size_t h) const {
			static const auto INITIAL = make_tuple(SIDE_SIZE, 0, 0, SIDE_SIZE);
			size_t l, r, t, b;
			tie(l, r, t, b) = INITIAL;
			for (size_t y = 0; y < SIDE_SIZE; ++y) {
				for (size_t x = 0; x < SIDE_SIZE; ++x) {
					if (figure[y * SIDE_SIZE + x]) {
						l = min(l, x); r = max(r, x);
						t = max(t, y); b = min(b, y);
					}
				}
			}
			if (tie(l, r, t, b) == INITIAL)
				return true;
			size_t dx = r - l + 1, dy = t - b + 1;
			return dx <= w && dy <= h || dx <= h && dy <= w;
		}

		inline bool operator < (const Polyomino& rhs) const {
			bitset<SIDE_SIZE * SIDE_SIZE> a = this->figure, b = rhs.figure;
			while (a == ((a >> 1) << 1))
				a >>= 1;
			while (b == ((b >> 1) << 1))
				b >>= 1;
			for (size_t i = 0; i < SIDE_SIZE * SIDE_SIZE; ++i)
				if (a[i] != b[i])
					return a[i] < b[i];
			return false;
		}
	private:
		bitset<SIDE_SIZE * SIDE_SIZE> figure;
	};

	inline Polyomino turnRight(const Polyomino& figure) {
		Polyomino result;
		for (size_t i = 0; i < figure.SIDE_SIZE; ++i)
			for (size_t j = 0; j < figure.SIDE_SIZE; ++j)
				result.set(i, j,
					figure.get(j, figure.SIDE_SIZE - i - 1));
		return result;
	}

	inline Polyomino mirror(const Polyomino& figure) {
		Polyomino result;
		for (size_t i = 0; i < figure.SIDE_SIZE; ++i)
			for (size_t j = 0; j < figure.SIDE_SIZE; ++j)
				result.set(i, j, 
					figure.get(figure.SIDE_SIZE - i - 1, j));
		return result;
	}

	template<size_t Count>
	struct Polyominoes {
	public:
		static const size_t TILES_COUNT = Count;
		Polyominoes() : 
			Polyominoes(Polyomino(),  MAX_SIZE_OF_POLYOMINO, MAX_SIZE_OF_POLYOMINO) {}
		Polyominoes(const Polyomino& figure, size_t x, size_t y) {
			auto cur = figure;
			cur.set(x, y, true);
			bool found = false;
			auto tmp = cur;
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 4; ++j) {
					found |= saved.find(tmp) != saved.end();
					tmp = turnRight(tmp);
				}
				if (!i)
					tmp = mirror(tmp);
			}
			if (!found) {
				saved.emplace(cur);
				queue<pair<size_t, size_t>> coords;
				coords.emplace(MAX_SIZE_OF_POLYOMINO, MAX_SIZE_OF_POLYOMINO);
				vector<bitset<Polyomino::SIDE_SIZE>> visited(Polyomino::SIDE_SIZE, 0);
				visited[coords.front().first][coords.front().second] = true;
				static const int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };
				while (!coords.empty()) {
					size_t cx, cy;
					tie(cx, cy) = coords.front();
					coords.pop();
					for (int i = 0; i < 4; ++i) {
						size_t tx = cx + dx[i], ty = cy + dy[i];
						if (visited[tx][ty])
							continue;
						visited[tx][ty] = true;
						if (cur.get(tx, ty))
							coords.emplace(tx, ty);
						else
							Polyominoes<Count + 1>(cur, tx, ty);
					}
				}
			}
		}
		static size_t count(size_t w, size_t h) {
			size_t result = 0;
			for (const auto& plmn : saved)
				result += plmn.fitInRect(w, h);
			return result;
		}
	private:
		static set<Polyomino> saved;
	};

	template <size_t Count>
	set<Polyomino> Polyominoes<Count>::saved;

	template<>
	struct Polyominoes<MAX_SIZE_OF_POLYOMINO + 1> {
		Polyominoes() {}
		Polyominoes(const Polyomino&, size_t, size_t) {}
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		Polyominoes<1>();

		cout << "const size_t answer[11][11][11] = {\n";
#define FindAnswer(n)\
		cout << "    {" << " // answer[" << n << "]:\n";\
		for (size_t h = 0; h <= MAX_SIZE_OF_POLYOMINO; ++h) {\
			cout << "        { ";\
			for(size_t w = 0; w <= MAX_SIZE_OF_POLYOMINO; ++w) {\
				cout << Polyominoes<n>::count(w, h);\
				cout << ", ";\
			}\
			cout << "}, // answer[" << n << "][" << h << "]\n";\
		}\
		cout << "    },\n";
		FindAnswer(0); FindAnswer(1); FindAnswer(2); FindAnswer(3);
		FindAnswer(4); FindAnswer(5); FindAnswer(6); FindAnswer(7);
		FindAnswer(8); FindAnswer(9); FindAnswer(10);
#undef FindAnswer
		cout << "};\n";

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
