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

	class SummatorNeuroweb {
	public:
		static const int INPUTS = 10;
		static const int OUTPUTS = 2 * INPUTS - 1;
		SummatorNeuroweb() {}
		~SummatorNeuroweb() {}
		void operator () (int a, int b, int res) {
			check_input(a, b, res);

			for (size_t i = 0; i < OUTPUTS; ++i) {
				if ((res % INPUTS != i) ^ (current[i](a, b)))
					current[i].good(a, b);
				else
					current[i].bad(a, b);
			}
			if ((res / INPUTS != 1) ^ (next(a, b)))
				next.good(a, b);
			else
				next.bad(a, b);
		}
		int operator () (int a, int b) {
			check_input(a, b, 0);

			int result = 0;

			for (size_t i = 0; i < OUTPUTS; ++i)
				if (current[i](a, b))
					result += i;

			if (next(a, b))
				result += INPUTS;

			return result;
		}
	private:
		void check_input(int a, int b, int res) const {
			if (a >= INPUTS || a < 0 ||
				b >= INPUTS || b < 0 ||
				res >= OUTPUTS || res < 0)
				throw "Wrong arguments passed to neuroweb";
		}
		struct Neuron {
			int w[INPUTS][INPUTS]; // weights
			bool la;
			Neuron() {
				memset(w, 0, sizeof(w));
			}
			bool operator() (int a, int b) {
				return la = w[a][b] > 0;
			}
			void good(int a, int b) {
				if (la)
					w[a][b] += 1;
				else
					w[a][b] -= 1;
				w[a][b] %= 10;
			}
			void bad(int a, int b) {
				if (la)
					w[a][b] -= 1;
				else
					w[a][b] += 1;
				w[a][b] %= 10;
			}
		};
		Neuron current[OUTPUTS];
		Neuron next;
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		SummatorNeuroweb nw;

		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < 10; ++j)
				nw(i, j, i + j);

		size_t incorrect = 0;

		for (size_t i = 0; i < 1000; ++i) {
			int a = rand() % 10;
			int b = rand() % 10;
			int r = nw(a, b);
			incorrect += (bool)(r != a + b);
			cout << a << " + " << b << " => " << r << '\n';
		}
		cout << "Incorrect " << incorrect << " of 1000\n";

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
