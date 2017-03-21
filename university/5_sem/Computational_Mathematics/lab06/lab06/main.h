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
#include "PolStr.h"
#include "MyMath.h"

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

	enum TaskType {
		linear = 1, parabolic = 2, cubic = 3,
	};

	enum ExpressionExists {
		yes = 'y', no = 'n',
	};

	enum BoundaryType {
		self = 0, first_derivative = 1,
	};

	struct Point {
		double x, y;
	};

	vector<vector<double>> getLinearSplinesCoeffs(
		const vector<Point>& points)
	{
		vector<vector<double>> result(points.size() - 1, vector<double>(2));
		for (size_t i = 0; i < result.size(); ++i) {
			const double dx = points[i + 1].x - points[i].x;
			const double dy = points[i + 1].y - points[i].y;
			result[i] = { points[i].y, dy / dx };
		}
		return result;
	}

	vector<vector<double>> getParabolicSplinesCoeffs(
		const vector<Point>& points,
		size_t bound_id,
		double bound)
	{
		vector<vector<double>> result(points.size(), vector<double>(3));
		auto a = [&](size_t i) -> double& { return result[i][0]; };
		auto b = [&](size_t i) -> double& { return result[i][1]; };
		auto c = [&](size_t i) -> double& { return result[i][2]; };
		auto x = [&](size_t i) -> double { return points[i].x; };
		auto y = [&](size_t i) -> double { return points[i].y; };
		for (size_t i = 0; i < result.size(); ++i)
			a(i) = y(i);
		if (bound_id == 0) {
			b(0) = bound;
			for (size_t i = 1; i < result.size(); ++i)
				b(i) = 2.0 * (y(i) - y(i - 1)) / (x(i) - x(i - 1)) - b(i - 1);
		}
		else {
			b(result.size() - 1) = bound;
			for (size_t i = result.size() - 2; i != (size_t)-1; ++i)
				b(i) = 2.0 * (y(i + 1) - y(i)) / (x(i + 1) - x(i)) - b(i + 1);
		}
		for (size_t i = 0; i < result.size() - 1; ++i)
			c(i) = 0.5 * (b(i + 1) - b(i)) / (x(i + 1) - x(i));
		return result;
	}

	vector<vector<double>> getCubicSplinesCoeffs(
		const vector<Point>& points,
		size_t bound_id,
		double boundA,
		double boundB)
	{
		static const double _1_6 = 1.0 / 6.0;
		static const double _1_3 = 1.0 / 3.0;

		size_t cnt = points.size();
		vector<vector<double>> result(cnt - 1, vector<double>(4));
		auto a = [&](size_t i) -> double& { return result[i][0]; };
		auto b = [&](size_t i) -> double& { return result[i][1]; };
		auto c = [&](size_t i) -> double& { return result[i][2]; };
		auto d = [&](size_t i) -> double& { return result[i][3]; };
		auto x = [&](size_t i) -> double { return points[i].x; };
		auto y = [&](size_t i) -> double { return points[i].y; };
		auto dx = [&](size_t i) -> double { return x(i + 1) - x(i); };
		auto dy = [&](size_t i) -> double { return y(i + 1) - y(i); };

		for (size_t i = 0; i < cnt - 1; ++i)
			a(i) = y(i);

		vector<double> m;
		
		if (bound_id == self) {

			RealMatrix matrix(cnt);
			matrix[0][0] = dx(0) * _1_3;
			matrix[cnt - 1][cnt - 1] = dx(cnt - 2) * _1_3;

			for (size_t j = 1; j < cnt - 1; ++j)
				matrix[j][j] = (x(j + 1) - x(j - 1)) * _1_3;

			for (size_t j = 0; j < cnt - 1; ++j)
				matrix[j][j + 1] = matrix[j + 1][j] = dx(j) * _1_6;

			debug << matrix << '\n';
			debug << "Det: " << getDeterminant(matrix) << "\n\n";

			vector<double> g(cnt);
			g[0] = dy(0) / dx(0) - boundA;
			g[cnt - 1] = boundB - dy(cnt - 2) / dx(cnt - 2);
			for (size_t i = 1; i < cnt - 1; ++i)
				g[i] = dy(i) / dx(i) - dy(i - 1) / dx(i - 1);

			b(0) = boundA;
			b(cnt - 2) = boundB;
			
			for (const auto& g_el : g)
				debug << g_el << ' ';
			debug << "\n\n";

			m = solveSLAE_Cramer(matrix, g);

			for (const auto& m_el : m)
				debug << m_el << ' ';
			debug << "\n\n";
		}
		else { // bound_id == first_derivative

			cnt -= 2;

			RealMatrix matrix(cnt);

			for (size_t i = 1; i < cnt + 1; ++i)
				matrix[i - 1][i - 1] = _1_3 * (dx(i - 1) + dx(i));

			for (size_t i = 1; i < cnt; ++i)
				matrix[i - 1][i] = matrix[i][i - 1] = _1_6 * dx(i);

			debug << matrix << '\n';
			debug << "Det: " << getDeterminant(matrix) << "\n\n";

			vector<double> g(cnt);
			for (size_t i = 0; i < cnt; ++i)
				g[i] = dy(i + 1) / dx(i + 1) - dy(i) / dx(i);
			g[0] -= dx(0) * boundA * _1_6;
			g[cnt - 1] -= dx(cnt) * boundB * _1_6;

			for (const auto& g_el : g)
				debug << g_el << ' ';
			debug << "\n\n";

			m = solveSLAE_Cramer(matrix, g);
			m.insert(m.begin(), boundA);
			m.emplace_back(boundB);

			for (const auto& m_el : m)
				debug << m_el << ' ';
			debug << "\n\n";

		}

		for (size_t i = 0; i < m.size() - 1; ++i) {
			const double tx = dx(i);
			b(i) = dy(i) / tx - tx * _1_6 * (2 * m[i] + m[i + 1]);
			c(i) = 0.5 * m[i];
			d(i) = (m[i + 1] - m[i]) / (6.0 * tx);
		}

		return result;
	}

	vector<RealPolynomial> buildSplines(
		const vector<vector<double>>& coeffs,
		const vector<Point>& x) 
	{
		vector<RealPolynomial> result(coeffs.size());
		for (size_t i = 0; i < result.size(); ++i) {
			const size_t cnt = coeffs[i].size();
			const double& a = coeffs[i][0];
			const double& b = coeffs[i][1];
			const double& c = cnt > 2 ? coeffs[i][2] : 0.0;
			const double& d = cnt > 3 ? coeffs[i][3] : 0.0;
			switch (cnt) {
			case 2:
				result[i] = RealPolynomial({
					a - b * x[i].x,
					b
				});
				break;
			case 3:
				result[i] = RealPolynomial({
					a + x[i].x * (c * x[i].x - b),
					b - 2.0 * c * x[i].x,
					c
				});
				break;
			case 4:
				result[i] = RealPolynomial({
					a + x[i].x * (c * x[i].x - b - d * x[i].x * x[i].x),
					b - 2.0 * c * x[i].x + 3.0 * d * x[i].x * x[i].x,
					c - 3.0 * d * x[i].x,
					d
				});
				break;
			default:
				throw "Incorrect task type";
			}
		}
		return result;
	}

	const size_t W = 12;

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t taskType;
		while (cin >> taskType) {
			// Reading input data
			size_t splinesCount;
			cin >> splinesCount;
			vector<Point> grid(splinesCount + 1);
			for (Point& point : grid)
				cin >> point.x;
			for (Point& point : grid)
				cin >> point.y;
			sort(grid.begin(), grid.end(), [](const Point& a, const Point& b) { return a.x < b.x; });
			size_t bound = 0;
			double boundA = 0.0, boundB1 = 0.0, boundB2 = 0.0;
			if (taskType > 1) {
				cin >> bound;
				if (taskType == 2)
					cin >> boundA;
				else
					cin >> boundB1 >> boundB2;
			}
			size_t resultCount;
			cin >> resultCount;
			vector<Point> resultGrid(resultCount + 1);
			for (Point& point : resultGrid)
				cin >> point.x;
			char exprExists;
			cin >> exprExists >> ws;
			string expr;
			if (exprExists == yes)
				getline(cin, expr);

			// Calculating results
			vector<vector<double>> splines_coeffs;
			switch (taskType) {
			case linear:
				splines_coeffs = getLinearSplinesCoeffs(grid);
				break;
			case parabolic:
				splines_coeffs = getParabolicSplinesCoeffs(grid, bound, boundA);
				break;
			case cubic:
				splines_coeffs = getCubicSplinesCoeffs(grid, bound, boundB1, boundB2);
				break;
			default:
				cout << "Incorrect task type: " << taskType << ". Should be 1, 2 or 3\n\n";
				continue;
			}
			vector<RealPolynomial> splines = buildSplines(splines_coeffs, grid);

			map<double, const RealPolynomial&> mapped;
			for (size_t i = 1; i < grid.size(); ++i)
				mapped.emplace(grid[i].x, splines[i - 1]);

			for (Point& p : resultGrid)
				p.y = mapped.lower_bound(p.x)->second(p.x);

			vector<double> fx;
			double deviation = 0.0;

			if (exprExists) {
				fx.assign(resultGrid.size(), 0.0);
				char* pol_str = CreatePolStr(expr.c_str(), 0);

				for (size_t i = 0; i < resultGrid.size(); ++i) {
					fx[i] = EvalPolStr(pol_str, resultGrid[i].x);
					double tmp = fx[i] - resultGrid[i].y;
					deviation += tmp * tmp;
				}
				deviation /= (double)resultGrid.size();
				deviation = sqrt(deviation);

				delete[] pol_str;
			}

			// Writing results to output
			cout << "=========================================================\n";
			switch (taskType) {
			case linear:
				cout << "Linear splines\n";
				break;
			case parabolic:
				cout << "Parabolic splines\n";
				break;
			case cubic:
				cout << "Cubic splines\n";
				break;
			}

			cout << "\n---------------------------------------\n";
			cout << "Splines coefficients:\n\n";
			for (size_t i = 0; i < splines_coeffs[0].size(); ++i) {
				if (i != 0)
					cout << ' ';
				cout << setw(W) << (char)('a' + i);
			}
			cout << "\n\n";
			for (const auto& vec : splines_coeffs) {
				for (size_t i = 0; i < vec.size(); ++i) {
					if (i != 0)
						cout << ' ';
					cout << setw(W) << vec[i];
				}
				cout << '\n';
			}

			cout << "\n---------------------------------------\n";
			cout << "Resulting grid:\n\n";
			cout << setw(W) << "x" << ' ' << setw(W) << "S(x)";
			if (fx.size())
				cout << ' ' << setw(W) << "f(x)";
			cout << "\n\n";
			for (size_t i = 0; i < resultGrid.size(); ++i) {
				cout << setw(W) << resultGrid[i].x << ' ' << setw(W) << resultGrid[i].y;
				if (fx.size())
					cout << ' ' << setw(W) << fx[i];
				cout << '\n';
			}

			if (fx.size()) {
				cout << "\n---------------------------------------\n";
				cout << "Standard deviation is: " << setw(W) << deviation << "\n\n";
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
