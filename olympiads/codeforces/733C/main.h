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

		int n, k;
		while (cin >> n) {
			vector<int> before(n);
			for (auto& monster : before)
				cin >> monster;
			cin >> k;
			vector<int> after(k);
			for (auto& monster : after)
				cin >> monster;

			vector<pair<size_t, bool>> order; // []<id, eats right>
			vector<size_t> ids(n);
			for (size_t i = 0; i < n; ++i)
				ids[i] = i + 1;
			size_t cur = 0;
			for (size_t i = 0; i < after.size(); ++i) {
				int tmp_sum = 0;
				size_t maxMonsterId = (size_t)-1;
				int maxMonsterWeight = -1;
				for (size_t j = cur; j < before.size(); ++j) {
					tmp_sum += before[j];
					if (before[j] > maxMonsterWeight && 
						j != cur && before[j - 1] < before[j] ||
						j != before.size() - 1 && before[j + 1] < before[j] &&
						tmp_sum < after[i] || tmp_sum == after[i])
					{
						maxMonsterId = j;
						maxMonsterWeight = before[j];
					}
					if (tmp_sum < after[i])
						continue;
					if (tmp_sum > after[i] || maxMonsterId == -1) {
						cur = (size_t)-1;
						break;
					}
					size_t id = maxMonsterId;
					int wgt = maxMonsterWeight;
					size_t l = id - 1, r = id + 1;
					while (l != cur - 1 || r != j + 1) {
						if (l != cur - 1 && l != -1 && before[l] < wgt) {
							order.emplace_back(ids[id], false);
							wgt += before[l];
							for (size_t t = id - 1; t < ids.size(); ++t)
								--ids[t];
							--l;
						}
						else if (r != j + 1 && r != before.size() && before[r] < wgt) {
							order.emplace_back(ids[id], true);
							wgt += before[r];
							for (size_t t = id + 1; t < ids.size(); ++t)
								--ids[t];
							++r;
						}
						else if (l != cur || r != j) {
							cur = (size_t)-1;
							break;
						}
					}
					cur = j + 1;
					if (tmp_sum == after[i])
						break;
					tmp_sum = 0;
					maxMonsterId = (size_t)-1;
					maxMonsterWeight = -1;
				}
				if (cur == (size_t)-1)
					break;
			}
			if (cur == (size_t)-1 || order.size() == 0) {
				cout << "NO\n";
				continue;
			}
			cout << "YES\n";
			for (const auto& p : order) {
				cout << p.first << (p.second ? " R\n" : " L\n");
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
