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

#include "MyMath\experimental.hpp"
#include "PolStr.h"

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
	using namespace MyMath;
	using namespace MyMath::experimental;

	typedef long long ll;
	typedef unsigned long long ull;

	const double EPS = 1e-9;

	enum TaskType {
		ttPolynomial = 0, ttFirstDerivative = 1, ttSecondDerivative = 2,
	};

	enum GridType {
		gtRegular = 'r', gtIrregular = 'i',
	};

	enum ExpressionExistence {
		eeYes = 'y', eeNo = 'n',
	};

	struct Node {
		double x, y;
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t task, gridSize;
		while (cin >> task >> gridSize) {
			cout << "===============================================\n\n";
			char gridType, exprExists;
			cin >> gridType;
			vector<Node> initGrid(gridSize + 1);
			if ((GridType)gridType == gtRegular) {
				double a, b, step;
				cin >> a >> b;
				if (b < a)
					swap(a, b);
				step = (b - a) / (double)gridSize;
				for (size_t i = 0; i < gridSize; ++i)
					initGrid[i].x = a + step * i;
				initGrid[gridSize].x = b;
			}
			else {
				for (size_t i = 0; i <= gridSize; ++i)
					cin >> initGrid[i].x;
			}
			for (size_t i = 0; i <= gridSize; ++i)
				cin >> initGrid[i].y;
			size_t resultSize;
			cin >> resultSize;
			vector<Node> resultGrid(resultSize + 1);
			for (size_t i = 0; i <= resultSize; ++i)
				cin >> resultGrid[i].x;
			cin >> exprExists >> ws;
			string expr;
			if ((ExpressionExistence)exprExists == eeYes)
				getline(cin, expr);
			vector<vector<double>> xij(gridSize + 1, vector<double>(gridSize + 1)); // x[i] - x[j]
			vector<string> xi(gridSize + 1); // x - x[i]
			for (size_t i = 0; i <= gridSize; ++i) {
				for (size_t j = 0; j <= gridSize; ++j)
					xij[i][j] = initGrid[i].x - initGrid[j].x;
				if (fabs(initGrid[i].x) < EPS) {
					xi[i] = "x";
					continue;
				}
				xi[i] = "(x";
				xi[i] += initGrid[i].x < 0 ? " + " : " - ";
				xi[i] += to_string(fabs(initGrid[i].x)) + ")";
			}
			vector<double> denominators(gridSize + 1);
			for (size_t i = 0; i <= gridSize; ++i) {
				denominators[i] = initGrid[i].y;
				for (size_t j = 0; j <= gridSize; ++j) {
					if (i == j)
						continue;
					denominators[i] /= xij[i][j];
				}
			}
			vector<string> li(gridSize + 1);
			for (size_t i = 0; i <= gridSize; ++i) {
				for (size_t j = 0; j <= gridSize; ++j) {
					if (i == j)
						continue;
					li[i] += xi[j] + " * ";
				}
				li[i] += "(" + to_string(denominators[i]) + ")";
			}
			string lagrange;
			for (size_t i = 0; i <= gridSize; ++i) {
				if (i != 0)
					lagrange += " + ";
				lagrange += li[i];
			}
			cout << "Lagrange polynomial:\nL(x) = " << lagrange << "\n\n";
			char* pol_lagrange = CreatePolStr(lagrange.c_str(), 0);
			if (pol_lagrange == nullptr) {
				cout << "Cannot get the poland string from Lagrange polynomial\n\n";
				continue;
			}
			cout << "Poland string of Lagrange polynomial:\n" << pol_lagrange << "\n\n";
			for (Node& node : resultGrid)
				cout << "L" << (task ? task == 1 ? "'" : "''" : "") << "(" << node.x << ") = "
					<< (node.y = EvalPolStr(pol_lagrange, node.x, task)) << '\n';
			cout << "\n";
			delete[] pol_lagrange;
			if (exprExists) {
				char* pol_expr = CreatePolStr(expr.c_str(), 0);
				cout << "Original function:\nf(x) = " << expr << "\n\n";
				if (pol_expr == nullptr) {
					cout << "Cannot get the poland string from original expression\n\n";
					continue;
				}
				cout << "Poland string of original function:\n" << pol_expr << "\n\n";
				vector<Node> originals = resultGrid;
				for (Node& node : originals)
					cout << "f" << (task ? task == 1 ? "'" : "''" : "") << "(" << node.x << ") = "
						<< (node.y = EvalPolStr(pol_expr, node.x, task)) << '\n';
				cout << "\n";
				delete[] pol_expr;
				double deviation = 0.0;
				for (size_t i = 0; i <= resultSize; ++i) {
					double dy = resultGrid[i].y - originals[i].y;
					deviation += dy * dy;
				}
				deviation /= (double)(resultSize + 1);
				deviation = sqrt(deviation);
				cout << "Standard deviation: " << scientific << deviation << fixed << "\n\n";
			}
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
