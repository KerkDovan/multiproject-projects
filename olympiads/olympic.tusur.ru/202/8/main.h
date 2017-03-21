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

	typedef long long ll;
	typedef unsigned long long ull;

	map<string, char> ranks = {
		{  "A", 't' },
		{  "2", 'f' },
		{  "3", 'f' },
		{  "4", 'f' },
		{  "5", 'f' },
		{  "6", 't' },
		{  "7", 't' },
		{  "8", 't' },
		{  "9", 't' },
		{ "10", 't' },
		{  "J", 't' },
		{  "Q", 't' },
		{  "K", 't' },
	};

	map<string, char> suits = {
		{ "C", 't' },
		{ "D", 't' },
		{ "H", 't' },
		{ "S", 't' },
		{ "B", 'f' },
		{ "R", 'f' },
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		string card;
		while (getline(cin, card)) {
			string rank, suit;
			if (card.size() == 2) {
				rank += card[0];
				suit += card[1];
			}
			else {
				rank += card[0];
				rank += card[1];
				suit += card[2];
			}
			char r, s;
			r = ranks[rank];
			s = suits[suit];
			if (r == 0 || s == 0) {
				cout << "MAGIC";
			}
			else if (r == 'f' || s == 'f') {
				if (suit == "B" || suit == "R")
					if (rank == "J")
						cout << "FULL";
					else
						cout << "MAGIC";
				else
					cout << "FULL";
			}
			else {
				cout << "FULL TRIMMED";
			}
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
