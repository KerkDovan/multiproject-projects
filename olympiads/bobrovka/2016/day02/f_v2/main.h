// Changeable code starts here. 

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <algorithm>
#include <array>
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
		{ 0x079, 0x1D2, 0x13C, 0x097, }, // T
		{ 0x0BA, 0x0BA, 0x0BA, 0x0BA, }, // X
		{ 0x0F2, 0x0B9, 0x09E, 0x13A, }, // R
		{ 0x0D6, 0x139, 0x0D6, 0x139, }, // S
		{ 0x193, 0x07C, 0x193, 0x07C, }, // Z
		{ 0x127, 0x1E4, 0x1C9, 0x04F, }, // V
		{ 0x19A, 0x07A, 0x0B3, 0x0BC, }, // 7
		{ 0x133, 0x0F4, 0x199, 0x05E, }, // W
	};

	const int checker = (1 << 9) - 1;

	inline int id(int field) {
		return field >> 9;
	}

	inline bool failed(int field) {
		return (field & checker) != 0;
	}

	inline int remove_full(int field) {
		static const int p = 1 << 29 | 1 << 28 | 1 << 27;
		bitset<10> full;
		int cnt = 0;
		int i;
		for (i = 0; i < 10; ++i)
			cnt += full[i] = (field & p >> i * 3) == p >> i * 3;
		int result = 0;
		for (i = 0; i < 10; ++i) {
			if (full[i])
				result >>= 3;
			else
				result |= field & p >> i * 3;
		}
		result <<= cnt * 3;
		return result;
	}

	inline int add_piece(int field, int piece) {
		int i = 1;
		while (i <= 7 && (field & (piece << i * 3)) == 0)
			++i;
		--i;
		field |= piece << (i * 3);
		return remove_full(field);
	}

	int sequence_size;
	unsigned char sequence[20];
	int dp_mem[1 << 21][20];

	int dp(int field, int num_in_seq) {
		int piece = sequence[num_in_seq];
		int& result = dp_mem[id(field)][num_in_seq];
		if (result == -2)
			throw 0;
		if (result != 0)
			return result;
		result = -2;
		int longest_play = 0;
		for (int i = (piece == 1 ? 3 : 0); i < 4; ++i) {
			int new_field = add_piece(field, pieces[piece][i]);
			if (!failed(new_field))
				longest_play = max(longest_play, dp(new_field, 
					(num_in_seq + 1) % sequence_size));
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
			catch (int) {
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