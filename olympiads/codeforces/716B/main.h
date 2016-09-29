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

	inline bool appropriate(int* times) {
		for (int i = 0; i < 26; ++i)
			if (times[i] > 1)
				return false;
		return true;
	}

	string& createGoodWord(int* times, string& str, size_t start) {
		for (size_t i = 0; i < start; ++i)
			str[i] = (str[i] == 26 ? 'A' : str[i] + 'A');
		char cur = 0;
		for (size_t i = start; i < start + 26; ++i) {
			while (times[cur])
				++cur;
			if (str[i] != 26)
				str[i] = str[i] + 'A';
			else {
				str[i] = cur + 'A';
				times[cur] = 1;
			}
		}
		for (size_t i = start + 26; i < str.size(); ++i)
			str[i] = (str[i] == 26 ? 'A' : str[i] + 'A');
		return str;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		string str;
		str.reserve(50000);
		while (getline(cin, str), str != "") {
			if (str.size() < 26)
				cout << "-1\n";
			else {
				while (true) {
					for (char& c : str) {
						if (c == '?')
							c = 26;
						else
							c -= 'A';
					}
					int times[27] = {};
					for (size_t i = 0; i < 26; ++i)
						++times[str[i]];
					if (appropriate(times)) {
						cout << createGoodWord(times, str, 0) << '\n';
						break;
					}
					bool ex = false;
					for (size_t i = 26; i < str.size(); ++i) {
						--times[str[i - 26]];
						++times[str[i]];
						if (appropriate(times)) {
							cout << createGoodWord(times, str, i - 26 + 1) << '\n';
							ex = true;
							break;
						}
					}
					if (!ex)
						cout << "-1\n";
					break;
				}
			}
			str = "";
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif