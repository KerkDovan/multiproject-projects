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

	struct MultiprojectDebug {
		template<class _Ty> friend MultiprojectDebug&
		operator << (MultiprojectDebug& db, const _Ty&) { return db; }
	} debug;

#endif

// Changeable code continues here. 

	using namespace std;

	typedef long long ll;
	typedef unsigned long long ull;

	template<
		class _Type, 
		_Type _Neutral,
		class _Operation
	>
	class SegmentTree {
	public:
		typedef _Type Type;
		typedef _Operation Operation;
		static const Type neutral = _Neutral;

		size_t size() const { return _size; }

		SegmentTree(size_t size, const Type& initial) {
			_size = size;
			_data_size = size * 4;
			_data = new Type[_data_size];
			for (size_t i = 0; i < _data_size; ++i)
				_data[i] = initial;
		}

		SegmentTree(size_t size) : SegmentTree(size, neutral) {}

		SegmentTree(const std::initializer_list<Type>& list) :
			SegmentTree(list.size())
		{
			size_t i = 0;
			for (
				auto iter = list.begin();
				iter != list.end();
				++i, ++iter)
			{
				singleOperation(i, *iter);
			}
		}

		~SegmentTree() {
			delete[] _data;
		}

		void singleOperation(size_t toChange, const Type& delta) {
			singleOperation(toChange, delta, 0, 0, _size);
		}

		Type getValueOnSegment(size_t l, size_t r) {
			return getValueOnSegment(0, 0, _size, l, r);
		}

	protected:
		static size_t left(size_t id) {
			return (id << 1) + 1;
		}
		static size_t right(const size_t id) {
			return (id << 1) + 2;
		}

		size_t _size;
		size_t _data_size;
		Type* _data;

		void singleOperation(size_t toChange, const Type& delta, size_t id, size_t l, size_t r) {
			if (r - l == 1) {
				_data[id] = Operation()(_data[id], delta);
				return;
			}
			size_t m = (l + r) >> 1;
			size_t n_id;
			if (toChange < m) {
				r = m;
				n_id = left(id);
			}
			else {
				l = m;
				n_id = right(id);
			}
			singleOperation(delta, toChange, n_id, l, r);
			_data[id] = Operation()(_data[left(id)], _data[right(id)]);
		}

		Type getValueOnSegment(size_t id, size_t kl, size_t kr, size_t l, size_t r) {
			if (l == kl && r == kr)
				return _data[id];
			Type result = neutral;
			size_t km = (kl + kr) >> 1;
			if (l < km)
				result = Operation()(result, getValueOnSegment(left(id), kl, km, l, min(km, r)));
			if (r > km)
				result = Operation()(result, getValueOnSegment(right(id), km, kr, max(km, l), r));
			return result;
		}
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t n;
		while (cin >> n) {
			SegmentTree<int, 0, plus<int>> segmentTree(n);
			for (size_t i = 0; i < n; ++i) {
				int tmp;
				cin >> tmp;
				segmentTree.singleOperation(i, tmp);
			}
			for (size_t i = 0; i < n; ++i) {
				for (size_t j = i + 1; j <= n; ++j) {
					cout << '[' << i << ", " << j << ") : " <<
						segmentTree.getValueOnSegment(i, j) << '\n';
				}
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
