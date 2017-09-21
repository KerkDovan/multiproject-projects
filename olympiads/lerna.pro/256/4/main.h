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
#ifdef MYLIB
	using namespace MyLib;
#endif // MYLIB

	typedef long long ll;
	typedef unsigned long long ull;

	string toBin(unsigned int num) {
		string result;
		while (num) {
			result += num % 2 + '0';
			num /= 2;
		}
		while (result.size() < 32)
			result += '0';
		reverse(result.begin(), result.end());
		return result;
	}

	int strToInt(const string& str) {
		int result = 0;
		for (char c : str)
			(result *= 10) += (int)(c - '0');
		return result;
	}

	int ipToInt(string ip) {
		ip += '.';
		int result = 0;
		size_t i = 0;
		string tmp;
		while (i < ip.size()) {
			if (ip[i] == '.')
				(result <<= 8) += strToInt(tmp),
				tmp = "";
			else
				tmp += ip[i];
			++i;
		}
		return result;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		vector<int> masks(32);
		int mask = 0;
		for (int i = 0; i < 32; ++i) {
			(mask <<= 1) |= 1;
			masks[31 - i] = ~mask;
		}

		for (int i : masks)
			debug << toBin(i) << '\n';

		int n, k;
		while (cin >> n >> k) {
			map<int, vector<int>> masked[32];
			vector<int> ips;
			ips.reserve(n);
			string ip;
			for (int i = 0; i < n; ++i) {
				cin >> ip;
				ips.emplace_back(ipToInt(ip));
				for (int i = 0; i < 32; ++i)
					masked[i][ips.back() & masks[i]].emplace_back(ips.size() - 1);
			}
			for (int i : ips)
				cout << toBin(i) << '\n';
			cout << '\n';
			for (int i = 0; i < 32; ++i) {
				cout << i << '\t' << toBin(masks[i]) << '\n';
				for (auto p : masked[i]) {
					cout << "\t#\t" << toBin(p.first) << '\n';
					for (int j : p.second)
						cout << "\t##\t" << toBin(ips[j]) << '\n';
				}
				cout << '\n';
			}
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
