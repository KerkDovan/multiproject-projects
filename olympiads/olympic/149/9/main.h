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
#include <tuple>
#include <vector>

#define stringify(str) stringify2(str)
#define stringify2(str) #str

// Changeable code stops here. 
	
#ifdef _LOCAL_MULTIPROJECT_

#include "multiproject.h"

namespace project {

#else

#include <iostream>

#define breakpoint_if(condition)
#define breakpoint
#define debug_output(...)
#define freopen_in(filename) freopen(filename, "r", stdin)
#define freopen_out(filename) freopen(filename, "w", stdout)
#define close_files

#endif

// Changeable code continues here. 

	using namespace std;

	typedef long long ll;
	typedef unsigned long long ull;

	ull gcd(ull a, ull b) {
		while (b) {
			a %= b;
			swap(a, b);
		}
		return a;
	}

	void reduce(ull& a, ull& b) {
		ull g = gcd(a, b);
		a /= g;
		b /= g;
	}

	vector<ull> three_degrees;
	vector<vector<ull>> dp_mem;
	vector<ull> dp_res;

	void dp(size_t count) {
		for (size_t i = 0; i <= count - 5; ++i)
			dp_mem[count][i] = dp_mem[count - 1][i] * 3 - (i >= 5 ? dp_mem[count - 5][i - 5] : 0);
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		three_degrees.resize(41);
		three_degrees[0] = 1;
		for (size_t i = 1; i < three_degrees.size(); ++i)
			three_degrees[i] = three_degrees[i - 1] * 3;

		dp_mem.resize(41, vector<ull>(41, 0));
		dp_mem[5][0] = 1;
		dp_mem[6][0] = dp_mem[6][1] = 3;
		dp_res.resize(41, 0);
		dp_res[5] = 1;
		dp_res[6] = 6;
		for (size_t i = 7; i < dp_mem.size(); ++i) {
			dp(i);
			for (auto j : dp_mem[i])
				dp_res[i] += j;
		}
		for (size_t i = 6; i < dp_res.size(); ++i)
			reduce(dp_res[i], three_degrees[i]);

		int n;
		while (cin >> n)
			cout << dp_res[n] << '/' << three_degrees[n] << '\n';

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif