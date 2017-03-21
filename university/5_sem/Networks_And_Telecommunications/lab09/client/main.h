// Changeable code starts here. 

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string.h>
#include <thread>
#include <tuple>
#include <vector>

#include "network.h"

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
	using namespace Network;

	typedef long long ll;
	typedef unsigned long long ull;

	typedef int Number;
	const size_t NUMBERSIZE = sizeof(Number);
	const size_t PORTSIZE = sizeof(SOCKADDR_IN::sin_port);
	const size_t ADDRSIZE = sizeof(SOCKADDR_IN::sin_addr);

	const u_long CLIENT_ADDR = htonl(INADDR_ANY);
	const u_long SERVER_ADDR = inet_addr("127.0.0.1");
	const u_short CLIENT_PORT = htons(0);
	const u_short SERVER_PORT = htons(54321);
	const size_t BUFFERSIZE = 2048;
	const size_t TIMEOUT = 1000;

	const vector<string> NAMES = {
		"Alpha", "Bravo", "Gamma", "Delta", "Billy", "Tommy", "Eddy",
		"Alice", "Elly", "Charlie", "Robert", "Danny", "Bonnie", "Clyde",
		"Tony", "Sia", "Shia", "Rob", "Henry", "Tim", "Jack", "Bruce",
		"Harley", "Barry", "Jerry", "Clark", "Matthew", "Peter", "Benjamin",
		"Natasha", "James", "Francisco", "Caitlin", "Jason", "John", "Jensen",
		"Jared", "Samuel", "Dean", "Michael", "Mark", "Jeffrey", "Ray",
		"Genevieve", "Nicole", "Chuck", "Stephen", "Katie", "Colin", "David",
		"Emily", "Willa", "Thea", "Moira", "Felicity", "Antonio", "Philip",
		"Antony", "Catherine", "Roy", "Slade", "Quentin", "Damien", "Echo",
		"Rick", "Morty", "Marty", "Emmett",
	};
	const string OPERATIONS = "=+-*/%^&|";
	map<char, function<Number(const Number&, const Number&)>> ACTIONS = {
		{ '+', [](const Number& a, const Number& b) -> Number { return std::move(a + b); } },
		{ '-', [](const Number& a, const Number& b) -> Number { return std::move(a - b); } },
		{ '*', [](const Number& a, const Number& b) -> Number { return std::move(a * b); } },
		{ '/', [](const Number& a, const Number& b) -> Number { return std::move(a / b); } },
		{ '%', [](const Number& a, const Number& b) -> Number { return std::move(a % b); } },
		{ '^', [](const Number& a, const Number& b) -> Number { return std::move(a ^ b); } },
		{ '&', [](const Number& a, const Number& b) -> Number { return std::move(a & b); } },
		{ '|', [](const Number& a, const Number& b) -> Number { return std::move(a | b); } },
	};

	template<class Cont>
	auto getRandom(const Cont& container) -> decltype(container[0]) {
		return container[(size_t)rand() % container.size()];
	}

	template<class Type>
	Type fromCharArray(const char* arr) {
		Type result;
		memcpy((char*)&result, arr, sizeof(Type));
		return result;
	}

	template<class Type>
	char* toCharArray(const Type& data) {
		const int cnt = sizeof(Type);
		char result[cnt];
		memcpy(result, (char*)&data, cnt);
		return result;
	}

	template<class Type>
	string toCharArrayS(const Type& data) {
		const int cnt = sizeof(Type);
		char* buffer = (char*)&data;
		string result;
		for (int i = 0; i < cnt; ++i)
			result += buffer[i];
		return result;
	}

	char get_checksum(const string& data) {
		char checksum = 0;
		for (size_t i = 0; i < data.size() - 1; ++i)
			checksum ^= i & 1 ? ~data[i] : -data[i];
		return checksum;
	}

	string make_checksum(const string& data) {
		string result = data;
		result.back() = get_checksum(data);
		return result;
	}

	bool check_checksum(const string& data) {
		return get_checksum(data) == data.back();
	}

#define end_work
#define exit_program(msg) { \
			cout << msg << " : " << WSAGetLastError() << endl; \
			unload_WSA(); \
			end_work; \
			exit(0); \
		}

	struct SendAndRecieve {
		SOCKET* s;
		SOCKADDR_IN* to;
		int send(const string& data) const {
			return this->send(data, *to);
		}
		int send(const string& data, const SOCKADDR_IN& addr) const {
			int cnt = sendto(*s, data.c_str(), (int)data.size(), 0, (LPSOCKADDR)&addr, sizeof(addr));
			if (cnt < 0)
				exit_program(0);
			return cnt;
		}
		int recieve(string& data) const {
			SOCKADDR_IN tmp;
			return this->recieve(data, tmp);
		}
		int recieve(string& data, SOCKADDR_IN& from) const {
			char buffer[BUFFERSIZE];
			int tmp = sizeof(from);
			int sz = recvfrom(*s, buffer, sizeof(buffer), 0, (LPSOCKADDR)&from, &tmp);
			if (sz < 0)
				return sz;
			data.clear();
			data.reserve((size_t)sz);
			for (int i = 0; i < sz; ++i)
				data += buffer[i];
			return sz;
		}
	};

	int main() {

		srand((unsigned int)time((time_t* const)NULL));

		if (SERVER_ADDR == INADDR_NONE) {
			cout << "Server IP is not correct" << endl;
			return 0;
		}

		if (load_WSA()) {
			cout << "Unable to load WSA" << endl;
			return 0;
		}

#undef end_work
#define end_work

		SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
		if (s < 0)
			exit_program("socket()")

#undef end_work
#define end_work \
			closesocket(s);

		SOCKADDR_IN s_in;
		memset(&s_in, 0, sizeof(s_in));
		s_in.sin_family = AF_INET;
		s_in.sin_addr.s_addr = CLIENT_ADDR;
		s_in.sin_port = CLIENT_PORT;

		if (net_bind(s, (LPSOCKADDR)&s_in, sizeof(s_in)) < 0)
			exit_program("bind()");

		const string name = getRandom(NAMES);
		const char operation = getRandom(OPERATIONS);

		cout << "Client " << name << " online\n";
		cout << "Operation : " << operation << "\n" << endl;
		
		SOCKADDR_IN server;
		memset(&server, 0, sizeof(server));
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = SERVER_ADDR;
		server.sin_port = SERVER_PORT;

		SendAndRecieve sar{ &s, &server };

		string buffer;

		buffer.assign(2 + name.size() + 1, 0);
		buffer[1] = operation;
		for (size_t i = 0; i < name.size(); ++i)
			buffer[2 + i] = name[i];

		sar.send(make_checksum(buffer));

		buffer = "";
		int a, b;
		char op;
		string tmp;
		vector<SOCKADDR_IN> performers;
		SOCKADDR_IN performer;
		int sz;
		Number num;
		int wsa_error;
		int counter;

		if (operation == '=') {
			timeval tv;
			tv.tv_sec = 0;
			tv.tv_usec = TIMEOUT * 1000;
			if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv)) < 0)
				exit_program(0);
		}

		while (true) {

			performers.clear();

			switch (operation) {
			case '=': // task-giver
				std::this_thread::sleep_for(std::chrono::milliseconds(TIMEOUT));
				op = '=';
				while (op == '=')
					op = getRandom(OPERATIONS);
				// ask for performers list
				buffer.assign(3, 0);
				buffer[0] = 1;
				buffer[1] = op;
				sar.send(make_checksum(buffer));
				sz = sar.recieve(buffer);
				if (sz < 0)
					exit_program(0);
				if (check_checksum(buffer) == false) {
					cout << "Checksum is incorrect, ignoring\n";
					break;
				}
				for (size_t i = 0; i + PORTSIZE + ADDRSIZE <= (size_t)sz; i += PORTSIZE + ADDRSIZE) {
					memset(&performer, 0, sizeof(performer));
					performer.sin_family = AF_INET;
					tmp = "";
					for (size_t j = 0; j < PORTSIZE; ++j)
						tmp += buffer[i + j];
					performer.sin_port = fromCharArray<decltype(performer.sin_port)>(tmp.c_str());
					tmp = "";
					for (size_t j = 0; j < ADDRSIZE; ++j)
						tmp += buffer[i + PORTSIZE + j];
					performer.sin_addr = fromCharArray<decltype(performer.sin_addr)>(tmp.c_str());
					performers.emplace_back(performer);
				}
				if (performers.size() == 0) {
					cout << "No performers found for operation " << op << "\n";
					break;
				}
				// send task to performer
				wsa_error = WSAETIMEDOUT;
				counter = 0;
				while ((wsa_error == WSAETIMEDOUT || wsa_error == WSAECONNRESET) && counter++ < 10) {
					performer = getRandom(performers);
					buffer.assign(1 + 2 * NUMBERSIZE + 1, 0);
					buffer[0] = op;
					cout << "Task: ";
					for (size_t i = 0; i < 2; ++i) {
						num = (Number)rand();
						cout << num << ' ';
						cout << (i == 0 ? op : '=') << ' ';
						tmp = toCharArrayS(num);
						for (size_t j = 0; j < NUMBERSIZE; ++j)
							buffer[1 + i * NUMBERSIZE + j] = tmp[j];
					}
					sar.send(make_checksum(buffer), performer);
					sz = sar.recieve(buffer);
					if (sz < 0) {
						cout << "\n";
						if ((wsa_error = WSAGetLastError()) == WSAETIMEDOUT)
							cout << "Timed out.";
						else if (wsa_error == WSAECONNRESET)
							cout << "Performer is unavailable right now.";
						else
							exit_program(0);
						cout << " Trying another performer.\n";
					}
					else {
						buffer.pop_back();
						num = fromCharArray<Number>(buffer.c_str());
						cout << num << "\n";
						wsa_error = 0;
					}
				}
				break;
			default: // performers
				sz = sar.recieve(buffer, performer);
				if (sz < 0)
					exit_program(0);
				if (check_checksum(buffer) == false) {
					cout << "Checksum is incorrect\n";
					break;
				}
				tmp = "";
				for (size_t i = 0; i < NUMBERSIZE; ++i)
					tmp += buffer[i];
				a = fromCharArray<Number>(tmp.c_str());
				tmp = "";
				for (size_t i = NUMBERSIZE; i < 2 * NUMBERSIZE; ++i)
					tmp += buffer[i];
				b = fromCharArray<Number>(tmp.c_str());
				num = ACTIONS[operation](a, b);
				buffer = toCharArrayS(num);
				buffer.push_back(0);
				sar.send(make_checksum(buffer), performer);
				cout << a << ' ' << operation << ' ' << b << " = " << num << "\n";
				break;
			}
			cout << endl;
		}

		closesocket(s);

		unload_WSA();

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

#undef exit_program
#undef end_work

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif
