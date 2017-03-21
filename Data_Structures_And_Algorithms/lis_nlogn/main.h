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

	template<class _Ty>
	vector<size_t> compress(const vector<_Ty>& arr) {
		multimap<_Ty, size_t> tmp; // <val, id>
		for (size_t i = 0; i < arr.size(); ++i)
			tmp.emplace(arr[i], i);
		size_t i = 0;
		vector<size_t> result(arr.size());
		for (auto iter = tmp.begin(); iter != tmp.end(); ++iter)
			result[iter->second] = i++;
		return result;
	}

	template<class _Ty>
	vector<_Ty> lis(const vector<_Ty>& sequence) {
		struct Pair {
			size_t a = 1, b = (size_t)(-1);
		};
		struct Max {
			inline Pair operator () (const Pair& lhs, const Pair& rhs) const {
				if (lhs.a == rhs.a) {
					if (lhs.b == (size_t)(-1))
						return rhs;
					return lhs;
				}
				if (lhs.a < rhs.a)
					return rhs;
				return lhs;
			}
		};
		vector<size_t> arr = compress(sequence);
		SegmentTree<Pair, Pair(), Max> segTree(arr.size());
		vector<size_t> ids(arr.size()); // [val] -> id
		for (size_t i = 0; i < arr.size(); ++i)
			ids[arr[i]] = i;
		
	}

	template<class _Ty>
	size_t lis_len(const vector<_Ty>& sequence) {
		struct Max {
			inline size_t operator () (size_t lhs, size_t rhs) const {
				return max(lhs, rhs);
			}
		};
		vector<size_t> arr = compress(sequence);
		SegmentTree<size_t, 0, Max> segTree(arr.size(), 0);
		size_t result = 0;
		for (size_t i = 0; i < arr.size(); ++i) {
			size_t tmp = segTree.getValueOnSegment(0, arr[i]) + 1;
			segTree.singleOperation(arr[i], tmp);
			result = max(result, tmp);
		}
		return result;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int n;
		while (cin >> n) {
			vector<int> seq(n);
			for (int& num : seq)
				cin >> num;
			cout << lis_len(seq) << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
