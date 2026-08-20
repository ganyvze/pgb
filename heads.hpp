#ifndef MINE_HEADS
#define MINE_HEADS

#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <map>
#include <queue>
#include <stack>
#include <array>
#include <algorithm> 
#include <conio.h> 
#include <Windows.h>
#include <fstream>
#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <thread>

using std::to_string;
using std::swap;
using std::exit;
using std::max;
using std::min;

using std::string;
using std::vector;
using std::pair;
using std::queue;
using std::stack;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::array;

using LL = long long;
using UL = unsigned long long;

namespace PGB { extern bool quick_output; }

inline string G2U(string text) {
	return text;
}

inline void my_sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

inline void put(string text) {
	string out_s = G2U(text);
	if(PGB::quick_output) {
		fputs(out_s.c_str(), stdout);
		fflush(stdout);
		return;
	}
	int len = static_cast<int>(out_s.size());
	for(int i = 0; i < len; i++) {
		unsigned char c = static_cast<unsigned char>(out_s[i]);
		putchar(c);
		if(c >= 0xF0 && i + 3 < len) {
			putchar(out_s[++i]);
			putchar(out_s[++i]);
			putchar(out_s[++i]);
		} else if(c >= 0xE0 && i + 2 < len) {
			putchar(out_s[++i]);
			putchar(out_s[++i]);
		} else if(c >= 0xC0 && i + 1 < len) {
			putchar(out_s[++i]);
		}
		fflush(stdout);
		if(rand() % 2) my_sleep(1);
	}
}

inline void putf(const char* format, ...) {
	char buffer[4096];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);
	put(string(buffer));
}

inline void init_console_encoding() {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif
}

#endif
