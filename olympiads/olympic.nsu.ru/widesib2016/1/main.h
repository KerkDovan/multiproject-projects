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

	typedef vector<pair<size_t, size_t>> vpss;

	const size_t SIZE = 10 * 1000 * 1000 + 1;

	size_t primes[SIZE];
	size_t l_pr[SIZE]; // least prime, that divides this number
	size_t num_div[SIZE]; // number, divided by it's l_pr
	size_t primes_count;
	vpss factorized[SIZE];

	void init_primes() {
		primes_count = 0;
		for (size_t i = 2; i < SIZE; ++i) {
			if (l_pr[i] == 0) {
				l_pr[i] = i;
				primes[primes_count++] = i;
			}
			for (size_t j = 0; j < primes_count; ++j) {
				size_t m = i * primes[j];
				if (primes[j] > l_pr[i] || m >= SIZE)
					break;
				l_pr[m] = primes[j];
				num_div[m] = i;
			}
		}
	}

	vpss factorize(size_t i) {
		if (i <= 1)
			return{};
		if (factorized[i].size())
			return factorized[i];
		auto tmp = factorize(num_div[i]);
		if (tmp.size() && tmp.back().first == l_pr[i])
			++tmp.back().second;
		else
			tmp.emplace_back(l_pr[i], 1);
		return factorized[i] = tmp;
	}

	set<size_t> skiers;

	void erase_unnecessary(const vpss& fact, size_t cur, size_t product, size_t number) {
		skiers.erase(product);
		if (cur == fact.size())
			return;
		if (cur + 1 < fact.size())
			erase_unnecessary(fact, cur + 1, product, number);
		for (size_t i = 0; i < fact[cur].second; ++i) {
			product *= fact[cur].first;
			if (product >= number)
				break;
			for (size_t j = cur + 1; j <= fact.size(); ++j)
				erase_unnecessary(fact, j, product, number);
		}
	}

	int main() {
		freopen_in("input.txt");
		freopen_out("output.txt");

		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		init_primes();

		size_t cnt;
		while (cin >> cnt) {
			skiers.clear();
			for (size_t i = 0; i < cnt; ++i) {
				size_t tmp;
				cin >> tmp;
				skiers.emplace(tmp);
			}
			for (auto iter = skiers.rbegin(); iter != skiers.rend(); ++iter)
				if (*iter > 1)
					erase_unnecessary(factorize(*iter), 0, 1, *iter);
			for (size_t skier : skiers)
				cout << skier << ' ';
			cout << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
