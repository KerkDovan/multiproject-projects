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

#include "network.h"

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

	inline const char* cur_time(char* buffer) {
		time_t tmp = time(NULL);
		tm t = *localtime(&tmp);
		strftime(buffer, 9, "%H:%M:%S", &t);
		return buffer;
	}

	inline string cur_time() {
		char buffer[9];
		cur_time(buffer);
		return string(buffer);
	}

	inline ostream& output_str(ostream& os, const char* str) {
		size_t i = 0;
		while (str[i])
			os << str[i++];
		return os;
	}

	int main() {
	#ifndef ONLINE_JUDGE
		//freopen_in("input.txt");
		//freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		// Инициализируем процесс библиотеки wsock32.dll
		WSADATA wsaData;
		int err = WSAStartup(0x0101, &wsaData);
		if (err == SOCKET_ERROR) {
			cout << "WSAStartup() failed: " << GetLastError() << '\n';
			return 0;
		}
		
		// Создаём сокет сервера
		SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// Задаём параметры для сокета сервера
		SOCKADDR_IN sa_in;
		sa_in.sin_family = AF_INET;
		sa_in.sin_port = htons(0xBEEF);
		sa_in.sin_addr.s_addr = INADDR_ANY;

		// Пытаемся запустить сервер
		if (bind(server, (LPSOCKADDR)&sa_in, sizeof(sa_in))) {
			cout << "bind() failed\n";
		}
		else {
			cout << "Server online\n\n";
			// Ждём клиентов
			while (true) {
				// Общаемся с клиентом
				listen(server, SOMAXCONN);
				SOCKADDR_IN from;
				int from_len = sizeof(from);
				SOCKET client = accept(server, (sockaddr*)&from, &from_len);
				cout << "Client " << client << " connected at time " << cur_time() << '\n';
				char* hello = "Hello, World!\n";
				send_data(client, hello, strlen(hello));
				cout << "Client " << client << " succesfully recieved data\n";
				char answer[256] = {};
				recieve_data(client, answer, sizeof(answer));
				cout << "Client " << client << " sent message: ";
				output_str(cout, answer) << '\n';
				closesocket(client);
				cout << "Client " << client << " disconnected at time " << cur_time() << "\n\n";
			}
		}

		closesocket(server);

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif