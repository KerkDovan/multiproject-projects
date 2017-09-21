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

	struct Row {
		Row() { _data.assign(3, 0.0); }
		double operator [] (int i) const { return _data[i]; }
		double& operator [] (int i) { return _data[i]; }
		Row& operator *= (double rhs) {
			for (double& num : _data)
				num *= rhs;
			return *this;
		}
		Row& operator -= (const Row& rhs) {
			for (int i = 0; i < 3; ++i)
				_data[i] -= rhs[i];
			return *this;
		}
		Row operator * (double rhs) const { return Row(*this) *= rhs; }
		Row operator - (const Row& rhs) const { return Row(*this) -= rhs; }
		vector<double> _data;
	};

	struct Matrix {
		Matrix() { _data.assign(3, Row()); }
		Row operator [] (int i) const { return _data[i]; }
		Row& operator [] (int i) { return _data[i]; }
		vector<Row> _data;
	};

	Matrix reverse(const Matrix& matrix) {
		Matrix r, m = matrix;
		for (int i = 0; i < 3; ++i)
			r[i][i] = 1.0;

		Row tmp;
		double t;

		// step 1

		r[1] -= r[0] * (m[1][0] / m[0][0]);
		m[1] -= m[0] * (m[1][0] / m[0][0]);

		r[2] -= r[0] * (m[2][0] / m[0][0]);
		m[2] -= m[0] * (m[2][0] / m[0][0]);

		r[0] *= 1 / m[0][0];
		m[0] *= 1 / m[0][0];

		// step 2

		r[2] -= r[1] * (m[2][1] / m[1][1]);
		m[2] -= m[1] * (m[2][1] / m[1][1]);

		r[1] *= 1 / m[1][1];
		m[1] *= 1 / m[1][1];

		// step 3

		r[2] *= 1 / m[2][2];
		m[2] *= 1 / m[2][2];

		// step 4

		r[1] -= r[2] * m[1][2];
		m[1] -= m[2] * m[1][2];

		// step 5

		r[0] -= r[2] * m[0][2];
		m[0] -= m[2] * m[0][2];

		// step 6

		r[0] -= r[1] * m[0][1];
		m[0] -= m[1] * m[0][1];

		return r;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		Matrix m;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				cin >> m[i][j];

		m = reverse(m);

		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				assert(!isnan(m[i][j])); // Run-time error on test 2

		cout << fixed;
		cout << m[1][1] << ' ' << m[0][2] << ' ' << m[1][2] << ' ' << m[2][2] << '\n';

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
