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
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string.h>
#include <vector>

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

#define breakpoint_if(...)
#define breakpoint
#define only_multiproject(...)
#define debug_output(...)
#define freopen_in(filename) freopen(filename, "r", stdin)
#define freopen_out(filename) freopen(filename, "w", stdout)
#define close_files

#endif

// Changeable code continues here. 

	using namespace std;

	typedef long long ll;
	typedef unsigned long long ull;

	typedef bitset<102> Field;

	only_multiproject(
	ostream& operator << (ostream& os, const Field& field) {
		for (size_t i = 0; i < 102; ++i)
			cout << field[i];
		return os;
	}

	ostream& operator << (ostream& os, const vector<Field>& vfield) {
		for (size_t i = 0; i < vfield.size(); ++i)
			cout << vfield[i] << '\n';
		return os;
	}
	);

	const int dx[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	const int dy[] = { -1, -1, -1, 0, 0, 1, 1, 1 };

	int W, H, w, h;
	int l, r, t, b;

	vector<Field> field;
	vector<Field> canvas;
	vector<Field> edge;
	vector<Field> visited;

	void makeEdge() {
		edge.assign(h + 2, Field(0));
		l = w + 2;
		r = -1;
		t = h + 2;
		b = -1;
		int x, y;
		for (int i = 1; i <= h; ++i) {
			for (int j = 1; j <= w; ++j) {
				if (canvas[i][j]) {
					x = j;
					y = i;
					l = min(l, j);
					r = max(r, j);
					t = min(t, i);
					b = max(b, i);
				}
			}
		}
		queue<pair<int, int> > nxt;
		nxt.push(make_pair(x, y));
		visited.assign(h + 2, 0);
		visited[y][x] = true;
		while (!nxt.empty()) {
			x = nxt.front().first;
			y = nxt.front().second;
			nxt.pop();
			for (int i = 0; i < 8; ++i) {
				int tx = x + dx[i], ty = y + dy[i];
				if (tx < 0 || tx > w + 1 || ty < 0 || ty > h + 1 || visited[ty][tx])
					continue;
				if (canvas[ty][tx])
					nxt.push(make_pair(tx, ty));
				else
					edge[ty][tx] = true;
				visited[ty][tx] = true;
			}
		}
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> H >> W >> ws) {
			// Игровое поле
			field.assign(H + 2, 0);
			for (int i = 1; i <= H; ++i) {
				for (int j = 1; j <= W; ++j) {
					char c;
					cin >> c >> ws;
					field[i][j] = c == '*';
				}
			}
			// Холст с макетом снежинки
			cin >> h >> w >> ws;
			canvas.assign(h + 2, Field(0));
			for (int i = 1; i <= h; ++i) {
				for (int j = 1; j <= w; ++j) {
					char c;
					cin >> c >> ws;
					canvas[i][j] = c == '*';
				}
			}
			makeEdge();
			// Нахождение ответа
			int result = 0;
			Field tmp_c, tmp_e;
			for (int i = 1; i <= H - b + t; ++i) {
				for (int j = 1; j <= W - r + l; ++j) {
					bool apprpt = true;
					for (int k = -1; k <= b - t + 1; ++k) {
						if (l > j) {
							tmp_c = canvas[t + k] >> (l - j);
							tmp_e = edge[t + k] >> (l - j);
						}
						else {
							tmp_c = canvas[t + k] << (j - l);
							tmp_e = edge[t + k] << (j - l);
						}
						bool v1 = (field[i + k] & tmp_c) != tmp_c;
						bool v2 = (field[i + k] & tmp_e).any();
						if (v1 || v2) {
							apprpt = false;
							break;
						}
					}
					if (apprpt)
						++result;
				}
			}
			cout << result << '\n';
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif