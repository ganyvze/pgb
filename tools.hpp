#ifndef MINE_TOOLS
#define MINE_TOOLS

constexpr LL nulltime = LLONG_MIN;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
bool Isout;
void getstr(string &s) {
	s.clear();
	char in = getchar();
	while(in == ' ' || in == '\t' || in == '\n' || in == '\r') in = getchar();
	while(in != ' ' && in != '\n' && in != '\r' && in != EOF) s += in, in = getchar();
	if(in == EOF) exit(-1);
}
void getlstr(string &s) {
	s.clear();
	char in = getchar(); 
	while(in != '\n' && in != '\r' && in != EOF) s += in, in = getchar();
	if(in == EOF) exit(-1);
}
LL get() {
    string s;
    bool iserror = 0, islong;
    LL ans, ign;
    do {
	    if(iserror) put("无效数字。\n请输入有效数字: ");
    	iserror = 0, islong = 0, ans = 0;
    	getstr(s);
    	if(s == "/hub") {
    		Isout = 1;
    		return 0;
		}
	    bool have = 0;
	    for(LL i : s) if(i == 'e' || i == 'u' || i == 'E' || i == 'U') {
	    	have = true;
	    	break;
		}
	    if(!sscanf(s.c_str(), "%lld", &ign) || have || (*s.begin() == '0' && s.size() > 1)) {
	    	iserror = 1;
	    	continue;
		}
	    if(s.size() > to_string(LONG_LONG_MAX).size()) {
	    	islong = 1;
	    put("数字过大。\n请输入更小的数字: ");
	    	continue;
		}
		sscanf(s.c_str(), "%lld", &ans);
	} while(iserror || islong);
    return ans;
}
double getf() {
    string s;
    bool iserror = 0, islong;
    double ans, ign;
    do {
	    if(iserror) put("无效数字。\n请输入有效数字: ");
    	iserror = 0, islong = 0, ans = 0;
    	getstr(s);
    	if(s == "/hub") {
    		Isout = 1;
    		return 0;
		}
	    bool have = 0;
	    for(LL i : s) if(i == 'e' || i == 'u' || i == 'E' || i == 'U') {
	    	have = true;
	    	break;
		}
	    if(!sscanf(s.c_str(), "%lf", &ign) || have || (*s.begin() == '0' && s.size() > 1)) {
	    	iserror = 1;
	    	continue;
		}
	    if(s.size() > to_string(LONG_LONG_MAX).size()) {
	    	islong = 1;
	    put("数字过大。\n请输入更小的数字: ");
	    	continue;
		}
		sscanf(s.c_str(), "%lf", &ans);
	} while(iserror || islong);
    return ans;
}
LL randomSeed = -1; 
static std::mt19937 rng = std::mt19937(time(0));
void setRandomSeed(LL seed) { rng.seed(randomSeed = seed); }
void setRandomSeed() { randomSeed = -1, rng.seed(time(0)); }
LL random(LL min, LL max) { return std::uniform_int_distribution <LL> (min, max)(rng); }
string colours[] = { "", "blue", "red", "green", "Lblue", "purple", "yellow", "gray", "cyan", "brown" };
namespace PGB {
	bool eye_protection = 0;
	bool quick_output = 0;
}
void chco(string s) {
	if(PGB::eye_protection) return ;
    if(s == colours[1]) SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    else if(s == colours[2]) SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    else if(s == colours[3]) SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    else if(s == colours[4]) SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
    else if(s == colours[5]) SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED);
    else if(s == colours[6]) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    else if(s == colours[7]) SetConsoleTextAttribute(hConsole, 0x08);
    else if(s == colours[8]) SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    else if(s == colours[9]) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    else SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
    return ;
}
void chco(LL colourid) { chco(colours[colourid]); }
void pause()
{ getch(); }

#endif
