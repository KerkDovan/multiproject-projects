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
#include <process.h>
#include <queue>
#include <set>
#include <sstream>
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

	typedef unsigned __stdcall threadFunction(void*);

	template<typename _Ty>
	HANDLE startThread(threadFunction* func, _Ty* params) {
		return reinterpret_cast<HANDLE>(_beginthreadex(
			NULL,
			0,
			func,
			static_cast<void*>(params),
			0,
			NULL
		));
	}

	const int MAXCOUNT = 3;
	const int MAXONLINE = 10;
	const int MAXOFFLINE = 2;
	const int MAXWAIT = 1;
	const int TIMEMULTIPLIER = 1000;
	const int TIMEFORSIMULATING = 30;

	vector<u_short> ports;
	vector<string> fruits;
	multimap<time_t, string> to_print[2][MAXCOUNT];
	SOCKET* sockets[2][MAXCOUNT];

	inline void print(const stringstream& msg, int t, int id) {
		to_print[t][id].emplace(time(NULL), msg.str());
	}

	struct Sock_n_Addr {
		SOCKET s;
		u_short port;
		SOCKADDR_IN addr;
	};

	bool exitcode = 0;

	void start_server(SOCKET* s, u_short port) {
		// Создаём сокет сервера
		*s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// Задаём параметры для сокета сервера
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = INADDR_ANY;

		// Запускаем сервер
		bind(*s, (LPSOCKADDR)&addr, sizeof(addr));
		listen(*s, SOMAXCONN);
	}

	void stop_server(SOCKET& s) {
		// Отключаем сервер
		closesocket(s);
	}

	unsigned __stdcall server_waits(void* sna) {
		Sock_n_Addr* tmp = static_cast<Sock_n_Addr*>(sna);
		SOCKET serv = tmp->s;
		int len = sizeof(tmp->addr);
		u_short port = tmp->port;

		while (true) {
			// Пытаемся принять какого-нибудь клиента
			tmp->s = accept(serv, (sockaddr*)&tmp->addr, &len);

			// Защита от ошибок
			if (!sockets[0][port % MAXCOUNT])
				return 0;

			// Получаем сообщение от клиента
			char fruit[32] = {};
			recieve_data(tmp->s, fruit, sizeof(fruit));

			// Обрабатываем выход из цикла
			if (fruit[0] == 0)
				return 0;

			// Либо выводим принятое сообщение
			stringstream ss;
			ss << "BEE #" << (tmp->port % MAXCOUNT) << " has eaten " << fruit << '\n';
			print(ss, 0, tmp->port % MAXCOUNT);
		}
		return 0;
	}

	unsigned __stdcall server(void* p) {
		u_short port = 0xBEE0 + *static_cast<u_short*>(p);
		ports.emplace_back(port);
		SOCKET*& s = sockets[0][port % MAXCOUNT];
		SOCKET exit_s;

		// Пока не конец работы программы
		while (!exitcode) {
			// Запускаем сервер
			start_server(s, port);
			stringstream ss;
			ss << "BEE #" << (port % MAXCOUNT) << " is now sitting on the flower #" << s << '\n';
			print(ss, 0, port % MAXCOUNT);

			// Ждём подключений
			Sock_n_Addr sna{ *s, port };
			HANDLE handle;
			handle = startThread(&server_waits, &sna);
			WaitForSingleObject(handle, (rand() % MAXONLINE + 1) * TIMEMULTIPLIER);

			if (s) {
				// Прерываем ожидание подключений
				sna.addr = { AF_INET, port, { { (UCHAR)inet_addr("127.0.0.1") } } };
				exit_s = *s;
				connect(exit_s, reinterpret_cast<const sockaddr*>(&sna.addr), sizeof(sna.addr));
				send_data(exit_s, "", 0);
			}

			// Отключаем сервер
			if (s)
				stop_server(*s);
			ss.str(string());
			ss.clear();
			ss << "BEE #" << (port % MAXCOUNT) << " has flew back to the hive\n";
			print(ss, 0, port % MAXCOUNT);

			// Случайное время сервер "лежит"
			Sleep((rand() % MAXOFFLINE + 1) * TIMEMULTIPLIER);
		}
		return 0;
	}

	void init_client(SOCKET& s, SOCKADDR_IN& addr) {
		// Создаём сокет клиента
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// Задаём параметры для сокета клиента
		addr = { AF_INET, 0, { { (UCHAR)inet_addr("127.0.0.1") } } };
	}

	unsigned __stdcall client(void* n) {
		int id = *static_cast<int*>(n);

		// Инициализируем клиента
		SOCKET s;
		SOCKADDR_IN addr;
		init_client(s, addr);

		// Пока не конец работы программы
		while (!exitcode) {
			// Выжидаем случайное время до следующего подключения
			Sleep((rand() % MAXWAIT + 1) * TIMEMULTIPLIER);

			// Пытаемся подключиться к случайному серверу
			u_short port = 0xBEE0 + rand() % MAXCOUNT;
			addr.sin_port = htons(port);

			// Защита от ошибок
			if (sockets[1][id])
				break;

			stringstream ss;
			if (!connect(s, (const sockaddr*)&addr, sizeof(addr))) {
				// В случае подключения отправляем данные
				char fruit[32] = {};
				int t = rand() % fruits.size();
				memcpy(fruit, fruits[t].c_str(), fruits[t].size());
				ss << "Minotaurus #" << id << " feeds the BEE #" << (port % MAXCOUNT) << " with " << fruit << '\n';
				send_data(s, fruit, strlen(fruit));
			}
			else {
				// Иначе сообщаем об этом
				ss << "Minotaurus #" << id << " tried to feed the BEE #" << (port % MAXCOUNT) << " but couldn't find it\n";
			}
			print(ss, 1, id);
		}
		// Отключаем клиента
		if (sockets[1][id])
			closesocket(s);
		stringstream ss;
		ss << "Minotaurus #" << id << " has resigned from these lands\n";
		print(ss, 1, id);

		return 0;
	}

	unsigned __stdcall timer(void*) {
		// Каждую секунду выводим в консоль текущее время
		time_t cur, prev = time(NULL) - 1, start = prev;
		while (true) {
			cur = time(NULL);
			if (cur > prev) {
				// Выводим в консоль текущее время
				char str[16] = {};
				tm t = *localtime(&cur);
				strftime(str, sizeof(str), "%H:%M:%S", &t);
				cerr << str << '\n';

				// В определённый момент начинаем завершать все процессы
				if (cur - start > TIMEFORSIMULATING - 5 && !exitcode) {
					exitcode = 1;
					//for (int i = 0; i < 2; ++i) {
					//	for (int j = 0; j < MAXCOUNT; ++j) {
					//		delete sockets[i][j];
					//		sockets[i][j] = nullptr;
					//	}
					//}
					cerr << "The darkness has come!\n";
				}
			}
			prev = cur;
		}
	}

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		startThread(&timer, &timer);

		srand(static_cast<unsigned int>(time(NULL)));

		// Инициализируем процесс библиотеки wsock32.dll
		WSADATA wsaData;
		int err = WSAStartup(0x0101, &wsaData);
		if (err == SOCKET_ERROR) {
			cout << "WSAStartup() failed: " << GetLastError() << '\n';
			return 0;
		}

		// Загружаем передаваемые сообщения
		string fruit = "apple";
		while (cin >> ws, getline(cin, fruit), fruit != "") {
			fruits.emplace_back(fruit);
			fruit = "";
		}

		// Создаём серверы и клиенты
		int ids[MAXCOUNT];
		for (int i = 0; i < MAXCOUNT; ++i)
			ids[i] = i;
		HANDLE threads[2 * MAXCOUNT];
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < MAXCOUNT; ++j) {
				sockets[i][j] = new SOCKET();
				threads[i * MAXCOUNT + j] = startThread(i ? &client : &server, ids + j);
				stringstream ss;
				if (i)
					ss << "Minotaurus #" << j << " has come to these lands\n";
				else
					ss << "BEE #" << j << " was born\n";
				print(ss, i, j);
				Sleep((rand() % 2 + 1) * TIMEMULTIPLIER);
			}
		}

		// Работаем определённое время, потом завершаем
		WaitForMultipleObjects(2 * MAXCOUNT, threads, true, TIMEFORSIMULATING * TIMEMULTIPLIER);

		// Выводим полученные логи в файл
		multimap<time_t, string> result_print;
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < MAXCOUNT; ++j) {
				for (auto p : to_print[i][j])
					result_print.emplace(p);
				delete sockets[i][j];
			}
		}
		for (const auto p : result_print) {
			char t[16] = {};
			tm tmp = *localtime(&p.first);
			strftime(t, sizeof(t), "%H:%M:%S", &tmp);
			cout << t << ": " << p.second;
		}

		// Выгружаем библиотеку
		WSACleanup();

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif