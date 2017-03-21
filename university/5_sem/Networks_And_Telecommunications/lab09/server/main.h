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
#include <functional>
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

	const u_short SERVER_PORT = htons(54321);
	const u_long SERVER_ADDR = htonl(INADDR_ANY);
	const int BUFFERSIZE = 2048;

	template<class Type>
	string toCharArray(const Type& value) {
		static const size_t cnt = sizeof(value);
		string result;
		result.reserve(cnt);
		const char* buffer = (const char*)&value;
		for (size_t i = 0; i < cnt; ++i)
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

	struct Client {
		Client(const string& name, char op, const SOCKADDR_IN& addr) :
			name(name), operation(op), addr(addr) {}
		string name;
		char operation;
		SOCKADDR_IN addr;
	};

	class Storage {
	public:
		void emplace(const string& name, char operation, const SOCKADDR_IN& addr) {
			_storage[operation].emplace_back(name, operation, addr);
		}
		const vector<Client>& operator [] (char op) {
			return _storage[op];
		}
	private:
		map<char, vector<Client>> _storage;
	};

#define end_work \
			closesocket(*s);
#define exit_program(msg) { \
			cout << msg << " : " << WSAGetLastError() << endl; \
			unload_WSA(); \
			end_work; \
			exit(0); \
		}

	struct SendAndRecieve {
		SOCKET* s;
		SOCKADDR_IN* addr;
		int send(const string& data) const {
			return this->send(data, *addr);
		}
		int send(const string& data, const SOCKADDR_IN& sa) const {
			int cnt = sendto(*s, data.c_str(), (int)data.size(), 0, (LPSOCKADDR)&sa, sizeof(sa));
			if (cnt < 0)
				exit_program("send()");
			return cnt;
		}
		int recieve(string& data) {
			char buffer[BUFFERSIZE];
			int cnt = this->recieve(buffer);
			if (cnt < 0)
				exit_program("recieve()");
			data.clear();
			data.reserve((size_t)cnt);
			for (int i = 0; i < cnt; ++i)
				data += buffer[i];
			return cnt;
		}
		int recieve(char* data) {
			int tmp = sizeof(*addr);
			return recvfrom(*s, data, BUFFERSIZE, 0, (LPSOCKADDR)addr, &tmp);
		}
	};

	int main() {

		if (SERVER_ADDR == INADDR_NONE) {
			cout << "Server IP is not correct" << endl;
			return 0;
		}

		if (load_WSA()) {
			cout << "Unable to load WSA" << endl;
			return 0;
		}

#undef end_work
#define end_work \
			closesocket(s);

		SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
		if (s < 0)
			exit_program("socket()")

#undef end_work
#define end_work

		SOCKADDR_IN s_in;
		s_in.sin_family = AF_INET;
		s_in.sin_addr.s_addr = SERVER_ADDR;
		s_in.sin_port = SERVER_PORT;

		if (net_bind(s, (sockaddr*)&s_in, sizeof(s_in)) < 0)
			exit_program("bind()");

#undef end_work
#define end_work \
			closesocket(s);

		cout << "Server online" << endl;
		cout << "port: " << ntohs(SERVER_PORT) << endl;
		cout << endl;
				
		Storage clients;

		SOCKADDR_IN clnt;
		SendAndRecieve sar{ &s, &clnt };

		while (true) {

			string buffer;
			int recvlen = sar.recieve(buffer);

			cout << "----------------------\n";
			cout << "Client connected, recieved " << recvlen << " bytes\n" << endl;

			if (check_checksum(buffer) == false) {
				cout << "Checksum is incorrect, ignoring packet\n" << endl;
				continue;
			}

			string name;
			char op = buffer[1];
			const vector<Client>* clnts;

			switch (buffer[0]) {
			case 0: // registering new client
				for (int i = 2; i < recvlen - 1; ++i)
					name += buffer[i];
				cout << "Registering new client\n";
				cout << "Name : " << name << "\n";
				cout << "Operation : " << op << "\n";
				clients.emplace(name, op, clnt);
				buffer = "";
				break;
			case 1: // query for performers list
				buffer = "";
				clnts = &clients[op];
				for (auto iter = clnts->crbegin(); iter != clnts->crend(); ++iter) {
					const auto& ca = iter->addr;
					if (buffer.size() + (size_t)(
						sizeof(ca.sin_port) +
						sizeof(ca.sin_addr)) > BUFFERSIZE)
						break;
					buffer += toCharArray(ca.sin_port);
					buffer += toCharArray(ca.sin_addr);
				}
				cout << "Sending performers list\n";
				cout << "Operation : " << op << "\n";
				cout << "Performers found : " << clnts->size() << "\n";
				buffer += ' ';
				sar.send(make_checksum(buffer));
				break;
			default:
				buffer = "";
				cout << "Unrecognized command\n";
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
