// Changeable code starts here.

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
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

	typedef unsigned int uint;
	typedef long long ll;
	typedef unsigned long long ull;

	const char* CHARS = "TXRSZV7W";

	const int pieces[8][4] = {
		{ 1055745, 7342082, 4201476, 2099207 }, // T
		{ 2104322, 2104322, 2104322, 2104322 }, // X
		{ 3151874, 2104321, 2100230, 4201474 }, // R
		{ 3147782, 4201473, 3147782, 4201473 }, // S
		{ 6293507, 1055748, 6293507, 1055748 }, // Z
		{ 4198407, 7344132, 7341057, 1049607 }, // V
		{ 6294530, 1055746, 2103299, 2104324 }, // 7
		{ 4200451, 3151876, 6294529, 1051654 }, // W
	};

	const int checker = 7347207;

	//template<typename _Ty>
	//inline void debug_field(int field, const _Ty& msg) {
	//	only_multiproject(
	//		static const int p = (1 << 10) - 1;
	//	int _field = (field & p) |
	//		(field & (p << 10)) |
	//		(field & (p << 20));
	//	string to_out = "\n";
	//	for (int i = 29; i != -1; --i) {
	//		to_out += ((_field & (1 << i)) >> i) + '0';
	//		if (i == 20 || i == 10)
	//			to_out += '\n';
	//	}
	//	debug_output("", msg, field, to_out);
	//	)
	//}

	inline int id(int field) {
		static const int p = (1 << 7) - 1;
		return ((field & (p << 3)) >> 3) |
			((field & (p << 13)) >> 6) |
			((field & (p << 23)) >> 9);
	}

	inline bool failed(int field) {
		return (field & checker) != 0;
	}

	inline bool has_full(int field) {
		static const int p = 1 << 29 | 1 << 19 | 1 << 9;
		bool has = false;
		for (int i = 0; i < 10; ++i)
			has |= ((field & (p >> i)) == (p >> i));
		return has;
	}

	inline int remove_full(int field) {
		static const int p = 1 << 29 | 1 << 19 | 1 << 9;
		static bitset<10> full;
		static int cnt;
		cnt ^= cnt;
		static int i;
		for (i = 0; i < 10; ++i)
			cnt += full[i] = ((field & (p >> i)) == (p >> i));
		static int result;
		result ^= result;
		for (i = 0; i < 10; ++i) {
			if (full[i])
				result >>= 1;
			else
				result |= field & (p >> i);
		}
		result <<= cnt;
		return result;
	}

	inline int add_piece(int field, int piece) {
		int i = 1;
		while (i <= 7 && (field & (piece << i)) == 0)
			++i;
		--i;
		field |= piece << i;
		return remove_full(field);
	}

	struct infinite_play {};

	int sequence_size;
	char sequence[20];
	int dp_mem[1 << 21][20];

	int dp(int field, int num_in_seq, int depth = 0) {
		int piece = sequence[num_in_seq];
		int& result = dp_mem[id(field)][num_in_seq];
		if (result == -2)
			throw infinite_play();
		if (result != 0)
			return result;
		result = -2;
		int longest_play = 0;
		for (int i = (piece == 1 ? 3 : 0); i < 4; ++i) {
			int new_field = add_piece(field, pieces[piece][i]);
			if (!failed(new_field))
				longest_play = max(longest_play, dp(new_field,
					(num_in_seq + 1) % sequence_size, depth + 1));
		}
		return result = 1 + longest_play;
	}

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("f.in");
		freopen_out("f.out");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		string line;
		while (getline(cin, line)) {
			only_multiproject(memset(dp_mem, 0, sizeof(dp_mem)));
			for (size_t i = 0; i < line.size(); ++i)
				sequence[i] = (unsigned char)(strchr(CHARS, line[i]) - CHARS);
			sequence_size = (int)line.size();
			try {
				cout << dp(0, 0) << '\n';
			}
			catch (const infinite_play&) {
				cout << "forever\n";
			}
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif