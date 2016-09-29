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
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string.h>
#include <tuple>
#include <vector>

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
#define freopen_in(filename) freopen(filename, "r", stdin)
#define freopen_out(filename) freopen(filename, "w", stdout)
#define close_files

#endif

// Changeable code continues here. 

	using namespace std;

	typedef long long ll;
	typedef unsigned long long ull;

	

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		// Хочу поставить сюда точку останова.
		breakpoint;

		// Хочу остановиться здесь, если выполнилось условие.
		breakpoint_if(2 + 2 == 4);

		// Просто map<string, long long>, который хранит пары <имя счётчика, счётчик>.
		// Объявлен в multiproject. Использование вне отладки не рекомендуется.
		assert(typeid(breakpoint_counters) == typeid(std::map<std::string, long long>));
		assert(breakpoint_counters == project::tools::debugging::BreakpointCounters);

		// Конкретный счётчик, найденный по имени в breakpoint_counters.
		// Использование вне отладки не рекомендуется.
		breakpoint_counter(kek lalka "это имя");

		// Устанавливает счётчику определённое значение.
		breakpoint_counter_init(kek lalka "это имя", 1295);

		// Увеличивает значение счётчика на определённое значение.
		breakpoint_counter_offset(kek lalka "это имя", 42);

		// Ставит точку останова, если значение счётчика равно определённому значению.
		breakpoint_when(kek lalka "это имя", 1337);

		// Ставит точку останова, если значение счётчика равно определённому значению.
		// Вне зависимости от установки точки останова увеличивает значения счётчика
		// на определённое значение.
		breakpoint_when_offset(kek lalka "это имя", 1337, -1015);

		// Сбрасывает значения всех счётчиков. В multiproject все значения счётчиков
		// между запусками main в потоках значения будут сохраняться, если не сделать
		// вызов этого макроса.
		breakpoint_counters_clear;

		close_files;
		breakpoint_counters_clear;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif