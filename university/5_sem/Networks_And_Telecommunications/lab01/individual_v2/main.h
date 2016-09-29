// Changeable code starts here. 

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iomanip>
#include <map>
#include <process.h>
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

	const int MAX_WAITING_BEETWEEN_INIT = 3;
	const int MAX_ONLINE = 10;
	const int MAX_OFFLINE = 10;
	const int MAX_WAITING_BETWEEN_CHECK = 3;
	const int SECOND = 1000;
	const int MAX_SERVER_COUNT = 2;
	const u_short INIT_PORT = 0xBEE0;

	bool exitcode = false;

	struct Info {
		SOCKET socket;
		u_short port;
		SOCKADDR_IN addr;
	};

	struct WaiterData {
		u_short port;
		u_short time;
	};

	string cur_time() {
		time_t tmp = time(NULL);
		tm t = *localtime(&tmp);
		char res[32]{};
		strftime(res, sizeof(res), "%H:%M:%S", &t);
		return string(res);
	}

	void start_server(Info& info) {
		// Создаём сокет сервера
		info.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (-1 == info.socket)
			cout << "server #" << info.port - INIT_PORT << ": socket() error\n";

		// Задаём параметры для сокета сервера
		info.addr.sin_family = AF_INET;
		info.addr.sin_port = htons(info.port);
		info.addr.sin_addr.s_addr = INADDR_ANY;

		// Запускаем сервер
		if (-1 == bind(info.socket, reinterpret_cast<SOCKADDR*>(&info.addr), sizeof(info.addr)))
			cout << "server #" << info.port - INIT_PORT << ": bind() error\n";
		if (-1 == listen(info.socket, SOMAXCONN))
			cout << "server #" << info.port - INIT_PORT << ": listen() error\n";
	}

	void stop_server(Info& info) {
		// Отключаем сервер
		closesocket(info.socket);
	}

	unsigned __stdcall accept_closer(void* p) {
		// Получаем необходимые данные
		WaiterData* data = static_cast<WaiterData*>(p);

		// Выжидаем необходимое время
		Sleep(static_cast<DWORD>(data->time));

		// Создаём сокет клиента
		SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (-1 == s)
			cout << "accept_closer: socket() error\n";
	
		// Задаём параметры для сокета клиента
		SOCKADDR_IN addr;
		addr = { AF_INET, htons(data->port) };
		addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	
		// Сообщаем серверу, что время вышло
		data->port = static_cast<u_short>(-1);
	
		// Закрываем текущий accept
		if (connect(s, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)))
			cout << "accept_closer: connect() error\n";

		// Разрываем соединение, завершаем работу функции
		shutdown(s, SD_BOTH);
		closesocket(s);

		return 0;
	}

	unsigned __stdcall server(void* p) {
		u_short port = *static_cast<u_short*>(p);
		while (!exitcode) {
			Info info{ {}, port };
			// Запускаем сервер
			start_server(info);
			cout << cur_time() << " server #" << port - INIT_PORT << " is now online\n";

			// Ограничиваем работу сервера по времени
			WaiterData wd{ port, static_cast<u_short>(SECOND * ((static_cast<int>(port) * rand()) % MAX_ONLINE + 1)) };
			startThread(&accept_closer, &wd);

			// Ожидаем подключения клиентов
			SOCKADDR_IN clnt;
			int addr_len = sizeof(clnt);
			SOCKET clnt_s;
			while (wd.port == port) {
				if (-1 == (clnt_s = accept(info.socket, reinterpret_cast<sockaddr*>(&clnt), &addr_len)))
					cout << cur_time() << " server #" << port - INIT_PORT << " accept() error\n";
				else
					closesocket(clnt_s);
			}

			// Приостанавливаем сервер
			stop_server(info);
			cout << cur_time() << " server #" << port - INIT_PORT << " is now offline\n";
			Sleep(SECOND * ((static_cast<int>(port) * rand()) % MAX_OFFLINE + 1));
		}
		return 0;
	}
	
	void init_client(Info& info) {
		// Создаём сокет клиента
		info.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (-1 == info.socket)
			cout << "client: socket() error\n";

		// Задаём параметры для сокета клиента
		info.addr = { AF_INET, htons(info.port) };
		info.addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	}

	unsigned __stdcall client(void*) {
		Info info;
		while (!exitcode) {
			// Инициализируем клиента
			info.port = INIT_PORT + rand() % MAX_SERVER_COUNT;
			init_client(info);
			
			// Пытаемся подключиться к случайному серверу
			if (connect(info.socket, reinterpret_cast<sockaddr*>(&info.addr), sizeof(info.addr)))
				cout << cur_time() << " cannot connect to server #" << info.port - INIT_PORT << '\n';
			else
				cout << cur_time() << " connected to server #" << info.port - INIT_PORT << " successfully\n";

			// Закрываем соединение, отключаем клиента
			shutdown(info.socket, SD_BOTH);
			closesocket(info.socket);
			
			// Ждём случайное время до следующей попытки соединения
			Sleep(SECOND * (rand() % MAX_WAITING_BETWEEN_CHECK + 1));
		}
		return 0;
	}

	unsigned __stdcall timer(void*) {
		// Каждую секунду выводим в консоль текущее время
		time_t cur, prev = time(NULL) - 1;
		while (true) {
			cur = time(NULL);
			if (cur > prev) {
				// Выводим в консоль текущее время
				char str[16] = {};
				tm t = *localtime(&cur);
				strftime(str, sizeof(str), "%H:%M:%S", &t);
				cerr << str << '\n';
			}
			prev = cur;
		}
	}

	int main() {
	#ifndef ONLINE_JUDGE
		//freopen_in("input.txt");
		freopen_out("output.txt"); startThread(&timer, &timer);
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		srand(static_cast<unsigned>(time(NULL)));

		// Инициализируем процесс библиотеки wsock32.dll
		WSADATA wsaData;
		int err = WSAStartup(0x0101, &wsaData);
		if (err == SOCKET_ERROR) {
			cout << "WSAStartup() failed: " << GetLastError() << '\n';
			return 0;
		
}
		// Запускаем серверы и клиенты в разных потоках
		HANDLE handles[MAX_SERVER_COUNT + 1];
		int ports[MAX_SERVER_COUNT];
		for (int i = 0; i < MAX_SERVER_COUNT; ++i)
			ports[i] = INIT_PORT + i;
		for (int i = 0; i < MAX_SERVER_COUNT; ++i) {
			handles[i] = startThread(&server, &ports[i]);
			Sleep(SECOND * (rand() % MAX_WAITING_BEETWEEN_INIT));
		}
		Sleep(SECOND * 2);
		handles[MAX_SERVER_COUNT] = startThread(&client, &client);

		// Ожидаем нажатия клавиши Esc
		while (_getch() != 27)
			;
		exitcode = true;

		// Завершаем работу с потоками
		for (int i = 0; i <= MAX_SERVER_COUNT; ++i)
			CloseHandle(handles[i]);

		// Выгружаем библиотеку
		WSACleanup();

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif