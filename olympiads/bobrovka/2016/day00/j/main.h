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

	int testCount;
	int questionCount;
	int studentCount;

	string to_binary(int n) {
		string result(questionCount, ' ');
		for (auto iter = result.rbegin(); iter != result.rend(); ++iter) {
			*iter = n % 2 + '0';
			n /= 2;
		}
		return result;
	}

	struct StudentMistakes {
		unsigned char data[12];
		friend bool operator < (const StudentMistakes& a, const StudentMistakes& b) {
			return memcmp(a.data, b.data, studentCount) < 0;
		}
		friend StudentMistakes& operator - (const StudentMistakes& lhs, StudentMistakes& rhs) { // EVIL
			for (int i = 0; i < studentCount; ++i)
				rhs.data[i] = lhs.data[i] - rhs.data[i];
			return rhs;
		}
	};

	map<StudentMistakes, pair<int, int>> studentMistakesLeft; // <mistakes, <left mask, count>>
	StudentMistakes studentResult;
	vector<int> studentAnswersLeft;
	vector<int> studentAnswersRight;

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("j.in");
		freopen_out("j.out");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		cin >> testCount;
		while (testCount--) {
			cin >> studentCount >> questionCount;
			int leftCount = questionCount / 2;
			int rightCount = questionCount - leftCount;
			studentMistakesLeft.clear();
			studentAnswersLeft.assign(studentCount, 0);
			studentAnswersRight.assign(studentCount, 0);
			char c;
			for (int i = 0; i < studentCount; ++i) {
				for (int j = 0; j < leftCount; ++j) {
					cin >> c;
					studentAnswersLeft[i] <<= 1;
					studentAnswersLeft[i] += c - '0';
				}
				for (int j = 0; j < rightCount; ++j) {
					cin >> c;
					studentAnswersRight[i] <<= 1;
					studentAnswersRight[i] += c - '0';
				}
				int tmp;
				cin >> tmp;
				studentResult.data[i] = questionCount - tmp;
			}
			
			for (int i = 0; i < (1 << leftCount); ++i) {
				StudentMistakes mistakes;
				for (int j = 0; j < studentCount; ++j)
					mistakes.data[j] = (unsigned char)bitset<15>(i ^ studentAnswersLeft[j]).count();
				auto iter = studentMistakesLeft.find(mistakes);
				if (iter == studentMistakesLeft.end())
					studentMistakesLeft.emplace(mistakes, make_pair(i, 1));
				else
					++iter->second.second;
			}

			int theFirst;
			int count = 0;

			for (int i = 0; i < (1 << rightCount); ++i) {
				StudentMistakes mistakes;
				for (int j = 0; j < studentCount; ++j)
					mistakes.data[j] = (unsigned char)bitset<15>(i ^ studentAnswersRight[j]).count();
				auto p = studentMistakesLeft.find(studentResult - mistakes);
				if (p == studentMistakesLeft.end())
					continue;
				auto cnt = p->second.second;
				if (!count && cnt == 1)
					theFirst = i | p->second.first << rightCount;
				count += cnt;
			}

			if (count == 1)
				cout << to_binary(theFirst) << '\n';
			else
				cout << count << " solutions\n";
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif