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

#include "libs\MyMath.h"

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
	using namespace MyMath;

	typedef long long ll;
	typedef unsigned long long ull;

	const double EPS = 1e-15;

	double norm(const RealMatrix& matrix) {
		double result = 0.0;
		for (auto iter = matrix.colCBegin(); iter != matrix.colCEnd(); ++iter)
			for (auto el : iter)
				result += el * el;
		return sqrt(result);
	}

	void cutSmallToZeros(RealMatrix& matrix, double eps = EPS) {
		for (auto iter = matrix.colBegin(); iter != matrix.colEnd(); ++iter)
			for (double& el : iter)
				if (fabs(el) < eps)
					el = 0.0;
	}

	enum TaskType { SLAE = 0, Determinant = 1, Invertible = 2, };
	enum Method { GaussJordan = 0, GaussSeidel = 1, };

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t method, taskType, matrixSize;
		while (cin >> method >> taskType >> matrixSize) {

			RealMatrix matrix(matrixSize, matrixSize);
			for (size_t i = 0; i < matrixSize; ++i)
				for (size_t j = 0; j < matrixSize; ++j)
					cin >> matrix[j][i];

			RealMatrix coeffsM(1, matrixSize);
			RealVectoredMatrix coeffs(&coeffsM);
			if (taskType == SLAE) {
				for (size_t i = 0; i < matrixSize; ++i)
					cin >> coeffs[i];
			}

			RealMatrix invertible(matrixSize, matrixSize);
			if (taskType == Invertible) {
				for (size_t i = 0; i < matrixSize; ++i)
					for (size_t j = 0; j < matrixSize; ++j)
						invertible[i][j] = (double)(i == j);
			}

			RealMatrix initialMatrix = matrix, 
				initialCoeffs = coeffsM, 
				initialInvertible = invertible;
			RealMatrixStatementOutput output(matrixSize);
			RealMatrix xM;
			RealVectoredMatrix x;
			RealMatrixStatementOutput xOutput;
			RealMatrixStatementOutput residualVectorOutput;
			RealMatrix xTM;
			RealMatrix residualVector;

			cout << "================================================================================\n";

			if (method == GaussJordan) {
				output << formatWidth(4) << &matrix;
				if (taskType == SLAE)
					output << "|" << &coeffsM;
				if (taskType == Invertible)
					output << "|" << &invertible;
				cout << "Initial:\n" << output << '\n';
				cout << "....................  Gauss-Jordan method  ....................\n\n";
				switch (taskType) {
				case SLAE:
					cout << "....................  Solution of SLAE  ....................\n\n";
					break;
				case Determinant:
					cout << "....................  Finding determinant  ....................\n\n";
					break;
				case Invertible:
					cout << "....................  Matrix inversion  ....................\n\n";
					break;
				}
				cout << "--------------------------------------------------\n";
				cout << "Converting matrix to the triangular one:\n\n";
				double det = 1.0;
				for (size_t step = 0; step < matrixSize; ++step) {
					cout << "Step #" << step + 1 << ":\n";
					if (matrix[step][step] <= EPS) {
						for (size_t row = step + 1; row < matrixSize; ++row) {
							if (matrix[step][row] > EPS) {
								det *= -1.0;
								for (size_t id = 0; id < matrixSize; ++id)
									swap(matrix[id][step], matrix[id][row]);
								if (taskType == Invertible)
									for (size_t id = 0; id < matrixSize; ++id)
										swap(invertible[id][step], invertible[id][row]);
								swap(coeffs[step], coeffs[row]);
								break;
							}
						}
					}
					double div = matrix[step][step];
					det *= div;
					coeffs[step] /= div;
					for (size_t i = 0; i < matrixSize; ++i)
						matrix[i][step] /= div;
					if (taskType == Invertible)
						for (size_t i = 0; i < matrixSize; ++i)
							invertible[i][step] /= div;
					for (size_t row = step + 1; row < matrixSize; ++row) {
						double mult = matrix[step][row] / matrix[step][step];
						for (size_t id = 0; id < matrixSize; ++id) {
							matrix[id][row] -= matrix[id][step] * mult;
							if (taskType == Invertible)
								invertible[id][row] -= invertible[id][step] * mult;
						}
						coeffs[row] -= coeffs[step] * mult;
					}
					cout << output << '\n';
				}

				if (taskType == Determinant) {
					cout << "--------------------------------------------------\n";
					cout << "Determinant is " << det << "\n\n";
				}

				if (taskType == SLAE) {
					cout << "--------------------------------------------------\n";
					cout << "Solution of SLAE:\n\n";
					xM = RealMatrix(matrixSize, 1, nan(""));
					x = RealVectoredMatrix(&xM);
					xOutput = RealMatrixStatementOutput(1);
					xOutput << "(" << &xM << ")";
					for (size_t i = matrixSize - 1; i != -1; --i) {
						cout << "Step #" << matrixSize - i << '\n';
						double rhs = coeffs[i];
						for (size_t j = i + 1; j < matrixSize; ++j)
							rhs -= matrix[j][i] * x[j];
						rhs /= matrix[i][i];
						x[i] = rhs;
						cutSmallToZeros(xM);
						cout << "x =" << xOutput << "\n";
					}
					cout << "Residual vector:\n";
					residualVectorOutput = RealMatrixStatementOutput(matrixSize);
					xTM = createTransposed(xM);
					residualVector = initialMatrix * xTM - initialCoeffs;
					cutSmallToZeros(residualVector);
					residualVectorOutput << formatWidth(4)
						<< &initialMatrix << " *" << &xTM << " -" << &initialCoeffs
						<< " =" << &residualVector;
					cout << residualVectorOutput << "\n";
				}

				if (taskType == Invertible) {
					cout << "--------------------------------------------------\n";
					cout << "Converting matrix to the diagonal one:\n\n";
					output.clear();
					output << formatWidth(4) << &matrix << "|" << &invertible;
					for (size_t step = matrixSize - 1; step != 0; --step) {
						cout << "Step #" << matrixSize - step << ":\n";
						for (size_t row = step - 1; row != -1; --row) {
							double mult = matrix[step][row] / matrix[step][step];
							for (size_t id = 0; id < matrixSize; ++id) {
								matrix[id][row] -= matrix[id][step] * mult;
								invertible[id][row] -= invertible[id][step] * mult;
							}
						}
						cout << output << '\n';
					}
					RealMatrixStatementOutput residualMatrixOutput(matrixSize);
					RealMatrix residualMatrix = initialMatrix * invertible;
					cutSmallToZeros(residualMatrix);
					residualMatrixOutput << formatWidth(4)
						<< &initialMatrix << " *" << &invertible
						<< " =" << &residualMatrix;
					cout << "Checking that we have the invertible matrix:\n"
						<< residualMatrixOutput << "\n";
					residualMatrixOutput.clear();
					residualMatrix -= initialInvertible;
					cutSmallToZeros(residualMatrix);
					residualMatrixOutput << formatWidth(4)
						<< &initialMatrix << " *" << &invertible << " -" << &initialInvertible
						<< " =" << &residualMatrix;
					cout << "Residual matrix:\n" << residualMatrixOutput << "\n\n";
				}
			} // method == GaussJordan

			if (method == GaussSeidel) {
				output << formatWidth(4) << &matrix << "|" << &coeffsM;
				cout << "Initial:\n" << output << '\n';

				cout << "....................  Gauss-Seidel method  ....................\n\n";
				cout << "....................  Solution of SLAE  ....................\n\n";
				cout << "--------------------------------------------------\n";
				cout << "Solution of SLAE:\n\n";

				output.clear();

				matrix = initialMatrix;
				coeffsM = initialCoeffs;

				bool consistent = true;
				for (size_t i = 0; i < matrixSize; ++i) {
					if (fabs(matrix[i][i]) > EPS)
						continue;
					bool swaped = false;
					for (size_t j = 0; j < matrixSize; ++j) {
						if (fabs(matrix[i][j] * matrix[j][i]) < EPS)
							continue;
						for (size_t k = 0; k < matrixSize; ++k)
							swap(matrix[k][i], matrix[k][j]);
						swap(coeffs[i], coeffs[j]);
						swaped = true;
					}
					if (!swaped) {
						consistent = false;
						break;
					}
				}

				if (!consistent) {
					cout << "Matrix is not consistent, cannot solve SLAE\n\n";
					continue;
				}

				xM.resize(1, matrixSize, 0.0);
				x = &xM;

				vector<RealMatrix> cM(matrixSize, RealMatrix(1, matrixSize, 0.0));
				vector<RealVectoredMatrix> c(matrixSize);

				RealMatrix dM(1, matrixSize);
				RealVectoredMatrix d = &dM;

				output << &xM << "=" << "(";

				RealMatrix aiiM(1, matrixSize);
				RealVectoredMatrix aii = &aiiM;
				for (size_t i = 0; i < matrixSize; ++i) {
					aii[i] = matrix[i][i];
					c[i] = &cM[i];
					d[i] = coeffs[i];
					output << &cM[i] << "+";
				}

				output << &dM << ")" << "/" << &aiiM;

				RealMatrix prevXM = xM;
				RealVectoredMatrix p = &prevXM;

				size_t step = 1;
				for (; ; ++step) {
					debug << "Step #" << step << '\n';

					for (size_t i = 0; i < matrixSize; ++i) {
						double tmp = d[i];
						for (size_t j = 0; j < i; ++j)
							tmp -= matrix[j][i] * x[j];

						for (size_t j = i + 1; j < matrixSize; ++j)
							tmp -= matrix[j][i] * p[j];

						x[i] = tmp / aii[i];
					}

					debug << output << '\n';
					if (norm(xM - prevXM) <= EPS || step > 100)
						break;

					swap(prevXM, xM);
				}

				cout << "Total " << step << " steps\n\n";

				xTM = createTransposed(xM);
				xOutput.clear();
				xOutput << "(" << &xTM << ")";
				cout << "x = " << xOutput << '\n';

				residualVector = initialMatrix * xM - initialCoeffs;
				cutSmallToZeros(residualVector);
				residualVectorOutput.clear();
				residualVectorOutput << formatWidth(4)
					<< &initialMatrix << " *" << &xM << " -" << &initialCoeffs
					<< " =" << &residualVector;
				cout << "Residual vector:\n" << residualVectorOutput << "\n\n";
			} // method == GaussSeidel
			cout << "\n\n";
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
