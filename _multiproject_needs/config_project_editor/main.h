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
#include <locale>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string.h>
#include <tuple>
#include <vector>
#include <Windows.h>

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

	typedef long long ll;
	typedef unsigned long long ull;

	string revert_slashes(const string& line) {
		string result = line;
		for (char& c : result)
			if (c == '\\')
				c = '/';
			else if (c == '/')
				c = '\\';
		return result;
	}

	string make_slashes(const string& line, char slash) {
		string result = line;
		for (char& c : result)
			if (c == '\\' || c == '/')
				if (c != slash)
					c = slash;
		return result;
	}

	int _cdecl system(const string& cmd) {
		return system(cmd.c_str());
	}

	int _cdecl tosystem(const string& cmd) {
		return system(make_slashes(cmd, '\\'));
	}

	string exec(const char* cmd) {
		char buffer[128];
		string result = "";
		shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
		if (!pipe)
			throw runtime_error("popen() failed!");
		while (!feof(pipe.get())) {
			if (fgets(buffer, 128, pipe.get()) != NULL)
				result += buffer;
		}
		return result;
	}

	string exec(const string& cmd) {
		return exec(cmd.c_str());
	}

	vector<string> split(const string& str, const string& separators = "\n\r") {
		vector<string> result(1, "");
		for (char c : str) {
			if (find(separators.begin(), separators.end(), c) != separators.end()) {
				if (result.back() != "")
					result.emplace_back("");
				continue;
			}
			result.back() += c;
		}
		if (result.back() == "")
			result.pop_back();
		return result;
	}

	vector<pair<string, string>> getFilenames(const string& path, const string& toFind = "") { // [] < name, path >
		vector<pair<string, string>> result;
		vector<string> dirs, files;
		dirs = split(exec("dir /A:D /B \"" + path + "\" 2>nul"));
		files = split(exec("dir /A:-D /B \"" + path + "\" 2>nul"));
		if (toFind == "") {
			for (const string& file : files)
				result.emplace_back(file, path);
		}
		else {
			for (const string& file : files)
				if (file == toFind)
					result.emplace_back(file, path);
		}
		for (const string& dir : dirs) {
			auto content = getFilenames(path + dir + "\\", toFind);
			for (const auto& p : content)
				result.emplace_back(p);
		}
		return result;
	}

	string convert_n_in_format(const string& str) {
		string result;
		result.reserve(str.size());
		bool slash = false;
		for (char c : str) {
			if (c == '\\' && !slash) {
				slash = true;
				continue;
			}
			if (slash && c == 'n') {
				result += '\n';
				slash = false;
				continue;
			}
			if (slash)
				result += '\\';
			slash = false;
			result += c;
		}
		return result;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		string working_dir;
		getline(cin, working_dir);
		working_dir = make_slashes(working_dir, '\\');
		if (working_dir.back() != '\\')
			working_dir += '\\';

		string from, to;
		getline(cin, from);
		getline(cin, to);

		string formatFrom, formatTo;
		getline(cin, formatFrom);
		getline(cin, formatTo);
		
		string frmtFrom = convert_n_in_format(formatFrom);
		string frmtTo = convert_n_in_format(formatTo);

		const auto files = getFilenames(working_dir, from);

		for (const auto& p : files) {
			const string& name = p.first;
			const string& path = p.second;

			int n;
			FILE* file;
			
			file = fopen((path + name).c_str(), "r");
			fscanf(file, frmtFrom.c_str(), &n);
			fclose(file);

			file = fopen((path + name).c_str(), "w");
			fprintf(file, frmtTo.c_str(), n);
			fclose(file);
		}

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
