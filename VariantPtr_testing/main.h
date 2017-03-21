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

#include "libs\Variant.hpp"

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

	

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		VariantPtr<int, string> var1, var2;
		cout << var1.index() << ' ' << var2.index() << '\n';

		int a = 13;
		int* b = &a;
		var1 = b;
		cout << var1.index() << ' ' << var2.index() << '\n';

		string* c = new string("kek");
		var2 = c;
		cout << var1.index() << ' ' << var2.index() << '\n';

		cout << *get<int>(var1) << ' ' << *get<string>(var2) << '\n';
		cout << var1.index() << ' ' << var2.index() << '\n';
		var2.deleteobj();
		cout << var1.index() << ' ' << var2.index() << '\n';

		VariantPtr<int, pair<double, char>> var3;
		var3.createobj<pair<double, char>>(123.6, 'A');
		cout << var3.index() << '\n';
		pair<double, char>* p = get<pair<double, char>>(var3);
		cout << p->first << ' ' << p->second << '\n';
		var3.deleteobj();

		VariantPtr<int, string> var4;
		int* d = var4.createobj<int>(13);
		string* e = var4.createobj<string>("kek");
		cout << *d << ' ' << *e << '\n';
		var4 = nullptr;
		*d = 234;
		var4 = d;
		cout << *get<int>(var4) << '\n';
		*e = "lalka";
		var4 = e;
		cout << *get<string>(var4) << '\n';
		delete d;
		delete e;

		VariantPtr<int, double, string> var5;
		// var5 = 'S'; // error: no operator matches these operands
		// var5.createobj<char>('S'); // assert: Appropriate type not found
		VariantPtr<char, string, double> var6;
		var5.createobj<double>(216.532);
		var6 = var5;
		cout << *get<double>(var5) << ' ' << *get<double>(var6) << '\n';

		cout << boolalpha;
		cout << "\nvar1 = " << *(int*)var1 << '\n';
		cout << "var1 holds int " << holds_alternative<int>(var1) << '\n';
		cout << "var1 holds string " << holds_alternative<string>(var1) << '\n';
		cout << "var1 holds char " << holds_alternative<char>(var1) << '\n';
		cout << "var1 holds double " << holds_alternative<double>(var1) << '\n';
		var2.createobj<string>("azaza");
		cout << "\nvar2 = " << *(string*)var2 << '\n';
		cout << "var2 holds int " << holds_alternative<int>(var2) << '\n';
		cout << "var2 holds string " << holds_alternative<string>(var2) << '\n';
		cout << "var2 holds char " << holds_alternative<char>(var2) << '\n';
		cout << "var2 holds double " << holds_alternative<double>(var2) << '\n';
		cout << '\n';
		var2.deleteobj();

		VariantPtr<int, double, string> var7;
		var7.createobj<double>(235.754);
		double* g = var7;
		cout << g << ' ' << *g << '\n';
		var7.deleteobj();

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif