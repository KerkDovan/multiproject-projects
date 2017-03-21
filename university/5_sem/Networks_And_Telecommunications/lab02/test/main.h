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
#include <tuple>
#include <vector>

#include "libs\network.h"

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
	using namespace Network;

	typedef long long ll;
	typedef unsigned long long ull;

	ostream& print_one_line(ostream& os, const char* msg) {
		size_t len = strlen(msg);
		for (size_t i = 0; i < len; ++i) {
			if (msg[i] == '\n' || msg[i] == '\r')
				return os;
			os << msg[i];
		}
		return os;
	}

#define snd(msg)	send(sender, msg, strlen(msg ## "\n"), 0);
#define rcv			recv(sender, msg_recv, 256, 0); print_one_line(cout, msg_recv) << '\n'; breakpoint;



	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		load_WSA();

		SOCKET sender = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		SOCKADDR_IN anAddr;
		anAddr.sin_family = AF_INET;
		anAddr.sin_port = htons(25);
		hostent *server_adress = gethostbyname("smtp.gmail.com");
		anAddr.sin_addr.s_addr = *((unsigned long *)server_adress->h_addr_list[0]);

		if (connect(sender, (const sockaddr*)&anAddr, sizeof(anAddr))) {
			cout << "Could not connect to server\n";
		}
		else {
			cout << "Successfully connected to server\n";

			char *msg_recv = new char[256];

			rcv;

			snd("HELO IMKEK");
			snd("MAIL FROM: iwannaberabbit@gmail.com");
			rcv;
			
			snd("RCPT TO: bogomolov.yuriy@gmail.com");
			rcv;

			closesocket(sender);
		}

		unload_WSA();

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif