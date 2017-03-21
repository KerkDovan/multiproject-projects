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
	using namespace MyMath;

	typedef long long ll;
	typedef unsigned long long ull;

	template<class _MTy>
	struct MatrixStatementOutput {
	public:
		typedef MyMath::Matrix::Matrix<_MTy> MatrixTy;

		explicit MatrixStatementOutput(size_t height) : height(height) {}
		~MatrixStatementOutput() {
			clear();
		}

		template<class _RhsTy>
		MatrixStatementOutput& operator << (const _RhsTy& rhs) {
			toOutput.emplace_back(rhs);
			return *this;
		}

		MatrixStatementOutput& operator << (const char* rhs) {
			toOutput.emplace_back(string(rhs));
			return *this;
		}

		friend ostream& operator << (ostream& os, const MatrixStatementOutput& out) {
			formatWidth fw(0);
			for (size_t row = 0; row < out.height; ++row) {
				for (auto& el : out.toOutput) {
					string* str;
					MatrixTy* matrix;
					switch (el.element.index()) {
					case elFormatWidth:
						fw = *get<formatWidth>(el.element);
						break;
					case elSeparator:
						str = get<string>(el.element);
						os << ' ' << (*str)[row % str->size()] << ' ';
						break;
					case elMatrix:
						matrix = get<MatrixTy>(el.element);
						if (row >= matrix->height)
							break;
						for (auto& mEl : matrix->row(row))
							os << fw << mEl << ' ';
						break;
					}
				}
				os << '\n';
			}
			return os;
		}

		void clear() {
			for (auto& obj : toOutput) {
				if (obj.toDeleteAfter)
					obj.element.deleteobj();
			}
			toOutput.clear();
		}

	protected:
		enum ElementType {
			elMatrix,
			elSeparator,
			elFormatWidth,
		};
		struct Element {
/*
#ifdef MAKE_CONSTRUCTORS
#error Rename the macro below to compile
#endif
#define MAKE_CONSTRUCTORS(CLASS)\
			explicit Element(const CLASS& obj) : toDeleteAfter(true) {\
				element.createobj<CLASS>(obj);\
			}\
			explicit Element(const CLASS* obj) : toDeleteAfter(false) {\
				element = obj;\
			}
			MAKE_CONSTRUCTORS(MatrixTy)
			MAKE_CONSTRUCTORS(string)
			MAKE_CONSTRUCTORS(formatWidth)
#undef MAKE_CONSTRUCTORS
*/
			template<class Type>
			explicit Element(const Type& obj) : toDeleteAfter(true) {
				element.createobj<Type>(obj);
			}
			template<class Type>
			explicit Element(const Type* obj) : toDeleteAfter(false) {
				element = obj;
			}
			bool toDeleteAfter;
			VariantPtr<MatrixTy, string, formatWidth> element;
		};
		size_t height;
		vector<Element> toOutput;
	};

	typedef MatrixStatementOutput<double> RealMatrixStatementOutput;

	template<class _Ty>
	struct VectoredMatrix {
	public:
		typedef _Ty _Ty;
		typedef MyMath::Matrix::Matrix<_Ty> MatrixTy;

		VectoredMatrix(const MatrixTy& matrix) : _byLink(false) {
			assert(matrix.width == 1 || matrix.height == 1);
			_vertical = (matrix.width == 1);
			_matrix = new MatrixTy(matrix);
		}
		VectoredMatrix(MatrixTy* matrix) : _byLink(true) {
			assert(matrix->width == 1 || matrix->height == 1);
			_vertical = (matrix->width == 1);
			_matrix = matrix;
		}
		~VectoredMatrix() {
			if (!_byLink)
				delete _matrix;
		}

		_Ty& operator [] (size_t id) {
			return _vertical ? _matrix->col(0)[id] : _matrix->row(0)[id];
		}
		_Ty operator [] (size_t id) const {
			return _vertical ? _matrix->col(0)[id] : _matrix->row(0)[id];
		}
		
#ifdef LOAD_ITER
#error Rename the macro below to compile
#endif
#define LOAD_ITER(iter)\
		auto iter() {\
			return _vertical ? _matrix->col(0).iter() : _matrix->row(0).iter();\
		}
		LOAD_ITER(begin)
		LOAD_ITER(end)
		LOAD_ITER(cbegin)
		LOAD_ITER(cend)
		LOAD_ITER(rbegin)
		LOAD_ITER(rend)
		LOAD_ITER(crbegin)
		LOAD_ITER(crend)
#undef LOAD_ITER

	protected:
		bool _byLink;
		bool _vertical;
		MatrixTy* _matrix;
	};

	typedef VectoredMatrix<double> RealVectoredMatrix;

	template<class _Ty>
	auto createTransposed(const MyMath::Matrix::Matrix<_Ty>& matrix) {
		MyMath::Matrix::Matrix<_Ty> result(matrix.height, matrix.width);
		for (size_t i = 0; i < result.width; ++i)
			for (size_t j = 0; j < result.height; ++j)
				result[i][j] = matrix[j][i];
		return result;
	}

	const double EPS = 1e-15;

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t matrixSize;
		while (cin >> matrixSize) {

			RealMatrix matrix(matrixSize, matrixSize);
			for (size_t i = 0; i < matrixSize; ++i)
				for (size_t j = 0; j < matrixSize; ++j)
					cin >> matrix[j][i];

			RealMatrix coeffsM(1, matrixSize);
			RealVectoredMatrix coeffs(&coeffsM);
			for (size_t i = 0; i < matrixSize; ++i)
				cin >> coeffs[i];

			RealMatrix invertible(matrixSize, matrixSize);
			for (size_t i = 0; i < matrixSize; ++i)
				for (size_t j = 0; j < matrixSize; ++j)
					invertible[i][j] = (double)(i == j);

			RealMatrix initialMatrix = matrix, 
				initialCoeffs = coeffsM, 
				initialInvertible = invertible;
			cout << "================================================================================\n";
			RealMatrixStatementOutput output(matrixSize);
			output << formatWidth(4) << &matrix << "|" << &coeffsM << "|" << &invertible;
			cout << "Initial:\n" << output << '\n';
			cout << "--------------------------------------------------\n";
			cout << "Converting matrix to the triangular one:\n\n";
			double det = 1.0;
			for (size_t step = 0; step < matrixSize; ++step) {
				cout << "Step #" << step + 1 << ":\n";
				if (matrix[step][step] <= EPS) {
					for (size_t row = step + 1; row < matrixSize; ++row) {
						if (matrix[step][row] > EPS) {
							for (size_t id = 0; id < matrixSize; ++id) {
								swap(matrix[id][step], matrix[id][row]);
								swap(invertible[id][step], invertible[id][row]);
							}
							swap(coeffs[step], coeffs[row]);
							break;
						}
					}
				}
				double div = matrix[step][step];
				det *= div;
				coeffs[step] /= div;
				for (size_t i = matrixSize - 1; i != -1; --i) {
					invertible[i][step] /= div;
					matrix[i][step] /= div;
				}
				for (size_t row = step + 1; row < matrixSize; ++row) {
					double mult = matrix[step][row] / matrix[step][step];
					for (size_t id = step; id < matrixSize; ++id) {
						matrix[id][row] -= matrix[id][step] * mult;
						invertible[id][row] -= invertible[id][step] * mult;
					}
					coeffs[row] -= coeffs[step] * mult;
				}
				cout << output << '\n';
			}

			cout << "--------------------------------------------------\n";
			cout << "Determinant is " << det << "\n\n";

			cout << "--------------------------------------------------\n";
			cout << "Solution of SOLE:\n\n";
			RealMatrix xM(matrixSize, 1, nan(""));
			RealVectoredMatrix x(&xM);
			RealMatrixStatementOutput xOutput(1);
			xOutput << "(" << &xM << ")";
			for (size_t i = matrixSize - 1; i != -1; --i) {
				cout << "Step #" << matrixSize - i << '\n';
				double rhs = coeffs[i];
				for (size_t j = i + 1; j < matrixSize; ++j)
					rhs -= matrix[j][i] * x[j];
				rhs /= matrix[i][i];
				x[i] = rhs;
				cout << "x =" << xOutput << "\n";
			}
			cout << "Residual vector:\n";
			RealMatrixStatementOutput residualVectorOutput(matrixSize);
			RealMatrix xTM = createTransposed(xM);
			RealMatrix residualVector = initialMatrix * xTM - initialCoeffs;
			residualVectorOutput << formatWidth(4)
				<< &initialMatrix << " *" << &xTM << " -" << &initialCoeffs
				<< " =" << &residualVector;
			cout << residualVectorOutput << "\n";

			cout << "--------------------------------------------------\n";
			cout << "Converting matrix to the diagonal one:\n\n";
			output.clear();
			output << formatWidth(4) << &matrix << "|" << &invertible;
			for (size_t step = matrixSize - 1; step != 0; --step) {
				cout << "Step #" << matrixSize - step << ":\n";
				for (size_t row = step - 1; row != -1; --row) {
					double mult = matrix[step][row] / matrix[step][step];
					matrix[step][row] -= matrix[step][step] * mult;
					invertible[step][row] -= invertible[step][step] * mult;
				}
				cout << output << '\n';
			}
			RealMatrixStatementOutput residualMatrixOutput(matrixSize);
			RealMatrix residualMatrix = initialMatrix * invertible;
			residualMatrixOutput << formatWidth(4)
				<< &initialMatrix << " *" << &invertible
				<< " =" << &residualMatrix;
			cout << "Checking that we've got the invertible matrix:\n"
				<< residualMatrixOutput << "\n";
			residualMatrixOutput.clear();
			residualMatrix -= initialInvertible;
			residualMatrixOutput << formatWidth(4)
				<< &initialMatrix << " *" << &invertible << " -" << &initialInvertible
				<< " =" << &residualMatrix;
			cout << "Residual matrix:\n" << residualMatrixOutput << "\n\n";
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
