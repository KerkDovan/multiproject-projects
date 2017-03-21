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

	const size_t SIZE = 10 * 1000 * 1000 + 1;

	size_t primes[SIZE];
	size_t primes_count = 0;
	size_t l_pr[SIZE]; // least prime divisor
	//map<ll, ll> hashed_primes;

	void init_primes() {
		for (size_t i = 2; i < SIZE; ++i) {
			if (l_pr[i] == 0) {
				l_pr[i] = i;
				primes[primes_count++] = i;
				//hashed_primes.emplace_hint(hashed_primes.end(), (ll)i * i, i);
			}
			for (size_t j = 0; j < primes_count; ++j) {
				size_t m = i * primes[j];
				if (primes[j] > l_pr[i] || m >= SIZE)
					break;
				l_pr[m] = primes[j];
			}
		}
	}

	inline bool isPower(ll x, ll result) {
		ll tmp = x;
		while (tmp < result)
			tmp *= x;
		return tmp == result;
	}

	ll getLargestPrimeDivisor(ll num) {
		//auto iter = hashed_primes.upper_bound(num > 100 ? sqrt(num) : num);
		//if (iter == hashed_primes.end() && iter != hashed_primes.begin())
		//	--iter;
		//for (; iter != hashed_primes.begin() && iter->second != 0; --iter) {
		//	ll tmp = num / iter->second;
		//	if (tmp * iter->second == num) {
		//		if (tmp == 1)
		//			return -1;
		//		return isPower(iter->second, num) ? (ll)-1 : iter->second;
		//	}
		//}
		ll result = -1;
		for (size_t i = primes_count - 1; primes[i] != 0; --i) {
			ll tmp = num / primes[i];
			if (tmp * primes[i] == num) {
				if (tmp == 1)
					return -1;
				if (result != -1)
					return result;
				if (isPower(primes[i], num))
					result = primes[i];
				else
					return primes[i];
			}
		}
		return -1;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		init_primes();

		ll num;
		while (cin >> num, num)
			cout << getLargestPrimeDivisor(num) << '\n';

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
