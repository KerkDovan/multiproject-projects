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
	
	int eventsCount, interventionsCount, diceSize;
	vector<int> bases;
	vector<vector<int>> p_effects;
	vector<vector<int>> n_effects;
	map<tuple<int, int>, double> dp_mem;

	int interventions;

	double dp(int cur_event, int effects) {
		auto iter = dp_mem.find(make_tuple(cur_event, effects));
		if (iter != dp_mem.end())
			return iter->second;
		int base = bases[cur_event];
		for (int i = 0; i < cur_event; ++i)
			base += effects & 1 << i ? p_effects[i][cur_event - i] : n_effects[i][cur_event - i];
		double p1;
		if (base >= 0)
			p1 = 1.0;
		else if (base + diceSize <= 0)
			p1 = 0.0;
		else
			p1 = (double)(base + diceSize) / (double)diceSize;
		if (cur_event == eventsCount - 1)
			return dp_mem[make_tuple(cur_event, effects)] = p1;
		double p2 = 1.0 - p1;
		double f1 = dp(cur_event + 1, effects | 1 << cur_event);
		double f2 = dp(cur_event + 1, effects);
		auto& result = dp_mem[make_tuple(cur_event, effects)] = (
			p1 * f1 + p2 * f2
		);
		if (result == 0.0 && interventions != interventionsCount) {
			++interventions;
			result = max(f1, f2);
		}
		return result;
	}

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("b.in");
		freopen_out("b.out");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> eventsCount >> interventionsCount >> diceSize) {
			bases.resize(eventsCount);
			p_effects.resize(eventsCount);
			n_effects.resize(eventsCount);
			dp_mem.clear();
			for (int i = 0; i < eventsCount - 1; ++i) {
				cin >> bases[i];
				int cnt = eventsCount - i;
				p_effects[i].resize(cnt);
				for (int j = 0; j < cnt; ++j)
					cin >> p_effects[i][j];
				n_effects[i].resize(cnt);
				for (int j = 0; j < cnt; ++j)
					cin >> n_effects[i][j];
			}
			cin >> bases[eventsCount - 1];
			
			cout << fixed << setprecision(6) << dp(0, 0) << '\n';

		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif