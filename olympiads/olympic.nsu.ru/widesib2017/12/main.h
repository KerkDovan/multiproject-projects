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
#ifdef MYLIB
	using namespace MyLib;
#endif // MYLIB

	typedef long long ll;
	typedef unsigned long long ull;

	const size_t MAX_BYTES_COUNT = 2 * 100 * 1000 + 10;
	const size_t MAX_BITS_COUNT = 8 * MAX_BYTES_COUNT;
	const size_t PATTERNS_COUNT = 6;

	bool bits[MAX_BITS_COUNT];
	vector<pair<size_t, size_t>> positions; // <bit_id, pattern>

	inline size_t is_pattern(size_t id) {
		size_t tmp = 0;
		while (bits[id + tmp] && tmp <= PATTERNS_COUNT)
			++tmp;
		if (tmp == 0)
			return 0;
		if (tmp == 1 || bits[id + tmp])
			return (size_t)-1;
		for (size_t i = 1; i < tmp; ++i)
			if (bits[id + 8 * i] != 1 || bits[id + 8 * i + 1] != 0)
				return (size_t)-1;
		return --tmp;
	}

	inline int from_pattern(size_t id, size_t pattern) {
		int result = 0;
		for (size_t i = pattern ? pattern + 2 : 1; i < 8; ++i)
			result = (result << 1) + bits[id + i];
		for (size_t i = 1; i <= pattern; ++i) {
			for (size_t j = 2; j < 8; ++j)
				result = (result << 1) | bits[id + (i << 3) + j];
		}
		return result;
	}

	int main() {
		freopen_in("input.txt");
		freopen_out("output.txt");

		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		positions.reserve(MAX_BYTES_COUNT);

		size_t cnt = 0;
		int bt;
		while (cin >> hex >> bt) {
			++cnt;
			for (size_t i = 1; i <= 8; ++i) {
				bits[8 * cnt - i] = bt & 1;
				bt >>= 1;
			}
		}

		for (size_t i = 0; i < cnt; ++i) {
			size_t pat = is_pattern(i << 3);
			if (pat == -1)
				continue;
			debug << dec << i << "[" << pat <<"]: " << hex << from_pattern(i << 3, pat) << '\n';
			positions.emplace_back(make_pair(i, pat));
		}

		size_t cur_size;
		for (size_t i = 0; i < positions.size(); i += cur_size) {
			cur_size = 1;
			while (i + cur_size < positions.size() &&
				positions[i + cur_size].first == positions[i + cur_size - 1].first + positions[i + cur_size - 1].second + 1)
			{
				++cur_size;
			}
			if (cur_size >= 3) {
				for (size_t j = 0; j < cur_size; ++j) {
					if (j)
						cout << ' ';
					cout << hex << uppercase << from_pattern(positions[i + j].first << 3, positions[i + j].second);
				}
				cout << '\n';
			}
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
