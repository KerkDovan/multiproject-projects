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
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string.h>
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

	typedef long long ll;
	typedef unsigned long long ull;

	const int MAXCOUNT = 2000;

	// Coded by Kolya

	template <int N>
	struct FenwickTree {
		int d[N];

		void init() {
			memset(d, 0x00, sizeof d);
		}

		int get(int right) {
			int result = 0;
			for (; right; right &= right - 1)
				result = max(result, d[right - 1]);
			return result;
		}

		void set(int i, int value) {
			for (; i < N; i |= i + 1)
				d[i] = max(d[i], value);
		}
	};

	int carsCount;
	int w[MAXCOUNT];
	int lis_mem[MAXCOUNT];
	int lds_mem[MAXCOUNT];
	FenwickTree<MAXCOUNT> fwt;

	void calc_lis() {
		fwt.init();
		for (int i = 0; i < carsCount; i++)
			fwt.set(MAXCOUNT - 1 - w[i], (lis_mem[i] = fwt.get(MAXCOUNT - 1 - w[i]) + 1));
	}

	void calc_lds() {
		fwt.init();
		for (int i = 0; i < carsCount; i++)
			fwt.set(w[i], (lds_mem[i] = fwt.get(w[i]) + 1));
	}

	/*
	int lis(int cur) {
		int& result = lis_mem[cur] = 0;
		for (int i = carsCount - 1; i != cur; --i) {
			if (w[cur] < w[i])
				result = max(result, lis_mem[i]);
		}
		return result += 1;
	}

	int lds(int cur) {
		int& result = lds_mem[cur] = 0;
		for (int i = carsCount - 1; i != cur; --i) {
			if (w[cur] > w[i])
				result = max(result, lds_mem[i]);
		}
		return result += 1;
	}
	*/

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("i.in");
		freopen_out("i.out");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> carsCount) {
			{
				vector<pair<int, int>> v;
				v.reserve(carsCount);
				for (int i = 0; i < carsCount; ++i) {
					cin >> w[i];
					v.emplace_back(w[i], i);
				}
				sort(v.begin(), v.end());
				/*
				int weightColor = unique(v.begin(), v.end(),
					[ ](const pair<int, int>& a, const pair<int, int>& b) {
						return a.first == b.first;
					}
				);
				*/
				for (int i = 0; i < carsCount; i++)
					w[v[i].second] = i;
			}
			reverse(w, w + carsCount);
			calc_lis();
			calc_lds();
			int max_len = 0;
			for (int i = 0; i < carsCount; ++i) {
				/*
				max_lis = max_lds = 0;
				for (int j = i + 1; j < carsCount; ++j) {
					if (w[i] < w[j])
						max_lis = max(max_lis, lis_mem[j]);
					else
						max_lds = max(max_lds, lds_mem[j]);
				}
				max_len = max(max_len, max_lis + max_lds);
				*/
				max_len = max(max_len, lis_mem[i] + lds_mem[i] - 1);
			}
			cout << max_len << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif