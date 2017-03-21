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

	struct Piles1 {
	public:
		unsigned get(unsigned id) const {
			return (data >> id * 3) & 0x7;
		}
		void set(unsigned id, unsigned value) {
			id *= 3, data = ((data & ~(0x7 << id)) | value << id);
		}
		unsigned data = 0;
	};

	union Piles2 {
	public:
		unsigned data = 0;
		unsigned operator [] (unsigned j) const {
			return j<5?j<2?j<1?s.a:s.b:j<4?j<3?s.c:s.d:s.e:j<7?j<6?s.f:s.g:j<9?j<8?s.h:s.i:s.rest;
		}
	private:
		struct {
			unsigned a:3,b:3,c:3,d:3,e:3,f:3,g:3,h:3,i:3,rest:5;
		} s;
	};

	struct Piles3 {
	public:
		struct Trine {
		public:
			Trine(Piles3& parent, unsigned id) :
				par(parent), off(id * 3) {}
			operator unsigned () const { return (par.data >> off) & 0x7; }
			Trine& operator = (unsigned value) {
				par.data = ((par.data & ~(0x7 << off)) | value << off);
				return *this;
			}
		protected:
			Piles3& par;
			unsigned off;
		};
		struct Iterator : public Trine {
			Iterator(Piles3& parent, unsigned id) : Trine(parent, id) {}
			Trine operator * () const { return (Trine)*this; }
			virtual Trine& operator ++ () { off += 3; return *this; }
			bool operator != (const Iterator& rhs) { return off != rhs.off; }
		};
		unsigned operator [] (unsigned id) const { return ((data >> id * 3) & 0x7); }
		Trine operator [] (unsigned id) { return Trine(*this, id); }
		Iterator begin() { return Iterator(*this, 0); }
		Iterator end() { return Iterator(*this, 9); }
		unsigned data = 0;
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		Piles1 kek1;
		kek1.set(0, 2);
		cout << kek1.data << '\n';

		cout << "\n";

		Piles2 kek2;
		kek2.data = 2;
		cout << kek2[0] << '\n';

		cout << "\n";

		Piles3 kek3;
		kek3.data = 2;
		// 0b10
		cout << kek3[0] << '\n';
		cout << kek3.data << '\n';
		kek3[1] = 4;
		// 0b100010
		cout << kek3.data << '\n';
		kek3[0] = 0;
		cout << kek3.data << '\n';
		kek3[4] = 9;

		cout << "\n\n";

		for (auto kek : kek3)
			cout << kek << ' ';

		cout << "\n";

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
