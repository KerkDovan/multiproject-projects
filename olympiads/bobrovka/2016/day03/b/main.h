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
	//typedef vector<int> vi;
	//typedef vector<vi> vvi;

	const int INF = 1 << 30;

	int vCount, eCount;
	vector<vector<int>> edges;

	int time_in;
	vector<int> times;
	vector<int> visited;
	bool impossible;
	set<pair<int, int>> directed;

	void dfs1(int cur) {
		if (visited[cur])
			return;
		visited[cur] = true;
		times[cur] = ++time_in;
		for (int nxt : edges[cur])
			dfs1(nxt);
	}

	int dfs2(int cur, int par) {
		if (visited[cur])
			return times[cur];
		visited[cur] = true;
		int minimal = INF;
		for (int nxt : edges[cur])
			if (nxt != par)
				minimal = min(minimal, dfs2(nxt, cur));
		if (minimal != 1 && minimal >= times[cur])
			impossible = true;
		return minimal;
	}

	void dfs3(int cur, int par) {
		// Code by Yura: 
		if (visited[cur])
			return;
		visited[cur] = true;
		for (int nxt : edges[cur]) {
			if (nxt != par) {
				if (directed.find(make_pair(cur, nxt)) == directed.end()) {
					cout << cur + 1 << ' ' << nxt + 1 << '\n';
					directed.insert(make_pair(nxt, cur));
					directed.insert(make_pair(cur, nxt));
				}
				dfs3(nxt, cur);
			}
		}
		// Code by Kostya: 
		//visited[cur] = 1;
		//for (int nxt : edges[cur]) {
		//	if (nxt != par ) {
		//		if (visited[nxt] == 0 || visited[nxt] == 1)
		//			cout << cur + 1 << ' ' << nxt + 1 << '\n';
		//		if (visited[nxt] == 0)
		//			dfs3(nxt, cur);
		//	}
		//}
		//visited[cur] = 2;
	}

	//void dfs(vvi& g, vi& tm, vi& low, int& t, int u, int p = -1) {
	//	tm[u] = low[u] = t++;
	//	for (int v : g[u]) if (v != p) {
	//		if (tm[v] == -1) {
	//			dfs(g, tm, low, t, v, u);
	//			low[u] = low[v];
	//			if (low[v] == tm[v]) {
	//				cout << "(" << u << " " << v << ") is a bridge\n";
	//			}
	//		}
	//		else if (tm[v] < tm[u]) {
	//			low[u] = min(low[u], tm[v]);
	//		}
	//	}
	//}

	int main() {
	//#ifndef ONLINE_JUDGE
		freopen_in("b.in");
		freopen_out("b.out");
	//#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int testCount;
		cin >> testCount;
		for (int test = 0; test < testCount; ++test) {
			cin >> vCount >> eCount;
			edges.assign(vCount, vector<int>());
			for (int i = 0; i < eCount; ++i) {
				int a, b;
				cin >> a >> b;
				edges[a - 1].push_back(b - 1);
				edges[b - 1].push_back(a - 1);
			}
			time_in = 0;
			times.assign(vCount, INF);
			visited.assign(vCount, 0);
			dfs1(0);
			visited.assign(vCount, 0);
			impossible = false;
			dfs2(0, -1);
			if (impossible) {
				cout << "NO\n";
				continue;
			}
			cout << "YES\n";
			visited.assign(vCount, 0);
			directed.clear();
			dfs3(0, -1);
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif