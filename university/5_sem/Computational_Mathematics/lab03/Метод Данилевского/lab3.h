#include <array>
#include <cassert>
#include <cmath>
#include <initializer_list>
#include <iostream>

using namespace std;

struct VectType {
	VectType() { data = { 0.0, 0.0, 0.0 }; }
	VectType(const array<double, 3>& vect) { data = vect; }
	VectType(double a, double b, double c) { data = { a, b, c }; }
	array<double, 3> data;
	double& operator [] (size_t id) {
		assert(id <= 2);
		return data[id];
	}
	double operator [] (size_t id) const {
		assert(id <= 2);
		return data[id];
	}
};

struct MatrType {
	MatrType() { data = { VectType(), VectType(), VectType() }; }
	MatrType(const array<VectType, 3>& matr) { data = matr; }
	MatrType(const VectType& a, const VectType& b, const VectType& c) {
		data = { a, b, c };
	}
	array<VectType, 3> data;
	VectType& operator [] (size_t id) {
		assert(id <= 2);
		return data[id];
	}
	VectType operator [] (size_t id) const {
		assert(id <= 2);
		return data[id];
	}
};

const MatrType MyMatr = array<VectType, 3> { 
	VectType {  1,  2, -1 },
	VectType {  3,  0,  2 },
	VectType {  4, -2,  5 },
};

const MatrType EM = array<VectType, 3> { 
	VectType {  1,  0,  0, },
	VectType {  0,  1,  0, },
	VectType {  0,  0,  1, },
};

const int N = 3;

double F(double x, const VectType& p) {
	return -1.0 * (x * x * x - p[0] * x * x - p[1] * x - p[2]);
}

double dF(double x, const VectType& p) {
	return -1.0 * (3.0 * x * x - 2 * p[0] * x - p[1]);
}

void MxM(const MatrType& A, const MatrType& B, MatrType& X) {
	X = MatrType();
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k)
				X[i][j] += A[i][k] * B[k][j];
}

void MxV(const MatrType& A, const VectType& V, VectType& X) {
	X = VectType();
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			X[i] += A[i][j] * V[j];
}

void Lab3(const MatrType& Matr, VectType& L, MatrType& X, MatrType& Ax, MatrType& Lx) {
	
}

int main() {
	return 0;
}
