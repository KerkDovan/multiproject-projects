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

#define FACTORIZATION_TYPE 0

	const size_t SIZE = 1000 * 1000;

	size_t l_pr_div[SIZE] = {}; // least prime divisor
	size_t primes[SIZE] = {};
	size_t primes_count = 0;
	size_t num_div_l_pr[SIZE] = {}; // number, divided by it's least prime divisor
#if FACTORIZATION_TYPE
	vector<size_t> factorized[SIZE];
#endif

	void init_primes() {
		for (size_t i = 2; i < SIZE; ++i) {
			if (l_pr_div[i] == 0) {
				l_pr_div[i] = i;
				primes[primes_count++] = i;
			}
			for (size_t j = 0; j < primes_count; ++j) {
				size_t m = i * primes[j];
				if (primes[j] > l_pr_div[i] || m >= SIZE)
					break;
				assert(l_pr_div[m] == 0); // making sure it's O(N)
				l_pr_div[m] = primes[j];
				num_div_l_pr[m] = i;
			}
		}
	}

#if FACTORIZATION_TYPE
	void init_factorize(size_t num) {
		if (num <= 1 || !factorized[num].empty())
			return;
		init_factorize(num_div_l_pr[num]);
		auto& prev = factorized[num_div_l_pr[num]];
		auto& cur = factorized[num] = vector<size_t>(prev.size() + 1);
		cur[0] = l_pr_div[num];
		for (size_t i = 0; i < prev.size(); ++i)
			cur[i + 1] = prev[i];
	}
#else
	vector<size_t> factorize(size_t num) {
		if (num <= 1)
			return{};
		auto tmp = factorize(num_div_l_pr[num]);
		tmp.emplace_back(l_pr_div[num]);
		return tmp;
	}
#endif

	template<class _Ty>
	ostream& print(ostream& os, const vector<_Ty>& vctr) {
		for (const auto& el : vctr)
			os << el << ' ';
		return os;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		init_primes();

#if FACTORIZATION_TYPE
		for (size_t i = 2; i < SIZE; ++i)
			init_factorize(i);
#endif
		
		cout << boolalpha;
		for (size_t i = SIZE - 1000; i < SIZE; ++i) {
			cout << i << " : ";
#if FACTORIZATION_TYPE
			const auto& fact = factorized[i];
#else
			const auto fact = factorize(i);
#endif
			print(cout, fact) << "=> ";
			size_t mul = 1;
			for (size_t el : fact)
				mul *= el;
			cout << (mul == i) << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
