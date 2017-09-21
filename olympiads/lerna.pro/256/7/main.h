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

	int toInt(const string& str) {
		int result = 0;
		for (char c : str)
			(result *= 10) += c - '0';
		return result;
	}

	pair<string, vector<int>> split_input(const string& input) {
		string res1;
		vector<int> res2;
		size_t i = 0;
		while (i < input.size() && input[i] != ' ')
			res1 += input[i++];
		string tmp;
		while (++i != input.size()) {
			if (input[i] != ' ' && input[i] != '\t')
				tmp += input[i];
			else
				res2.emplace_back(toInt(tmp)),
				tmp = "";
		}
		if (tmp != "")
			res2.emplace_back(toInt(tmp));
		return make_pair(res1, res2);
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int n, m;
		while (cin >> n >> m >> ws) {
			vector<vector<int>> letters(m);
			for (int i = 0; i < n; ++i) {
				string input;
				getline(cin, input);
				string tmp1;
				vector<int> tmp2;
				tie(tmp1, tmp2) = split_input(input);
				
				for (char c : tmp1) {
					int t = (int)(c - 'A');
					if (letters[t].empty()) {
						letters[t] = tmp2;
					}
					else {
						sort(letters[t].begin(), letters[t].end());
						sort(tmp2.begin(), tmp2.end());
						vector<int> tmp(min(tmp2.size(), letters[t].size()));
						auto iter = set_intersection(letters[t].begin(), letters[t].end(), tmp2.begin(), tmp2.end(), tmp.begin());
						tmp.resize(iter - tmp.begin());
						letters[t] = tmp;
					}
				}
			}

			for (vector<int>& letter : letters)
				sort(letter.begin(), letter.end());
			bool no_changes = false;
			size_t visited_cnt = 0;
			vector<bool> visited(letters.size());
			while (visited_cnt != visited.size() && !no_changes) {
				no_changes = true;
				for (int i = 0; i < (int)letters.size(); ++i) {
					if (!visited[i] && letters[i].size() == 1) {
						no_changes = false;
						++visited_cnt;
						visited[i] = true;
						for (int j = 0; j < (int)letters.size(); ++j) {
							if (i == j)
								continue;
							letters[j].erase(remove(letters[j].begin(), letters[j].end(), letters[i][0]), letters[j].end());
						}
					}
				}
			}

			bool possible = true;
			int zeros = 0;
			set<int> unused;
			for (int i = 0; i < (int)letters.size(); ++i)
				unused.emplace(i);
			for (const vector<int>& letter : letters) {
				if (letter.size() > 1) {
					possible = false;
					break;
				}
				if (letter.size() == 0)
					++zeros;
				else
					unused.erase(letter[0]);
			}
			if (zeros > 1)
				possible = false;
			else if (zeros == 1 && unused.size() == 1) {
				for (vector<int>& letter : letters)
					if (letter.size() == 0)
						letter.emplace_back(*unused.begin());
			}

			if (possible) {
				cout << "YES\n";
				for (const vector<int>& letter : letters)
					cout << *letter.begin() << ' ';
				cout << '\n';
			}
			else {
				cout << "NO\n";
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
