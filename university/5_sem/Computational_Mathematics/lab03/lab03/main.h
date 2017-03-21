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

#include "PolStr.h"

#define stringify(...) stringify2(__VA_ARGS__)
#define stringify2(...) #__VA_ARGS__

#define let const auto

// Changeable code stops here.

#ifdef _LOCAL_MULTIPROJECT_

#include "multiproject.h"

#include "MyMath.h"
#include "MyMath/experimental.hpp"

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
	using namespace MyMath;

	typedef long long ll;
	typedef unsigned long long ull;

	enum TaskType { eigenvalues = 1, eigenvectors = 2 };

	const int EPS_PREC = 2;
	const double EPS = 1e-9;
	const double NINF = -1e9;
	const double PINF = 1e9;

	RealMatrix cutZeros(const RealMatrix& src) {
		RealMatrix result = src;
		//for (auto iter = result.colBegin(); iter != result.colEnd(); ++iter)
		//	for (auto& el : iter)
		//		el = el < EPS ? 0.0 : el;
		return result;
	}

	string toStr(int num) {
		static const int prec = 0;
		string result = to_string(num);
		if (prec)
			result.reserve(result.size() + 1 + prec);
		for (int i = 0; i < prec; ++i) {
			if (i == 0)
				result += '.';
			result += '0';
		}
		return result;
	}
	
	string toStr(double num) {
		static const int prec = EPS_PREC;
		int t = 1;
		for (int i = 0; i < prec; ++i)
			t *= 10;
		num *= t;
		num = floor(num + 0.5) / (t + 0.0);
		string result = to_string(num);
		t = 0;
		for (int i = 0; i < (int)result.size(); ++i) {
			if (t || result[i] == '.')
				++t;
		}
		if (t != 0)
			--t;
		if (t > prec)
			result.resize(result.size() - t + prec);
		else
			for (int i = t; i < prec; ++i)
				result += '0';
		if (result.back() == '.')
			result.pop_back();
		return result;
	}

	double getDeterminant(RealMatrix matrix) {
		for (size_t i = 0; i < matrix.height - 1; ++i) {
			double t = matrix[i][i];
			for (double& el : matrix.row(i))
				el /= t;
			for (size_t j = i + 1; j < matrix.height; ++j) {
				t = matrix[i][j];
				for (size_t k = i + 1; k < matrix.width; ++k)
					matrix[k][j] -= t * matrix[k][i];
			}
		}
		double det = 1.0;
		for (size_t i = 0; i < matrix.height; ++i)
			det *= matrix[i][i];
		return det;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		Polynomial<double> pol_testing({ 3, 5, 1, -1 }); // ({ 24, -44, 22, 3, -5, 1 });
		auto rootsTesting = getRoots(pol_testing, NINF, PINF, EPS, fabs);
		debug << pol_testing.toString(toStr) << "\n";
		debug << "{ ";
		for (auto root : rootsTesting)
			debug << root << ", ";
		debug << "}\n";
		debug << pol_testing.getDerivative(1).toString(toStr) << "\n";
		debug << pol_testing.getDerivative(1)(-1.0) << "\n\n";

		cout << setprecision(EPS_PREC) << fixed;

		formatWidth fw(5);

		int taskType;
		while (cin >> taskType) {
			debug << "===============================================\n\n";
			cout << "===============================================\n\n";
			cout << "Finding " << (taskType == eigenvalues ?
				"eigenvalues\n" : "eigenvectors\n");
			cout << "\n-----------------------------------------------\n\n";
			size_t matrixSize;
			cin >> matrixSize;
			RealMatrix initialMatrix(matrixSize, matrixSize);
			for (auto row = initialMatrix.rowBegin(); row != initialMatrix.rowEnd(); ++row)
				for (auto& el : row)
					cin >> el;
			RealMatrix matrix = initialMatrix;
			RealMatrixStatementOutput output(matrixSize);
			output << fw << &matrix;
			cout << "Initial matrix:\n" << output;
			cout << "\n-----------------------------------------------\n\n";
			cout << "Getting Frobenius matrix:\n\n";
			RealMatrix m(matrixSize), m1(matrixSize), tmp, s(matrixSize);
			output.clear();
			output << fw << &m1 << " * " << &matrix << " * " << &m << " = " << &tmp << "|" << &s;
			for (size_t step = 1; step < matrixSize; ++step) {
				size_t rowId = matrixSize - step;
				cout << "Step #" << step << " (row #" << rowId << "):\n";
				for (size_t i = 0; i < matrixSize; ++i)
					m[i][rowId] = m1[i][rowId] = (double)(i == rowId);
				for (size_t i = 0; i < matrixSize; ++i) {
					m[i][rowId - 1] = (i == rowId - 1 ? 1 / matrix[rowId - 1][rowId] :
						-matrix[i][rowId] / matrix[rowId - 1][rowId]);
					m1[i][rowId - 1] = matrix[i][rowId];
				}
				debug << cutZeros(m * m1) << '\n';
				s *= m;
				tmp = m1 * matrix * m;
				cout << output << '\n';
				swap(matrix, tmp);
			}
			output.clear();
			output << fw << &matrix;
			cout << "Frobenius matrix:\n" << output;
			cout << "\n-----------------------------------------------\n\n";
			Polynomial<double> polynomial(matrixSize, matrixSize & 1 ? 1.0 : -1.0);
			polynomial[matrixSize] *= -1.0;
			for (size_t i = 0; i < matrixSize; ++i)
				polynomial[i] *= matrix.row(0)[matrixSize - i - 1];
			cout << "Polynomial:\n" << polynomial.toString(toStr) << "\n";
			cout << "\n-----------------------------------------------\n\n";
			cout << "Roots of the polynomial / eigenvalues:\n{ ";
			auto roots = getRoots(polynomial, NINF, PINF, EPS, fabs);
			map<double, size_t> eg_values;
			for (double root : roots)
				++eg_values[root];
			roots.clear();
			vector<size_t> multiplicities;
			for (auto eg_value : eg_values) {
				cout << toStr(eg_value.first) << " [" << eg_value.second << "], ";
				roots.emplace_back(eg_value.first);
				multiplicities.emplace_back(eg_value.second);
			}
			cout << "}\n";
			cout << "\n-----------------------------------------------\n\n";
			if (taskType == eigenvalues) {
				cout << "Testing eigenvalues:\n\n";
				for (size_t i = 0; i < roots.size(); ++i) {
					output.clear();
					output << fw;
					auto le = roots[i] * RealMatrix(matrixSize);
					auto mle = matrix - le;
					auto det = getDeterminant(mle);
					char ss[100];
					sprintf(ss, "%e", det);
					output << " D " << "|" << &matrix << " - " << le << " = "
						<< mle << "|" << " = " << RealMatrix(1, 1, det);
					cout << output << "\n" << ss << "\n";
					
				}
			}
			else {
				cout << "Eigenvectors are:\n";
				vector<RealMatrix> eg_vect(roots.size(), RealMatrix(1, matrixSize, 1.0));
				output.clear();
				output << fw;
				for (size_t i = 0; i < roots.size(); ++i) {
					auto vect = eg_vect[i][0];
					for (size_t j = matrixSize - 1; j != -1; --j)
						for (size_t k = j - 1; k != -1; --k)
							vect[k] *= roots[i];
					eg_vect[i] = s * eg_vect[i];
					if (i != 0)
						output << "|";
					output << &eg_vect[i];
				}
				cout << output << "\n";
				cout << "\n-----------------------------------------------\n\n";
				cout << "Testing eigenvectors:\n\n";
				for (size_t i = 0; i < roots.size(); ++i) {
					cout << "-------\n\n";
					output.clear();
					output << fw;
					const auto vect = eg_vect[i];
					const auto diff = (initialMatrix * vect - roots[i] * vect);
					output << &initialMatrix << " * " << &vect << " - " <<
						vect * roots[i] << " = " <<
						diff;
					cout << output;
					cout << "\nMultiplicity is " << multiplicities[i] << "\n\n";
					output.clear();
					output << diff;
					cout << "Residual matrix:\n";
					cout << scientific << output << fixed << "\n";
				}
			}
			cout << "\n";
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
