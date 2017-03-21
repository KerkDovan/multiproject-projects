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

	

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int n, m;
		while (cin >> n >> m) {
			vector<int> bands(n);
			vector<int> fav(m, 0); // favourite
			vector<int> unfav; // not favourite positions
			vector<vector<int>> posns(m); // [fav band][] -> position
			for (int i = 0; i < n; ++i) {
				cin >> bands[i];
				--bands[i];
				if (bands[i] < m) {
					++fav[bands[i]];
					posns[bands[i]].push_back(i);
				}
				else
					unfav.push_back(i);
			}

			multimap<int, int> cnts; // <count, band>
			for (int i = 0; i < m; ++i)
				cnts.emplace(fav[i], i);

			size_t to_change = unfav.size();
			for (size_t i = 0; i < unfav.size(); ++i) {
				auto iter = cnts.begin();

				int f = iter->second, fc = iter->first;

				cnts.erase(iter);

				cnts.emplace(fc + 1, f);
				bands[unfav[i]] = f;
				posns[f].push_back(unfav[i]);
			}

			auto fst = cnts.begin(), lst = cnts.end();
			--lst;
			while (lst->first - fst->first > 1) {
				++to_change;
				if (posns[lst->second].empty())
					break;

				int f = fst->second, fc = fst->first;
				int l = lst->second, lc = lst->first;

				cnts.erase(fst);
				cnts.erase(lst);

				posns[f].push_back(posns[l].back());
				posns[l].pop_back();
				bands[posns[f].back()] = f;

				cnts.emplace(fc + 1, f);
				cnts.emplace(lc - 1, l);

				fst = cnts.begin();
				lst = cnts.end();
				--lst;
			}

			cout << cnts.begin()->first << ' ' << to_change << '\n';
			for (int band : bands)
				cout << band + 1 << ' ';
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