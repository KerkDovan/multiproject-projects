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
#include <functional>
#include <iomanip>
#include <iterator>
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

	template<class First, class... Rest>
	class TableStorage {
	public:
		using Myt = TableStorage<First, Rest...>;
		using Myelt = std::tuple<First, Rest...>;
		template<size_t id>
		using getNth = std::tuple_element_t<id, Myelt>;

		static const size_t Myelsize = 1 + sizeof...(Rest);

		TableStorage() {}
		TableStorage(const TableStorage& rhs) { *this = rhs; }
		TableStorage(TableStorage&& rhs) { *this = rhs; }
		~TableStorage() {}

		TableStorage& operator = (const TableStorage& rhs) {
			this->_data = rhs._data;
			return *this;
		}
		TableStorage& operator = (TableStorage&& rhs) {
			this->_data = std::move(rhs._data);
			return *this;
		}

		bool operator == (const TableStorage& rhs) const {
			return this->_data == rhs._data;
		}
		bool operator != (const TableStorage& rhs) const {
			return this->_data != rhs._data;
		}

		template<class... Types>
		void emplace(const Types&... data) {
			return insert(data...);
		}

		void insert(const First& first, const Rest&... rest) {
			return this->insert(std::make_tuple(first, rest...));
		}

		void insert(const Myelt& element) {
			while (_data.find(_unique_id) != _data.end())
				++_unique_id;
			sort_on_insert<0>(_data.emplace(_unique_id, element).first);
		}

		template<size_t id>
		Myelt find(const getNth<id>& key) const {

		}

		void clear() {
			_unique_id = 0;
			_data.clear();
			_sorted = Sortedtype();
			_auxiliary = Auxsort();
		}

		struct iterator :
			public std::iterator<std::random_access_iterator_tag, Myelt, size_t>
		{
		public:
			using owner_type = Myt;

			iterator() {}
			iterator(const iterator& iter) {
				_owner = iter._owner;
				_id = iter._id;
			}
			~iterator() {}

#define TableStorage_iterator_make_operator(op) \
			auto operator op (const iterator& rhs) const \
				-> decltype(_id op _id) \
			{ \
				_compat(rhs); \
				return _id op rhs._id; \
			}
			TableStorage_iterator_make_operator(== );
			TableStorage_iterator_make_operator(!= );
			TableStorage_iterator_make_operator(< );
			TableStorage_iterator_make_operator(> );
			TableStorage_iterator_make_operator(<= );
			TableStorage_iterator_make_operator(>= );
			TableStorage_iterator_make_operator(- );
#undef TableStorage_iterator_make_operator

			iterator& operator += (size_t offset) {
				_id += offset;
				_debug_range();
				return *this;
			}
			iterator& operator -= (size_t offset) {
				_id -= offset;
				_debug_range();
				return *this;
			}
			iterator operator + (size_t offset) const {
				return iterator(result) += offset;
			}
			iterator operator - (size_t offset) const {
				return iterator(result) -= offset;
			}
			friend iterator operator + (size_t offset, const iterator& iter) {
				return iter + offset;
			}
			iterator& operator ++ () {
				return *this += (size_t)1;
			}
			iterator& operator -- () {
				return *this -= (size_t)1;
			}
			iterator operator ++ (int) const {
				return *this + (size_t)1;
			}
			iterator operator -- (int) const {
				return *this - (size_t)1;
			}

		private:
			Myt* _owner = nullptr;
			size_t _id = 0;
#if _ITERATOR_DEBUG_LEVEL
			void _compat(const iterator& rhs) const {
				assert(this->_owner == rhs._owner);
			}
			void _debug_range() const {
				assert(_id <= _owner->_data.size());
			}
#else _ITERATOR_DEBUG_LEVEL
			void _compat(const iterator& rhs) const {
			}
			void _debug_rage() const {
			}
#endif
		};

	private:

		template<class F, class S>
		struct Mymap {
			typedef Mymap<F, S> Myt;
			typedef std::vector<std::pair<F, S>> Myelt;
			typedef typename Myelt::iterator iterator;
			std::vector<std::pair<F, S>> _data;
			void sort() { std::sort(_data.begin(), _data.end(),
				[](const pair<F, S>& l, const pair<F, S>& r) {
					return l.first < r.first;
				});
			}
			void emplace(const F& f, const S& s) {
				_data.emplace_back(f, s);
				sort();
			}
			void erase(size_t id) {
				for (size_t i = id; i < _data.size() - 1; ++i)
					swap(_data[i], _data[i + 1]);
				_data.pop_back();
			}
			void clear() { _data.clear(); }
			S find(const F& key) const { return std::find(_data.begin(), _data.end()).second; }
			S& find(const F& key) { return std::find(_data.begin(), _data.end()).second; }
			S operator [] (size_t id) const { return _data[id].second; }
			S& operator [] (size_t id) { return _data[id].second; }
		};

		using Datatype = Mymap<size_t, std::tuple<First, Rest...>>;
		using Datatypeiter = typename Datatype::iterator;
		using Sortedtype = std::tuple<
			Mymap<First, Datatypeiter>,
			Mymap<Rest, Datatypeiter>...>;
		template<size_t id>
		using Sortedtypeiter = typename std::tuple_element_t<id, Sortedtype>::iterator;
		using Auxsort = std::tuple<
			Mymap<size_t, typename Mymap<First, Datatypeiter>::iterator>,
			Mymap<size_t, typename Mymap<Rest, Datatypeiter>::iterator>...>;

		size_t _unique_id = 0;
		Datatype _data;
		Sortedtype _sorted;
		Auxsort _auxiliary;

		template<size_t id>
		void sort_on_insert(const Datatypeiter& iter) {
			Sortedtypeiter i = std::get<id>(_sorted).emplace(std::get<id>(*iter), iter).first;
			std::get<id>(_auxiliary).emplace(id, i);
			sort_on_insert<id + 1>(iter);
		}

		template<>
		void sort_on_insert<Myelsize>(const Datatypeiter&) {}

	};



	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		TableStorage<int, string, char, double> kek;

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
