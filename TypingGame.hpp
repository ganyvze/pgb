#ifndef MINE_TYPINGGAME
#define MINE_TYPINGGAME

namespace TypingGame {
	vector <string> word = {
		"auto", "and",
		"bool", "break",
		"const", "constexpr", "char", "continue", "class", "catch", "case",
		"do", "delete", "default", "double",
		"enum", "else",
		"for", "friend", "float", "false",
		"goto",
		"int", "if", "inline",
		"long", "long long", 
		"namespace", "nullptr", "new", "not",
		"operator", "or",
		"public", "private", "protected",
		"return", "register",
		"static", "short", "struct", "sizeof", "switch", "signed",
		"typedef", "try", "throw", "this", "true",
		"unsigned", "using", "union",
		"void", "virtual",
		"while",
		"xor",
		"array", "vector", "string", "set", "map", "queue", "deque", "stack", "list",
		"scanf", "printf", "unique", "cin", "cout", "sort", "stable_sort", "puts",
		"strcmp", "strcat", "strcpy", "strlen", "getline", "endl",
		"include", "define", "iostream", "algorithm"
	};
	constexpr LL linelen = 30;
	const char endsymbol = '_';
	LL n;
	char nowdown;
	string typing, typed;
	void init() {
		nowdown = 0;
		typing.clear();
		typed.clear();
	}
	void new_word() {
		LL lastword = -1;
		for(LL i = 1; i <= n; i ++) {
			re:LL x = random(0, word.size() - 1);
			if(lastword == x) goto re;
			typing += word[x] + " ";
			lastword = x;
		}
		typing.pop_back();
	}
	void printword() {
		LL st = linelen * floor(LL(typed.size()) / 3.0 / linelen) * 3;
		for(UL i = st; i < UL(st + linelen * 3) && i < UL(n); i += linelen) {
			chco("");
			for(UL j = i; j < i + linelen && j < UL(n); j ++) {
				if(j >= typed.size()) chco("");
				else if(typing[j] != typed[j]) chco("red");
				else if(typing[j] == typed[j]) chco("green");
				printf("%c", typing[j]);
			}
			chco(""), printf("\n");
			if(i == typed.size()) chco(""), printf("%c", endsymbol);
			else for(UL j = i; j < i + linelen && j < typed.size(); j ++) {
				if(typed[j] != typing[j]) chco("red");
				else chco("green");
				printf("%c", typed[j]);
				if(j + 1 == typed.size() && j + 1 < i + linelen) chco(""), printf("%c", endsymbol);
			}
			chco("blue"), printf("\n______________________________\n");
		}
		chco("");
	}
	LL speed(LL starttime, LL nowtime) { if(nowtime == starttime) return 0; return double(typed.size()) / ((nowtime - starttime) / 60.0); }
    LL wrongcnt() { LL cnt = 0; for(UL i = 0; i < typed.size(); i ++) if(typed[i] != typing[i]) cnt ++; return cnt; }
	bool game() {
		printf("Words count: "), n = get();
		if(Isout) return false;
		while(n < 0) {
			printf("Length should be larger than 0.\nTyping length: "), n = get();
			if(Isout) return false;
		}
		init();
		new_word();
		n = typing.size();
		LL starttime = nulltime;
		while(typing.size() != typed.size()) {
			system("cls");
			printword();
			LL nowtime = time(0);
			printf("Speed: %lld letters/minute\nDone: %lld%%\nWrong: %lld\nMenu: [TAB]\n", speed(starttime, nowtime), LL(100ull * typed.size() / typing.size()), wrongcnt());
			reinput:char in = getch();
			if(in == EOF) exit(-1);
			if(in == '\t') {
				system("cls");
				printf("Are you sure you are going to quit? (Y/N)");
				re2: char is = getch();
				if(is == EOF) exit(-1);
				if(is == 'y' || is == 'Y') return false;
				else if(is == 'n' || is == 'N') continue;
				else goto re2;
			}
			if(typed.size() && in == 8) typed.pop_back();
			else if(LL(typed.size()) < n && (isalpha(in) || isdigit(in) || in == ' ' || in == '_')) typed.push_back(in);
			else goto reinput;
			if(starttime == nulltime) starttime = time(0);
		}
		LL endtime = time(0);
		system("cls");
		printword();
		LL wrong = wrongcnt();
		printf("\nScore: %lld Speed: %lld letters/minute Time: %llds Wrong: %lld\n", speed(starttime, endtime) * LL(1.0 * (LL(typed.size()) - wrong) / LL(typed.size())), speed(starttime, endtime), endtime - starttime, wrong);
		if(typing.size() != typed.size()) printf("Press enter to return to menu...");
		else printf("Perfect! You finished all of the words!\nPress enter to return to menu...");
		pause();
		PGB::HPB(6, 1.0 * speed(starttime, endtime) * (LL(typed.size()) - wrong) / LL(typed.size()), endtime - starttime);
		return true;
	}
}

#endif
