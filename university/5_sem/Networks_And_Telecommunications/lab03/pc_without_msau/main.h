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
	using namespace std::chrono;
	using namespace Network;

	typedef long long ll;
	typedef unsigned long long ull;

	typedef u_long AddrType;
	typedef u_short PortType;

	const size_t PORTSIZE = sizeof(SOCKADDR_IN::sin_port);
	const size_t ADDRSIZE = sizeof(SOCKADDR_IN::sin_addr);

	const AddrType MSAU_ADDR = inet_addr("127.0.0.1");
	const AddrType PC_ADDR = htonl(INADDR_ANY);
	const size_t BUFFERSIZE = 2048;
	const int MICRO_TO_MILLI = 1000;
	const int RECIEVE_TIMEOUT = 10 * MICRO_TO_MILLI;
	const int TIMER_MULTIPLIER = 50;
	const int TIMER_TO_NEW_MESSAGE_INITIAL = 50 * TIMER_MULTIPLIER;
	const int TIMER_TO_REELECT_MONITOR_INITIAL = 200 * TIMER_MULTIPLIER;
	const int TIMER_TO_MONITOR_HELLO_INITIAL = 50 * TIMER_MULTIPLIER;
	const int TIMER_TO_TOKEN_EXISTENCE_INITIAL = 500 * TIMER_MULTIPLIER;
	const int TIMER_TO_HAVE_TOKEN = 5 * TIMER_MULTIPLIER;

	enum FrameTypes {
		Error	= '-',
		Echo	= 'e',
		Token	= 't',
		Data	= 'd',
		Monitor = 'm',
		Stop	= 's',
	};

	const vector<string> RANDOM_PHRASES = {
		"Hello, World!\n",
		"It's high noon somewhere\n",
		"To be, or not to be\n",
		"Just for keks\n",
		"I wonder what happens, if I hit the cray button,\nI guarantee that whole place starts jumping!\nI wonder what happens, if I hit the cray button,\nI guarantee that whole place starts jumping!\nI wonder what happens, if I hit the cray button,\nI'm a do it!\nWatch me hit the cray button\nI hit the cray button\nI hit the cray button\n",
		"Zombie zombie zombie,\nZombie zombie zombie,\nRe-re-reanimated,\nBack-back-back-back from the dead\n",
		"Running for your life\n(From Shia LaBeouf.)\nHe's brandishing a knife.\n(It's Shia LaBeouf.)\nLurking in the shadows\nHollywood superstar Shia LaBeouf.\nLiving in the woods,\n(Shia LaBeouf.)\nKilling for sport,\n(Shia LaBeouf.)\nEating all the bodies\nActual, cannibal Shia LaBeouf.\n",
		"Just DO IT! Yesterday you said \"tomorrow\", so JUST DO IT!",
		"I might be strong,\nI might be weak,\nThere might be a part of me\nThat I won't let you keep.\nBeen on this road and come this far\nDon't need a man to hold my hand,\nI just want one to hold my heart!\n",
		"Dovahkiin, Dovahkiin\nnaal ok zin los vahriin\nwah dein vokul mahfaeraak ahst vaal!\nAhrk fin norok paal graan\nfod nust hon zindro zaan\nDovahkiin, fah hin kogaan mu draal!\n",
		"V lesu rodilas' yolochka,\nV lesu ona rosla,\nZimoy i letom stroynaya,\nZelyonaya byla.\n",
		"Born underground, suckled from a teat of stone\nRaised in the dark, the safety of our mountain home\nSkin made of iron, steel in our bones\nTo dig and dig makes us free\nCome on brothers sing with me!\nI am a dwarf and I'm digging a hole\nDiggy diggy hole, diggy diggy hole\nI am a dwarf and I'm digging a hole\nDiggy diggy hole, digging a hole\n",
	};

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

	struct Timer {
	public:
		explicit Timer(size_t count) {
			limit = count;
		}
		void reset() {
			point = system_clock::now();
		}
		bool get() {
			return limit <= duration_cast<milliseconds>(system_clock::now() - point).count();
		}
	private:
		size_t limit;
		time_point<system_clock> point;
	};

	vector<int> MAC_ADDRESSES;
	Timer timer_new_message(TIMER_TO_NEW_MESSAGE_INITIAL);
	Timer timer_reelect_monitor(TIMER_TO_REELECT_MONITOR_INITIAL);
	Timer timer_monitor_hello(TIMER_TO_MONITOR_HELLO_INITIAL);
	Timer timer_token_existence(TIMER_TO_TOKEN_EXISTENCE_INITIAL);
	Timer timer_have_token(TIMER_TO_HAVE_TOKEN);

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
			int sz = recvfrom(*s, buffer, BUFFERSIZE, 0, (LPSOCKADDR)&from, &tmp);
			if (sz < 0)
				return sz;
			data.clear();
			data.reserve((size_t)sz);
			for (int i = 0; i < sz; ++i)
				data += buffer[i];
			return sz;
		}
	};

	struct Packet {
		static const char CHECKED_SYMBOL = '1';
		static const char UNCHECKED_SYMBOL = '0';
		char type;
		int from;
		int to;
		string data;
		bool checked;
		bool operator == (const Packet& rhs) const {
			return make_tuple(type, from, to, data) ==
				make_tuple(rhs.type, rhs.from, rhs.to, rhs.data);
		}
		Packet() {}
		Packet(const string& packet) {
			if (packet.empty()) {
				type = Error;
				return;
			}
			type = packet[0];
			data = "";
			size_t offset = sizeof(type);
			char tmp = CHECKED_SYMBOL;
			switch (type) {
			case Echo:
				break;
			case Token:
				break;
			case Data:
				from = fromCharArray<decltype(from)>(packet.c_str() + offset);
				offset += sizeof(from);
				to = fromCharArray<decltype(to)>(packet.c_str() + offset);
				offset += sizeof(to);
				for (size_t i = offset; i < packet.size() - sizeof(tmp); ++i)
					data += packet[i];
				tmp = packet.back();
				break;
			case Monitor:
				from = fromCharArray<decltype(from)>(packet.c_str() + offset);
				offset += sizeof(from);
				to = fromCharArray<decltype(to)>(packet.c_str() + offset);
				tmp = packet.back();
				break;
			case Stop:
				break;
			default:
				break;
			}
			checked = tmp == CHECKED_SYMBOL;
		}
		static Packet makeStopFrame() {
			return Packet(string() + (char)Stop);
		}
		static Packet makeTokenFrame() {
			return Packet(string() + (char)Token);
		}
		static Packet makeDataFrame(int from, int to, const string& data, bool checked) {
			Packet p;
			p.type = Data;
			p.from = from;
			p.to = to;
			p.data = data;
			p.checked = checked;
			return p;
		}
		static Packet makeMonitorFrame(int MAC, bool checked) {
			Packet p;
			p.type = Monitor;
			p.from = MAC;
			p.to = MAC;
			p.checked = checked;
			return p;
		}
		string toString() const {
			string result;
			result += type;
			switch (type) {
			case Echo:
				break;
			case Token:
				break;
			case Data:
				result += toCharArrayS(from);
				result += toCharArrayS(to);
				result += data;
				result += checked ? CHECKED_SYMBOL : UNCHECKED_SYMBOL;
				break;
			case Monitor:
				result += toCharArrayS(from);
				result += toCharArrayS(to);
				result += checked ? CHECKED_SYMBOL : UNCHECKED_SYMBOL;
				break;
			case Stop:
				break;
			default:
				break;
			}
			return result;
		}
	};

	Packet previousDataPacket;

	struct PC {
		static const size_t RESEND_TRIES_COUNT = 3;
		static const size_t TOKENS_MAX_COUNT = 2;
		bool monitor = false;
		bool has_token = false;
		int MAC;
		SOCKET s;
		SendAndRecieve msau;
		//size_t toSendCount = 2;
		pair<int, string> pending = { -1, "" };
		bool toResend = false;
		size_t resendTries = 0;
		size_t tokensAccepted = 0;
		bool sentReelect = false;

		bool checkConnection() const {
			cout << "Checking connection to MSAU" << endl;
			string tmp;
			msau.send("0");
			return msau.recieve(tmp) > 0;
		}
		void connectMSAU(const PortType& port) {
			msau.s = &this->s;
			msau.to.sin_family = AF_INET;
			msau.to.sin_addr.S_un.S_addr = MSAU_ADDR;
			msau.to.sin_port = port;
		}
		void receivedPacket(const string& packet) {
			Packet p(packet);
			bool send_back = true;
			switch (p.type) {
			case Echo:
				//cout << "Hello from MSAU" << endl;
				break;
			case Token:
				cout << "Token arrived" << endl;
				timer_token_existence.reset();
				timer_have_token.reset();
				has_token = rand() % 2; // toSendCount > 0;
				send_back = !has_token;
				tokensAccepted += has_token;
				break;
			case Data:
				if (p.from == MAC) {
					if (p.checked) {
						cout << "Packet to " << p.to << " delivered successfully" << endl;
						pending = make_pair(-1, "");
						//--toSendCount;
						toResend = false;
					}
					else {
						cout << "Packet to " << p.to << " was not delivered" << endl;
						toResend = true;
					}
					send_back = false;
				}
				else {
					if (p.to == MAC) {
						if (p.checked == false) {
							cout << "Message from " << p.from << ":" << endl;
							cout << p.data << endl;
							p.checked = true;
						}
					}
				}
				break;
			case Monitor:
				timer_reelect_monitor.reset();
				if (p.checked == false) {
					monitor = false;
					has_token = false;
					toResend = false;
					if (sentReelect && p.to < MAC) {
						send_back = false;
						break;
					}
					cout << "System monitor electing" << endl;
					if (p.to < MAC) {
						cout << "Became the candidate" << endl;
						p.to = MAC;
					}
					else if (p.to == MAC) {
						cout << "Elected as system monitor" << endl;
						sentReelect = false;
						monitor = true;
						p = Packet::makeTokenFrame();
					}
				}
				else {
					//cout << "System monitor exists" << endl;
					if (sentReelect)
						send_back = false;
					sentReelect = false;
					if (monitor) {
						if (p.to == MAC)
							send_back = false;
						else {
							cout << "Found one more system monitor, reelecting" << endl;
							p = Packet::makeMonitorFrame(MAC, false);
						}
					}
				}
				break;
			case Stop:
				if (monitor)
					p = Packet::makeTokenFrame();
				else {
					cout << "Stop frame recieved" << endl;
					toResend = false;
					sentReelect = false;
				}
				break;
			default:
				send_back = false;
				break;
			}
			if (send_back)
				msau.send(p.toString());
		}
	};

	int main(int argc, char** argv) {

		// Randomizing
		srand((unsigned int)time((time_t* const)NULL));

		// Trying to read MSAU port and PC MAC from command line
		PortType port;
		PortType MAC;
		if (argc <= 2) {
			cout << "Command line arguments should be: NEXT_PORT PC_MAC" << endl;
			port = 323;
			MAC = 327;
		}
		else {
			port = StrToNum<PortType>(argv[1]);
			MAC = StrToNum<PortType>(argv[2]);
		}
		cout << "Next pc port: " << port << endl;
		cout << "PC MAC address: " << MAC << endl;
		port = htons(port);

		// Initializing PC
		PC pc;
		pc.MAC = MAC;
		pc.connectMSAU(port);

		// Verificating IP
		if (PC_ADDR == INADDR_NONE) {
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
		pc.s = socket(AF_INET, SOCK_DGRAM, 0);
		if (pc.s < 0)
			exit_program("socket()")

#undef end_work
#define end_work \
			closesocket(pc.s);

		// Trying to start client
		SOCKADDR_IN s_in;
		memset(&s_in, 0, sizeof(s_in));
		s_in.sin_family = AF_INET;
		s_in.sin_addr.S_un.S_addr = PC_ADDR;
		s_in.sin_port = htons(MAC);

		if (net_bind(pc.s, (LPSOCKADDR)&s_in, sizeof(s_in)) < 0)
			exit_program("bind()");

		// Auxiliary data
		string buffer;
		int recieved;
		string phrase;
		Packet prev;

		// Loading MAC addresses of other PCs in ring
		ifstream macs("macs.txt");
		int tmp_mac;
		cout << "Other PC's: ";
		while (macs >> tmp_mac)
			if (tmp_mac != MAC) {
				MAC_ADDRESSES.emplace_back(tmp_mac);
				cout << tmp_mac << ", ";
			}
		cout << endl << endl;
		macs.close();

		// Waiting for incoming packets
		while (true) {

			buffer = "";

			// Timers ticking and handling
			//if (timer_new_message.get()) {
			//	timer_new_message.reset();
			//	cout << "Messages to send: " << pc.toSendCount << endl;
			//	++pc.toSendCount;
			//}

			// System monitor presence is important
			if (pc.monitor) {
				// Saying "It's me!"
				if (timer_monitor_hello.get()) {
					timer_monitor_hello.reset();
					pc.msau.send(Packet::makeMonitorFrame(pc.MAC, true).toString());
				}
				// Checking token existence
				if (timer_token_existence.get()) {
					timer_token_existence.reset();
					cout << "Token loss, sending new" << endl;
					pc.msau.send(Packet::makeStopFrame().toString());
				}
			}
			else {
				// Saying "It seems, we don't have a monitor
				if (timer_reelect_monitor.get()) {
					timer_reelect_monitor.reset();
					cout << "Possible system monitor loss" << endl;
					pc.msau.send(Packet::makeMonitorFrame(pc.MAC, false).toString());
					pc.sentReelect = true;
				}
			}

			// It's needed to say something sometimes
			if (pc.has_token) {

				// If there is packet pending
				if (rand() % 2 && !timer_have_token.get()) {

					if (pc.toResend && (++pc.resendTries > PC::RESEND_TRIES_COUNT ||
						pc.tokensAccepted >= PC::TOKENS_MAX_COUNT))
					{
						cout << "It seems the reciever is offline. Removing message" << endl;
						pc.pending = make_pair(-1, "");
						pc.resendTries = 0;
						pc.tokensAccepted = 0;
					}

					if (pc.pending.first == -1) {
						// Choosing random MAC and random phrase
						tmp_mac = getRandom(MAC_ADDRESSES);
						phrase = getRandom(RANDOM_PHRASES);
						pc.pending = make_pair(tmp_mac, phrase);
						pc.toResend = true;
					}
					
					if (pc.toResend) {
						cout << "Sending message" << endl;

						// Packing data to packet
						Packet p = Packet::makeDataFrame(MAC, tmp_mac, phrase, false);

						// Sending data to selected PC
						pc.msau.send(p.toString());
						pc.toResend = false;

					}
				}
				else {
					cout << "Sending token" << endl;
					pc.msau.send(Packet::makeTokenFrame().toString());
					pc.has_token = false;
				}
			}

			// Receiving any data
			recieved = pc.msau.recieve(buffer);
			if (recieved < 0)
				continue;

			// Handling data
			pc.receivedPacket(buffer);

		}

		// Closing socket
		closesocket(pc.s);

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
