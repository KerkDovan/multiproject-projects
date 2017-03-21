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

	pair<size_t, size_t> tryEmplace(const string& field, size_t pos, size_t len) { // <right, cnt>
		size_t right = pos;
		while (right < field.size() && field[right] != '1')
			++right;
		size_t cnt = (right - pos) / len;
		return make_pair(right, cnt);
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t n, a, b, k;
		while (cin >> n >> a >> b >> k >> ws) {
			string field;
			getline(cin, field);
			vector<size_t> poses; // <pos, cnt>
			size_t pos = 0, cnt = 0, tmp = 0;
			while (pos < field.size()) {
				if (field[pos] == '1') {
					++pos;
					continue;
				}
				size_t old = pos;
				tie(pos, tmp) = tryEmplace(field, pos, b);
				for (size_t i = 0; i < tmp; ++i)
					poses.emplace_back(old + i * b);
				cnt += tmp;
			}
			size_t shoots = cnt - a + 1;
			cout << shoots << '\n';
			for (size_t i = 0; i < shoots && i < poses.size(); ++i)
				cout << poses[i] + b << ' ';
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
