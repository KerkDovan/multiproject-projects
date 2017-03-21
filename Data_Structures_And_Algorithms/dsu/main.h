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

	template<class _Ty>
	class DSU {
	public:
		typedef _Ty ElementType;
		DSU() {}
		~DSU() {
			for (auto s : _sets)
				delete s.second;
		}
		_Ty& makeSet(const _Ty& element) {
			auto iter = _sets.find(element);
			if (iter == _sets.end()) {
				_sets.emplace(element, new Tree(element));
				return _sets.find(element)->second->_value;
			}
			return iter->second->_value;
		}
		_Ty& find(const _Ty& element) {
			return findTree(element)->_value;
		}
		_Ty& unite(const _Ty& el1, const _Ty& el2) {
			auto iter1 = findTree(el1), iter2 = findTree(el2);
			if (iter1 == iter2)
				return iter1->_value;
			if (iter1->_rank < iter2->_rank)
				swap(iter1, iter2);
			iter2->_parent = iter1;
			iter1->_rank = max(iter1->_rank, iter2->_rank + 1);
			return iter1->_value;
		}
	private:
		struct Tree {
			_Ty _value;
			Tree* _parent;
			size_t _rank;
			Tree(const _Ty& val) : _value(val), _parent(nullptr), _rank(1) {}
		};
		Tree* findTree(const _Ty& element) {
			auto iter = _sets.find(element);
			if (iter == _sets.end())
				throw "No such element in DSU";
			if (iter->second->_parent == nullptr)
				return iter->second;
			return iter->second = findTree(iter->second->_parent->_value);
		}
		map<_Ty, Tree*> _sets;
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		DSU<int> dsu;
		dsu.makeSet(1);
		dsu.makeSet(2);
		dsu.makeSet(3);
		dsu.makeSet(4);
		dsu.makeSet(5);

		cout << dsu.find(4) << '\n';

		dsu.unite(1, 4);
		dsu.unite(3, 5);
		cout << '\n';

		cout << dsu.find(4) << '\n';
		cout << dsu.find(1) << '\n';
		cout << dsu.find(2) << '\n';

		dsu.unite(5, 2);
		cout << '\n';

		cout << dsu.find(5) << '\n';
		cout << dsu.find(3) << '\n';

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
