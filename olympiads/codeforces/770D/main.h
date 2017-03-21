﻿// Changeable code starts here. 

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

	struct Tree {
	public:
		Tree(const string& src, size_t from, size_t to) {
			queue<size_t> ids;
			size_t cnt = 0;
			for (size_t i = from; i < to; ++i) {
				// for '['
				if (cnt == 0)
					ids.emplace(i);
				src[i] == '[' ? ++cnt : --cnt;
				// for ']'
				if (cnt == 0)
					ids.emplace(i);
			}
			while (!ids.empty()) {
				size_t tmp = ids.front();
				ids.pop();
				children.emplace_back(src, tmp + 1, ids.front());
				ids.pop();
			}
		}

		size_t get_depth() {
			if (~depth)
				return depth;
			depth = 0;
			for (Tree& child : children)
				depth = max(depth, child.get_depth() + 1);
			return depth;
		}
		void set_depth(size_t new_depth) {
			depth = new_depth--;
			for (Tree& child : children)
				child.set_depth(new_depth);
		}

		size_t draw(vector<string>& canvas, size_t col) const {
			size_t row1 = canvas.size() / 2 - depth + 1;
			size_t row2 = canvas.size() - row1;
			if (row2 < row1)
				swap(row1, row2);
			if (children.empty()) {
				if (depth > 0)
					--row1, ++row2;
				for (size_t i = row1; i < row2; ++i)
					canvas[i] += "   ";
				return col + 3;
			}
			//cout << canvas.size() << ' ' << depth << ' ' << row1 << ' ' << row2 << '\n';
			for (const Tree& child : children) {
				//cout << child.depth << ' ' << row1 << ' ' << row2 << '\n';
				canvas[row1 - 1] += "+-";
				canvas[row2] += "+-";
				for (size_t i = row1; i < row2; ++i)
					canvas[i] += '|';

				col = child.draw(canvas, col + 1);

				while (canvas[row1 - 1].size() < col - 1)
					canvas[row1 - 1] += ' ';
				while (canvas[row2].size() < col - 1)
					canvas[row2] += ' ';

				canvas[row1 - 1] += "-+";
				canvas[row2] += "-+";
				for (size_t i = row1; i < row2; ++i)
					canvas[i] += "|";

				col += 1;
			}
			return col;
		}

	private:
		vector<Tree> children;
		size_t depth = (size_t)-1;
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t len;
		string seq;
		while (cin >> len >> seq) {
			Tree root(seq, 0, len);
			root.set_depth(root.get_depth());

			vector<string> result(2 * root.get_depth() + 1, "");
			root.draw(result, 0);

			for (const string& line : result)
				cout << line << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
