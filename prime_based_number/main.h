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
#include <sstream>
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
	
	size_t primes_count;
	vector<ull> primes;

	class PrimeBasedNumber {
	public:
		PrimeBasedNumber() {
			_length = 1;
			_count = primes_count;
			_digits.assign(_count, 0);
		}

		PrimeBasedNumber& operator ++ () {
			ull rem = 1;
			size_t id = 0;
			while (rem && id < _count) {
				_digits[id] += rem;
				rem = _digits[id] / primes[id];
				_digits[id] %= primes[id];
				++id;
			}
			if (id > _length)
				_length = id;
			return *this;
		}

		friend ostream& operator << (ostream& os, const PrimeBasedNumber& rhs) {
			stringstream ss;
			for (size_t i = 0; i < rhs._length; ++i) {
				if (i)
					ss << '.';
				ull tmp = rhs._digits[rhs._length - i - 1];
				ss << tmp;
			}
			return os << setw(15) << ss.str();
		}

	private:
		vector<ull> _digits;
		size_t _count;
		size_t _length;
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		cin >> primes_count;
		primes.resize(primes_count);
		for (ull& prime : primes)
			cin >> prime;

		ull num_d = 2;
		PrimeBasedNumber num_p;
		++++num_p;
		size_t id = 0;
		while (id < primes_count) {
			if (num_d == primes[id]) {
				cout << setw(6) << num_d << " = " << num_p << '\n';
				++id;
			}
			++num_d;
			++num_p;
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
