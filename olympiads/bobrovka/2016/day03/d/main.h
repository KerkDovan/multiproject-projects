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

	const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	int worldWidth, worldHeight;
	char world[1000][1000];
	int distances[1000][1000];
	vector<bitset<1000>> visited;
	queue<pair<int, int>> nxt, after_nxt;
	int landlockness[26];

	int main() {
		//#ifndef ONLINE_JUDGE
		freopen_in("d.in");
		freopen_out("d.out");
		//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> worldHeight >> worldWidth >> ws) {
			only_multiproject(
				memset(distances, 0, sizeof(distances));
				memset(world, 0, sizeof(world));
			);
			visited.assign((size_t)worldWidth, 0);
			for (int i = 0; i < 26; ++i)
				landlockness[i] = 1 << 30;
			for (int y = 0; y < worldHeight; ++y) {
				for (int x = 0; x < worldWidth; ++x) {
					cin.get(world[x][y]);
					if (world[x][y] == 'W')
						nxt.push(make_pair(x, y));
					world[x][y] -= 'A';
				}
				cin >> ws;
			}
			while (!nxt.empty()) {
				int curx, cury;
				tie(curx, cury) = nxt.front();
				nxt.pop();
				visited[curx][cury] = true;
				for (int i = 0; i < 8; ++i) {
					int tx = curx + dx[i];
					int ty = cury + dy[i];
					if (tx < 0 || tx >= worldWidth ||
						ty < 0 || ty >= worldHeight ||
						visited[tx][ty])
						continue;
					if (world[tx][ty] == world[curx][cury]) {
						distances[tx][ty] = distances[curx][cury];
						nxt.push(make_pair(tx, ty));
					}
					else if (distances[tx][ty] == 0) {
						distances[tx][ty] = distances[curx][cury] + 1;
						after_nxt.push(make_pair(tx, ty));
					}
				}
				if (nxt.empty())
					swap(nxt, after_nxt);
			}
			for (int x = 0; x < worldWidth; ++x) {
				for (int y = 0; y < worldHeight; ++y) {
					landlockness[world[x][y]] = min(landlockness[world[x][y]], distances[x][y]);
				}
			}
			for (int i = 0; i < 26; ++i) {
				if (i != 'W' - 'A' && landlockness[i] != 1 << 30)
					cout << (char)('A' + i) << ' ' << landlockness[i] - 1 << '\n';
			}
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif