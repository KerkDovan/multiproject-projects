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

	int eventsCount;
	map<int, int> correct; // <id, time>
	vector<int> answers; // [] <id>
	vector<int> lis_mem; // [id] <lis_len>

	int lis(int cur) { // (id) -> lis_len
		int& result = lis_mem[cur];
		result = 0;
		for (int i = 0; i < cur; ++i) {
			if (correct[answers[i]] < correct[answers[cur]])
				result = max(result, lis_mem[i]);
		}
		return result += 1;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> eventsCount) {
			correct.clear();
			for (int i = 0; i < eventsCount; ++i) {
				int event_id;
				cin >> event_id;
				correct.emplace(event_id, i);
			}
			answers.resize(eventsCount);
			lis_mem.resize(eventsCount);
			int event_id = -1;
			while (cin >> event_id, ~event_id) {
				answers[0] = event_id;
				for (int i = 1; i < eventsCount; ++i)
					cin >> answers[i];
				int max_len = 0;
				for (int i = 0; i < eventsCount; ++i)
					max_len = max(max_len, lis(i));
				cout << max_len << '\n';
				event_id = -1;
			}
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif