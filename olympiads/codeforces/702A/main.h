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

	size_t seqSize;
	vector<int> sequence;
	vector<size_t> lia_mem;

	size_t lia(size_t cur) {
		size_t& result = lia_mem[cur] = 1;
		if (sequence[cur] > sequence[cur - 1])
			result = lia_mem[cur - 1] + 1;
		return result;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> seqSize) {
			sequence.clear();
			sequence.resize(seqSize + 1);
			lia_mem.clear();
			lia_mem.resize(seqSize + 1);
			size_t max_len = 0;
			for (size_t i = 1; i <= seqSize; ++i) {
				cin >> sequence[i];
				max_len = max(max_len, lia(i));
			}
			cout << max_len << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif