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

	typedef unsigned char uchar;
	typedef long long ll;
	typedef unsigned long long ull;

	inline bool operator == (const vector<uchar>& lhs, const vector<uchar>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); ++i) {
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}

	inline bool all_different(const vector<uchar>& a) {
		short cnt[7] = {};
		for (const uchar& c : a)
			if (++cnt[c] > 1)
				return false;
		return true;
	}

	inline bool all_different(const vector<uchar>& a, const vector<uchar>& b) {
		short cnt[7] = {};
		for (const uchar& c : a)
			if (++cnt[c] > 1)
				return false;
		for (const uchar& c : b)
			if (++cnt[c] > 1)
				return false;
		return true;
	}

	inline vector<uchar> nxt(const vector<uchar>& num, const vector<uchar>& mod) {
		vector<uchar> result = num;
		//if (num.size() == 1 && num[0] == 0)
		//	result.assign(mod.size(), 0);
		for (size_t i = 0; i != result.size(); ++i) {
			++result[i];
			if (result[i] < 7)
				break;
			result[i] = 0;
		}
		if (result == mod)
			result.assign(mod.size(), 0);
		return result;
	}

	vector<uchar> hours, minutes, h_mod, m_mod;

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int hoursCount, minutesCount;
		while (cin >> hoursCount >> minutesCount) {
			int hh_cnt = 0, mm_cnt = 0;
			for (int tmp_h = hoursCount; tmp_h; tmp_h /= 7)
				++hh_cnt;
			for (int tmp_m = minutesCount; tmp_m; tmp_m /= 7)
				++mm_cnt;
			int total = 0;
			if (hh_cnt + mm_cnt <= 7) {
				h_mod.assign(hh_cnt, 0);
				for (int tmp_h = hoursCount, i = 0; tmp_h; tmp_h /= 7, ++i)
					h_mod[i] = tmp_h % 7;
				m_mod.assign(mm_cnt, 0);
				for (int tmp_m = minutesCount, i = 0; tmp_m; tmp_m /= 7, ++i)
					m_mod[i] = tmp_m % 7;
				hours = vector<uchar>(hh_cnt, 0);
				for (int h = 0; h < hoursCount; ++h) {
					minutes = vector<uchar>(mm_cnt, 0);
					for (int m = 0; m < minutesCount; ++m) {
						minutes = nxt(minutes, m_mod);
						if (all_different(hours, minutes))
							++total;
					}
					hours = nxt(hours, h_mod);
					if (!all_different(hours))
						continue;
				}
			}
			cout << total << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif