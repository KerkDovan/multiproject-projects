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

#define _MULTIPROJECT_STACK_SIZE_MB_ 512

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

	const size_t FIELDSIZE = 1000 * 1000;
	const int CHECKPOINT_DISTANCE = 10; // smaller value - more memory, bigger value - more time

	typedef bitset<FIELDSIZE> Field;

	struct Query {
		unsigned char op;
		size_t x;
		union {
			size_t y, k;
		};
	};

	Field base;

	size_t w, h, cnt;
	map<size_t, Field> fields;
	vector<Query> queries;

	Field respond(Field field, const Query& query);

	inline Field op_set(Field field, size_t x, size_t y) {
		field.set(y * w + x);
		return field;
	}

	inline Field op_reset(Field field, size_t x, size_t y) {
		field.reset(y * w + x);
		return field;
	}

	inline Field op_inverse(Field field, size_t y) {
		return field ^= (base << y * w);
	}

	inline Field op_get_back(size_t k) {
		auto iter = fields.lower_bound(cnt - k);
		Field result = iter->second;
		for (size_t i = cnt - iter->first; i <= k; ++i)
			result = respond(result, queries[i]);
		return result;
	}

	inline Field respond(Field field, const Query& query) {
		switch (query.op) {
		case 1:
			field = op_set(field, query.x, query.y);
			break;
		case 2:
			field = op_reset(field, query.x, query.y);
			break;
		case 3:
			field = op_inverse(field, query.y);
			break;
		case 4:
			field = op_get_back(query.k);
			break;
		}
		return field;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		while (cin >> h >> w >> cnt) {
			fields.clear();
			fields.emplace(cnt, 0);
			queries.clear();
			queries.resize(cnt + 1);
			base.reset();
			for (size_t i = 0; i < w; ++i)
				base[i] = 1;
			Field current = 0;
			int until_save = CHECKPOINT_DISTANCE;
			for (size_t i = 1; i <= cnt; ++i) {
				int op = 0;
				size_t x = 0, y = 0, k = 0;
				cin >> op;
				switch (op) {
				case 1:
				case 2:
					cin >> y >> x;
					break;
				case 3:
					cin >> y;
					break;
				case 4:
					cin >> y;
					++y;
					break;
				}
				queries[i] = { (unsigned char)op, x - 1, y - 1 };
				current = respond(current, queries[i]);
				cout << current.count() << '\n';
				if (op == 4 || --until_save == 0) {
					fields[cnt - i] = current;
					until_save = CHECKPOINT_DISTANCE;
				}
			}
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif