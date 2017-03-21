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

	typedef u_long AddrType;
	typedef u_short PortType;

	const size_t PORTSIZE = sizeof(SOCKADDR_IN::sin_port);
	const size_t ADDRSIZE = sizeof(SOCKADDR_IN::sin_addr);

	const AddrType ADDR = inet_addr("127.0.0.1");
	const size_t BUFFERSIZE = 2048;
	const size_t RECIEVE_TIMEOUT = 10 * 1000;

	template<class Number>
	Number StrToNum(const string& str) {
		if (str.size() == 0)
			return 0;
		Number number = str[0] - '0';
		for (size_t i = 1; i < str.size(); ++i)
			number = number * 10 + str[i] - '0';
		return number;
	}

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

#define end_work
#define exit_program(msg) { \
			cout << msg << " : " << WSAGetLastError() << endl; \
			Network::unload_WSA(); \
			end_work; \
			exit(0); \
		}

	struct SendAndRecieve {
		SOCKET* s;
		SOCKADDR_IN to;
		int send(const string& data) const {
			return this->send(data, to);
		}
		int send(const string& data, const SOCKADDR_IN& addr) const {
			int cnt = sendto(*s, data.c_str(), (int)data.size(), 0, (LPSOCKADDR)&addr, sizeof(addr));
			if (cnt < 0)
				exit_program("send()");
			return cnt;
		}
		int recieve(string& data) const {
			SOCKADDR_IN tmp;
			return this->recieve(data, tmp);
		}
		int recieve(string& data, SOCKADDR_IN& from) const {
			char buffer[BUFFERSIZE];
			int tmp = sizeof(from);
			fd_set fds;
			FD_ZERO(&fds);
			FD_SET(*s, &fds);
			struct timeval tv;
			tv.tv_sec = 0;
			tv.tv_usec = RECIEVE_TIMEOUT;
			int n = select(*s, &fds, NULL, NULL, &tv);
			if (n <= 0)
				return -1;
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

	struct MSAU {
		static const size_t PC_COUNT = 8;
		SOCKET s;
		SendAndRecieve next;
		SendAndRecieve* pc[PC_COUNT];
		MSAU() {
			for (size_t i = 0; i < PC_COUNT; ++i)
				pc[i] = nullptr;
		}
		bool checkConnection(const SendAndRecieve& sar) const {
			string tmp;
			sar.send("0");
			return sar.recieve(tmp) > 0;
		}
		bool checkConnection() const {
			return checkConnection(next);
		}
		bool checkConnection(size_t pc_id) {
			if (pc[pc_id] == nullptr)
				return false;
			bool checked = checkConnection(*pc[pc_id]);
			if (checked == false) {
				delete pc[pc_id];
				pc[pc_id] = nullptr;
			}
			return checked;
		}
		bool tryConnectPC(const SOCKADDR_IN& s_in) {
			// Looking for empty slot
			size_t id = (size_t)-1;
			for (size_t i = 0; i < PC_COUNT; ++i) {
				if (pc[i] == nullptr || checkConnection(i) == false) {
					id = i;
					break;
				}
			}
			if (id == (size_t)-1) {
				cout << "Cannot connect new PC : no empty slots" << endl;
				return false;
			}
			// Connecting to empty slot
			pc[id] = new SendAndRecieve();
			pc[id]->s = &this->s;
			pc[id]->to = s_in;
			cout << "New PC successfully connectied to slot #" << id << endl;
			return true;
		}
		void connectNext(const PortType& port) {
			next.s = &this->s;
			next.to.sin_family = AF_INET;
			next.to.sin_addr.S_un.S_addr = ADDR;
			next.to.sin_port = port;
		}
		void resend(const string& data, const SOCKADDR_IN& from) {
			// Looking for sender
			size_t id = (size_t)-1;
			for (size_t i = 0; i < PC_COUNT; ++i) {
				if (pc[i] != nullptr && memcmp(&pc[i]->to, &from, sizeof(from)) == 0) {
					id = i + 1;
					break;
				}
			}
			// Sender detected
			cout << "Recieved data from ";
			if (id == (size_t)-1) {
				cout << "previous MSAU";
				id = 0;
			}
			else
				cout << "PC #" << (id - (size_t)1);
			cout << endl;
			// Needed to find available PC
			static const auto find_next = [&]() {
				while (id < PC_COUNT && !checkConnection(id))
					++id;
			};
			// Looking for next reciever
			find_next();
			if (id == PC_COUNT) {
				if (checkConnection()) {
					next.send(data);
					cout << "Data recent to next MSAU" << endl;
					return;
				}
				id = 0;
				find_next();
				if (id == PC_COUNT) {
					cout << "There is no available PC or MSAU, packet destroyed" << endl;
					return;
				}
			}
			cout << "Data resent to PC #" << id << endl;
			pc[id]->send(data);
		}
	};

	int main(int argc, char** argv) {

		// Randomizing
		srand((unsigned int)time((time_t* const)NULL));

		// Trying to read ports from command line
		PortType port, next;
		if (argc <= 1) {
			cout << "Command line arguments should be: PORT [NEXT]" << endl;
			port = 1337;
			next = 1338;
		}
		else {
			port = StrToNum<PortType>(argv[1]);
			if (argc > 2)
				next = StrToNum<PortType>(argv[2]);
			else
				next = port + 1;
		}
		cout << "MSAU port: " << port << endl;
		cout << "Next MSAU port: " << next << endl;
		port = htons(port);
		next = htons(next);

		// Verificating IP
		if (ADDR == INADDR_NONE) {
			cout << "IP is not correct" << endl;
			return 0;
		}

		// Loading WSA library
		if (load_WSA()) {
			cout << "Unable to load WSA" << endl;
			return 0;
		}

#undef end_work
#define end_work

		// Creating UDP socket
		SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
		if (s < 0)
			exit_program("socket()")

#undef end_work
#define end_work \
			closesocket(s);

		// Trying to start server on selected port
		SOCKADDR_IN s_in;
		memset(&s_in, 0, sizeof(s_in));
		s_in.sin_family = AF_INET;
		s_in.sin_addr.S_un.S_addr = ADDR;
		s_in.sin_port = port;

		if (net_bind(s, (LPSOCKADDR)&s_in, sizeof(s_in)) < 0)
			exit_program("bind()");

		// Initializing MSAU
		MSAU msau;
		msau.s = s;
		msau.connectNext(next);
		cout << "MSAU successfully initialized and ready to use" << endl;

		// Listening port
		while (true) {

			// Auxiliary data from anybody
			string buffer;
			SOCKADDR_IN from;
			int recieved;

			// Receiving data
			recieved = msau.next.recieve(buffer, from);
			if (recieved < 0)
				continue;
			//cout << "Recieved some data" << endl;

			// Resending data
			if (buffer == "0") {
				//cout << "Recieved hello, sent back" << endl;
				msau.next.send("0", from);
				continue;
			}
			else if (buffer == "00") {
				cout << "Registering new PC" << endl;
				buffer[1] = msau.tryConnectPC(from) ? '1' : '0';
				msau.next.send(buffer, from);
				continue;
			}
			string tmp;
			tmp.reserve(recieved);
			for (size_t i = 0; i < (size_t)recieved; ++i)
				tmp += buffer[i];
			msau.resend(tmp, from);

		}

		// Closing socket
		closesocket(s);

		// Unloading WSA library
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
