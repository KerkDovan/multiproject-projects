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

	const char* messages[] = {
		"Hello, my friend!\0",
		"Ooo, Eee, Ooo-Ah-Ah, Ting-Tang, Wolla-Wolla, Bang-Bang!\0",
		"Let the bodies hit the floor, Let the bodies hit the floor, Let the bodies hit the... FLOO-O-O-O-O-O-OR!!!\0",
		"Did I ever tell you what the definition of \"Insanity\"?\0",
		"Why so serious?\0",
		"YOU ARE NOT PREPARED!\0"
	};

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
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

		// Создаём сокет клиента
		SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// Задаём параметры сокета клиента
		SOCKADDR_IN anAddr;
		anAddr.sin_family = AF_INET;
		anAddr.sin_port = htons(0xBEEF);
		anAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

		if (connect(client, (const sockaddr*)&anAddr, sizeof(anAddr))) {
			cout << "Could not connect to server\n";
		}
		else {
			cout << "Successfully connected to server\n";
			char msg[100];
			recieve_data(client, msg, sizeof(msg));
			cout << msg << '\n';
			srand(time(NULL));
			int sel = rand() % (sizeof(messages) / sizeof(const char*));
			send_data(client, messages[sel], strlen(messages[sel]));
		}

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif