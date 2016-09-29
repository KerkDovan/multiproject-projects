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

	class BigInteger {
	public:
		BigInteger() { data.assign(1, 0); }
		BigInteger(ull value) { data.assign(1, value); *this += BigInteger(); }
		bool operator == (ull rhs) const {
			return data.size() == 1 && data[0] == rhs;
		}
		bool operator != (ull rhs) const {
			return !(*this == rhs);
		}
		BigInteger& operator += (const BigInteger& rhs) {
			for (size_t i = data.size(); i < rhs.data.size(); ++i)
				data.emplace_back(0);
			data.emplace_back(0);
			for (size_t i = 0; i < data.size(); ++i) {
				if (i < rhs.data.size())
					data[i] += rhs.data[i];
				if (data[i] >= modulo) {
					data[i + 1] += data[i] / modulo;
					data[i] %= modulo;
				}
			}
			while (data.size() > 1 && data.back() == 0)
				data.pop_back();
			return *this;
		}
		friend ostream& operator << (ostream& os, const BigInteger& bi) {
			string result;
			BigInteger big = bi;
			size_t id = 0;
			while (id != big.data.size()) {
				if (id != big.data.size() - 1) {
					for (int i = 0; i < 15; ++i) {
						result += big.data[id] % 10 + '0';
						big.data[id] /= 10;
					}
				}
				else {
					while (big.data[id]) {
						result += big.data[id] % 10 + '0';
						big.data[id] /= 10;
					}
				}
				++id;
			}
			reverse(result.begin(), result.end());
			return os << result;
		}
	private:
		vector<ull> data;
		static const ull modulo = (ull)1000 * 1000 * 1000 * 1000 * 1000;
	};

	BigInteger dp_mem[1820][11][11];
	
	BigInteger dp(int length, int base, int digit) {
		BigInteger& result = dp_mem[length][base][digit];
		if (result != -1)
			return result;
		if (length == 1)
			return result = 1;
	
		result = 0;
		if (digit != 0)
			result += dp(length - 1, base, 0);
		for (int i = 1; i < base; ++i)
			result += dp(length - 1, base, i);
	
		return result;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		for (int i = 0; i < 2000; ++i)
			for (int j = 0; j < 11; ++j)
				for (int k = 0; k < 11; ++k)
					dp_mem[i][j][k] = -1;

		int len, base;
		while (cin >> len >> base) {
			cout << dp(len + 1, base, 0) << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif