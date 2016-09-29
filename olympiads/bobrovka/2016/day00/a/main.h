// Changeable code starts here. 

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
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

	struct Word {
		int pos, len;
	};

	char s[500001];
	vector<Word> words;
	int indices[500000];

	int readLine(char s[]) {
		int i;
		for (i = 0; s[i] = (char)getchar(), s[i] != '\n'; i++)
			;
		s[i] = '\0';
		return i;
	}

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("a.in");
		freopen_out("a.out");
	//#endif
		
		//ios_base::sync_with_stdio(false);
		//cin.tie(NULL);
		int a, b, n;
		words.reserve(250001);
		while (readLine(s), scanf("%d%d", &a, &b) == 2) {
			words.clear();
			bool sp = true;
			int curWord = 0;
			for (n = 0; s[n]; n++) {
				if (s[n] == ' ')
					curWord++;
				indices[n] = curWord;
				if (sp) {
					words.push_back({ n, 0 });
					sp = false;
				}
				else if (s[n] == ' ') {
					words.back().len = n - words.back().pos;
					sp = true;
				}
			}
			words.back().len = n - words.back().pos;
			//for (auto w: words)
			//  debug << w.pos _ w.len << '\n';
			for (int w = a; w <= b; w++) {
				int result = 0;
				int i = 0;
				while (result += words[i].len + 1, words[i].pos + w < n)
					i = indices[words[i].pos + w];
				printf("%d\n", result - 1);
			}
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif