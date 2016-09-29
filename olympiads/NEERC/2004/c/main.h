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

#endif

// Changeable code continues here. 

	using namespace std;

	typedef long long ll;
	typedef unsigned long long ull;

	const int INF = 2 * 1000 * 1000 * 1000;

	struct Tree {
		Tree() : children({}), from(0) {}
		~Tree() {
			for (Tree* child : children)
				delete child;
		}
		vector<Tree*> children;
		size_t from;
		friend ostream& operator << (ostream& os, Tree* tree) {
			if (tree->children.empty())
				os << 'a';
			else {
				size_t i = tree->from;
				do {
					os << tree->children[i];
					++i %= tree->children.size();
				} while (i != tree->from);
				os << tree->children.size();
			}
			return os;
		}
	};

	int find_first(Tree* tree) {
		if (tree->children.empty())
			return 1;

		vector<int> costs(tree->children.size());
		for (size_t i = 0; i < costs.size(); ++i)
			costs[i] = find_first(tree->children[i]);

		int min_cost = INF;
		for (size_t i = 0; i < costs.size(); ++i) {
			int max_cost = 0, sum_cost = 0;
			size_t j = i;
			do {
				max_cost = max(max_cost, sum_cost + costs[j]);
				++sum_cost;
				++j %= costs.size();
			} while (j != i);
			if (max_cost < min_cost) {
				min_cost = max_cost;
				tree->from = i;
			}
		}

		return min_cost;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		string line;
		while (cin >> line) {
			stack<Tree*> stck;
			for (char c : line) {
				Tree* tmp = new Tree();
				if (c != 'a') {
					while (c-- != '0') {
						tmp->children.emplace_back(stck.top());
						stck.pop();
					}
					reverse(tmp->children.begin(), tmp->children.end());
				}
				stck.push(tmp);
			}
			cout << find_first(stck.top()) << '\n' << stck.top() << '\n';
			delete stck.top();
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif