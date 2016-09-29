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

	inline bool nextDate(int& date, int& points) {
		string line;
		getline(cin, line);
		if (line == "" || line == "\n")
			return false;
		date = points = 0;
		size_t i = 0;
		while (line[i] != ' ') {
			date *= 10;
			date += line[i] - '0';
			++i;
		}
		while (line[i] == ' ')
			++i;
		while (i < line.size()) {
			points *= 10;
			points += line[i] - '0';
			++i;
		}
		return true;
	}

	inline string strDate(int date) {
		string dd, mm, yyyy;
		// day
		dd = date % 10;
		date /= 10;
		dd += date % 10;
		date /= 10;
		swap(dd[0], dd[1]);
		// month
		mm = date % 10;
		date /= 10;
		mm += date % 10;
		date /= 10;
		swap(mm[0], mm[1]);
		// year
		while (date) {
			yyyy += date % 10;
			date /= 10;
		}
		reverse(yyyy.begin(), yyyy.end());
		return yyyy + '-' + mm + '-' + dd;
	}

	void printVerdict(int date, int merit, int demerit) {
		cout << strDate(date) << ' ';
		if (merit + demerit) {
			if (merit)
				cout << merit << " merit";
			else
				cout << demerit << " demerit";
			cout << " point(s).\n";
		}
		else
			cout << "No merit or demerit points.\n";
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int testCount;
		while (cin >> testCount) {
			while (testCount--) {
				int merit = 0, demerit = 0;
				int prevDemeritDate = 0, curDate, date, points;
				cin >> curDate;
				printVerdict(curDate, merit, demerit);
				while (nextDate(date, points)) {

				}
			}
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif