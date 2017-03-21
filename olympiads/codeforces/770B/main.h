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

	//size_t digit_sum(size_t number) {
	//	size_t result = 0;
	//	while (number) {
	//		result += number % 10;
	//		number /= 10;
	//	}
	//	return result;
	//}

	struct Number {
		static const size_t SIZE = 20;
		Number() { memset(digits, 0, sizeof(digits)); }
		Number(ull source) : Number() {
			size_t i = 0;
			while (source) {
				digits[i] = source % (ull)10;
				source /= (ull)10;
				++i;
			}
		}
		ull digits[SIZE];
		Number& operator ++ () {
			size_t i = 0;
			for (; i < SIZE; ++i)
				if (digits[i] < 9)
					break;
			if (i != 0)
				--digits[i - 1];
			++digits[i];
			return *this;
		}
		bool operator <= (Number rhs) const {
			for (size_t i = SIZE - 1; i != (size_t)-1; --i)
				if (digits[i] > rhs.digits[i])
					return false;
				else if (digits[i] < rhs.digits[i])
					return true;
			return true;
		}
		operator ull () const {
			ull result = 0;
			for (size_t i = SIZE - 1; i != (size_t)-1; --i) {
				result *= (ull)10;
				result += digits[i];
			}
			return result;
		}
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		//set<size_t> results;
		//size_t prev = 0;
		//for (size_t i = 0; i < 100 * 1000; ++i) {
		//	size_t max_num = prev;
		//	size_t max_sum = digit_sum(prev);
		//	for (size_t j = max_num; j <= i; ++j) {
		//		size_t tmp = digit_sum(j);
		//		if (tmp >= max_sum)
		//			max_sum = tmp,
		//			max_num = j;
		//	}
		//	prev = max_num;
		//	results.emplace(max_num);
		//}
		//for (size_t res : results)
		//	cout << res << " => " << digit_sum(res) << '\n';

		ull x;
		while (cin >> x) {
			Number source(x);
			Number iterator, prev;
			while (iterator <= source) {
				prev = iterator;
				++iterator;
			}
			ull result = prev;
			cout << result << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
