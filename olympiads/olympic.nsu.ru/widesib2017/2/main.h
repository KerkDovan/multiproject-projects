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

	struct Trie {
		map<char, Trie> nxt;
		Trie* add(const string& str, size_t id = 0) {
			if (id == str.size() - 1)
				return nullptr;
			return nxt[str[id]].add(str, ++id);
		}
	};

	int main() {
		freopen_in("input.txt");
		freopen_out("output.txt");

		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t cnt;
		cin >> cnt;
		while (cin >> cnt >> ws) {
			Trie trie, *tmp = &trie;
			size_t max_size = 0;
			for (size_t i = 0; i < cnt; ++i) {
				string str;
				getline(cin, str);
				trie.add(' ' + str);
				max_size = max(max_size, str.size());
			}
			bool ag = false; // answer given
			while (tmp->nxt.size()) {
				if (tmp->nxt.size() > 1) {
					cout << "Impossible\n";
					ag = true;
					break;
				}
				tmp = &tmp->nxt.begin()->second;
			}
			if (!ag)
				cout << max_size << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
