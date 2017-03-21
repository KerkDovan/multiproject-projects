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
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string.h>
#include <typeinfo>
#include <tuple>
#include <utility>
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

	template<class Cont, class... Args> struct Found {
	private:
		struct no_find; static constexpr no_find detect(...) {}
		template<class C, class... A> static constexpr auto
			detect(const C& c, A&&... a) -> decltype(c.find(std::forward<A>(a)...)) {}
	public:
		static constexpr bool has_find = !std::is_same<no_find,
			decltype(detect(std::declval<Cont>(), std::declval<Args>()...))>::value;
		template<bool, class...> struct Find;
		template<class... V> struct Find<false, Cont, V...> {
			static constexpr bool find(const Cont& begin, const Cont& end, V&&... values) {
				return std::find(begin, end, std::forward<V>(values)...) != end;
			}
		};
		template<class... V> struct Find<false, V...> {
			static constexpr bool find(const Cont& container, V&&... values) {
				return std::find(container.begin(), container.end(),
					std::forward<V>(values)...) != container.end();
			}
		};
		template<class... A> struct Find<true, A...> {
			static constexpr bool find(const Cont& container, A&&... arguments) {
				return container.find(std::forward<A>(arguments)...) != container.end();
			}
		};
	};

	template<class Cont, class... Args>
	inline constexpr bool found(const Cont& container, Args&&... args) {
		return Found<Cont, Args...>::template Find<Found<Cont, Args...>::has_find,
			Args...>::find(container, std::forward<Args>(args)...);
	}

	struct Foo {
		int find(int a, int b) const { return (a & 1) ^ ((b >> 1) & 1); }
		int end() const { return 0; }
	};

	struct Bar {
		int value = 228;
		int find(const Bar& b, int val) const { return b.value + val; }
		int end() const { return 322; }
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		vector<int> a = { 4, 8, 15, 16, 23, 42 };
		set<int> b = { 4, 8, 15, 16, 23, 42 };
		Foo c;
		Bar d;
		for (int i = 0; i < 100; ++i) {
			cout << setw(3) << i << "  :::  ";
			cout << found(a, i) << " | ";
			cout << found(b, i) << " | ";
			cout << found(a.begin(), a.end(), i) << " | ";
			cout << found(c, i, a[i % a.size()]) << " | ";
			cout << found(d, d, i) << " | ";
			cout << "\n";
		}
		cout << "\n";
		cout << found(a, 4) << "\n";
		cout << found(b, 4) << "\n";
		cout << found(a.begin(), a.end(), 4) << "\n";
		cout << found(c, 3, 5) << "\n";
		cout << found(d, Bar(), 94) << "\n";

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
