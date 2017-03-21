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

	class Trie {
	public:
		Trie() {}
		Trie(char c) : cur(c) {}
		~Trie() {
			for (Trie* trie : nxt)
				delete trie;
		}
		void insert(const char* word, int page) {
			if (strlen(word) == 0) {
				if (pgs.empty() || pgs.back() != page)
					pgs.push_back(page);
			}
			else {
				char t = (char)toupper((int)word[0]) - 'A';
				if (nxt[t] == nullptr)
					nxt[t] = new Trie(t);
				nxt[t]->insert(word + 1, page);
			}
		}
		void print(ostream& os, const string& str) const {
			if (pgs.size()) {
				os << str << ' ';
				for (size_t i = 0; i < pgs.size(); ++i) {
					size_t t = i + 1;
					while (t < pgs.size() - 1 && pgs[t] == pgs[t - 1] + 1)
						++t;
					if (t - i > 1) {
						os << pgs[i] << '-' << pgs[t];
						i = t - 1;
					}
					else
						os << pgs[i];
					if (i != pgs.size() - 1)
						cout << ',';
				}
				cout << '\n';
			}
			for (int i = 0; i < 26; ++i) {
				if (nxt[i] == nullptr)
					continue;
				string tmp = str + (char)(i + 'A');
				nxt[i]->print(os, tmp);
			}
		}
	private:
		char cur = 0;
		Trie* nxt[26] = {};
		vector<int> pgs;
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		size_t pgSize;
		cin >> pgSize >> ws;
		Trie root;
		vector<string> paragraph;
		string line;
		size_t pg = 0, ln = 0;
		bool neof = false;
		while (neof = (bool)getline(cin, line), true) {
			debug << line << '\n';
			if (line == "") {
				vector<size_t> pgs(paragraph.size());
				for (size_t i = 0; i < pgs.size(); ) {
					pgs[i] = pg;
					++ln;
					if (ln == pgSize) {
						++pg;
						ln = 0;
					}
					++i;
				}
				if (ln >= pgSize - 1) {
					++pg;
					ln = 0;
				}
				else
					++ln;
				for (size_t i = 0; i < paragraph.size(); ++i) {
					string word;
					for (size_t j = 0; j < paragraph[i].size(); ++j) {
						if (isalpha((unsigned char)paragraph[i][j]))
							word += paragraph[i][j];
						else {
							if (word != "") {
								root.insert(word.c_str(), pgs[i] + 1);
								debug << word << '\n';
							}
							word = "";
						}
					}
					if (word != "")
						root.insert(word.c_str(), pgs.back());
				}
				paragraph.clear();
			}
			else
				paragraph.push_back(line);
			if (!neof)
				break;
			line = "";
		}
		root.print(cout, "");

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
