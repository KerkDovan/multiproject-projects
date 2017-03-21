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

	typedef long long ll;
	typedef unsigned long long ull;

	typedef bitset<101> Visited;
	typedef pair<size_t, size_t> Pair;
	typedef vector<Pair> Path;
	typedef pair<Path, size_t> Result;

	size_t n, m; // 3 <= n <= 100; 2 <= m <= 1000;
	Pair Start, End;
	vector<vector<size_t>> edges;
	vector<vector<bool>> neighbours;

	Result dfs(Visited visitedA, Visited visitedB, const Pair& cur) {
		if (cur == End)
			return Result(Path(1, cur), 0);
		visitedA[cur.first] = visitedB[cur.second] = true;
		Result minPath, tmpPath;
		for (size_t nxtA : edges[cur.first]) {
			for (size_t nxtB : edges[cur.second]) {
				if (nxtA == nxtB || !neighbours[nxtA][nxtB] ||
					nxtA == cur.second && nxtB == cur.first ||
					//nxtA == cur.second && nxtB == cur.second ||
					//nxtB == cur.first && nxtA == cur.first ||
					nxtA == cur.first && nxtB == cur.second ||
					visitedA[nxtA] && visitedB[nxtB])
					continue;
				tmpPath = dfs(visitedA, visitedB, Pair(nxtA, nxtB));
				size_t tmpAdd = (nxtA != cur.first) + (nxtB != cur.second);
				if (tmpPath.first[0] == End &&
					((minPath.second == 0) ^ (tmpPath.second + tmpAdd <= minPath.second)))
				{
					swap(minPath, tmpPath);
					minPath.second += tmpAdd;
				}
			}
		}
		minPath.first.push_back(cur);
		return minPath;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> n >> m >> 
			Start.first >> Start.second >> 
			End.first >> End.second)
		{
			edges.assign(n + 1, vector<size_t>());
			neighbours.assign(n + 1, vector<bool>(n + 1, false));
			for (size_t i = 0; i <= n; ++i)
				edges[i].emplace_back(i);
			for (size_t i = 0; i < m; ++i) {
				size_t a, b;
				cin >> a >> b;
				edges[a].emplace_back(b);
				edges[b].emplace_back(a);
				neighbours[a][b] = neighbours[b][a] = true;
			}
			Result path = dfs(0, 0, Start);
			cout << path.second << ' ' << path.first.size() << '\n';
			for (auto iter = path.first.crbegin(); iter != path.first.crend(); ++iter)
				cout << iter->first << ' ' << iter->second << '\n';
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
