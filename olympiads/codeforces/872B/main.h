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
#ifdef MYLIB
	using namespace MyLib;
#endif // MYLIB

	typedef long long ll;
	typedef unsigned long long ull;

	class Tree {
	public:
		Tree(size_t size) {
			_size = size;
			_nodes.resize(size * 4);
		}
		void insert(size_t pos, int val) {
			_insert(0, _size, pos, 0, val);
		}
		int get_min(size_t left, size_t right) const {
			return _get_min(left, right, 0, _size, 0);
		}
	private:
		size_t _size;
		vector<int> _nodes;
		void _insert(size_t left, size_t right, size_t pos, size_t cur, int val) {
			if (right - left == 1) {
				_nodes[cur] = val;
				return;
			}
			size_t mid = (right + left - 1) / 2 + 1;
			if (pos < mid)
				_insert(left, mid, pos, cur * 2 + 1, val);
			else
				_insert(mid, right, pos, cur * 2 + 2, val);
			_nodes[cur] = min(_nodes[cur * 2 + 1], _nodes[cur * 2 + 2]);
		}
		int _get_min(size_t left, size_t right, size_t cur_l, size_t cur_r, size_t cur) const {
			if (left == cur_l && right == cur_r)
				return _nodes[cur];
			size_t mid = (cur_r + cur_l - 1) / 2 + 1;
			if (right <= mid)
				return _get_min(left, right, cur_l, mid, cur * 2 + 1);
			if (left >= mid)
				return _get_min(left, right, mid, cur_r, cur * 2 + 2);
			return min(_get_min(left, mid, cur_l, mid, cur * 2 + 1),
				_get_min(mid, right, mid, cur_r, cur * 2 + 2));
		}
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t n, k;
		while (cin >> n >> k) {
			if (k == 1 || k >= 3) {
				auto fn = [&](int a, int b) { return (k == 1 ? min(a, b) : max(a, b)); };
				int x;
				cin >> x;
				for (size_t i = 1; i < n; ++i) {
					int tmp;
					cin >> tmp;
					x = fn(x, tmp);
				}
				cout << x << '\n';
			}
			else {
				Tree tree(n);
				for (size_t i = 0; i < n; ++i) {
					int tmp;
					cin >> tmp;
					tree.insert(i, tmp);
				}
				int x = tree.get_min(0, 1);
				for (size_t i = 1; i < n; ++i)
					x = max({ x, tree.get_min(0, i), tree.get_min(i, n), });
				cout << x << '\n';
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
