#ifndef MINE_SLIDINGPUZZLE
#define MINE_SLIDINGPUZZLE

namespace SlidingPuzzle {
	const LL dx[] = {1, -1, 0, 0};
	const LL dy[] = {0, 0, 1, -1};
	LL n, diff, ax, ay, donecnt, isdone;
	vector <vector <LL>> mp;
	string out, space;
	void init() {
		mp.clear();
		mp.resize(n + 2, vector <LL> (n + 2, 0));
		for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= n && (i != n || j != n); j ++) mp[i][j] = (i - 1) * n + j;
		ax = ay = n;
		LL logn = log10(n * n) + 1;
		out = "%" + to_string(logn) + "lld ";
		space.clear(); space.resize(logn + 1, ' ');
		isdone = n * n - 1;
	}
	LL donecount() {
		for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= n && (i != n || j != n); j ++) if(mp[i][j] != (i - 1) * n + j) return (i - 1) * n + j;
		return isdone;
	}
	void new_puzzle() {
		remake:LL t = diff, lstmov = 0;
		while(t --) {
			LL p = random(0, 3);
			LL x = ax + dx[p], y = ay + dy[p];
			if(x < 1 || x > n || y < 1 || y > n || lstmov == mp[x][y]) { t ++; continue; }
			lstmov = mp[x][y]; swap(mp[x][y], mp[ax][ay]); ax = x, ay = y;
		}
        if(donecount() == isdone) goto remake;
	}
	void printpuzzle() {
		for(LL i = 1; i <= n; i ++, printf("\n")) for(LL j = 1; j <= n; j ++) if(mp[i][j]) chco(mp[i][j] == (i - 1) * n + j ? "green" : (mp[i][j] == donecnt ? "blue" : "")), printf(out.c_str(), mp[i][j]), chco("");
		else printf(space.c_str());
	}
	void mup() { if(ax != n) swap(mp[ax][ay], mp[ax + 1][ay]), ax ++; }
	void mdown() { if(ax != 1) swap(mp[ax][ay], mp[ax - 1][ay]), ax --; }
	void mleft() { if(ay != n) swap(mp[ax][ay], mp[ax][ay + 1]), ay ++; }
	void mright() { if(ay != 1) swap(mp[ax][ay], mp[ax][ay - 1]), ay --; }
	bool move(char way) {
		switch(way) {
			case 'w': case 'i': mup(); break;
			case 's': case 'k': mdown(); break;
			case 'a': case 'j': mleft(); break;
			case 'd': case 'l': mright(); break;
			default: return false;
		}
		return true;
	}
	bool game() {
		printf("Puzzle size: "), n = get();
		while(n <= 2 && !Isout) printf("Number should br larger than 2.\nPuzzle size: "), n = get();
		if(Isout) return 0;
		re1:system("cls");
		printf("Difficulties:\n\nA:Easy\nB:Normal\nC:Hard\n\nChoose a difficulty: ");
		string dif_; getlstr(dif_);
		if(dif_ == "/hub") return false;
		if(dif_.empty()) goto re1;
		char d = dif_.front(); if(!isalpha(d)) goto re1; d = tolower(d);
		switch(d) {
			case 'a': diff = random(5 * n * n, 15 * n * n); break;
			case 'b': diff = random(20 * n * n, 40 * n * n); break;
			case 'c': diff = random(50 * n * n, 100 * n * n); break;
			default: goto re1;
		}
		init(), new_puzzle();
		LL starttime = nulltime;
		while(donecnt != isdone) {
			system("cls");
			donecnt = donecount();
			printpuzzle();
			printf("Press:\nW or I for up\nS or K for down\nA or J for left\nD or L for right\n[TAB] for menu\n");
			re:char op = getch();
			if(op == EOF) exit(-1);
			if(op == '\t') {
				system("cls");
				printf("Are you sure you are going to quit? (Y/N)");
				re2: char is = getch();
				if(is == EOF) exit(-1);
				if(is == 'y' || is == 'Y') return false;
				else if(is == 'n' || is == 'N') continue;
				else goto re2;
			}
			if(!isalpha(op)) goto re; op = tolower(op);
			if(!move(op)) goto re;
			if(starttime == nulltime) starttime = time(0);
		}
		LL endtime = time(0);
		system("cls");
		printpuzzle();
		printf("Perfect! Time: %llds\nScore: %lld\nPress enter to return to menu...", endtime - starttime, n * n * (d - 'a' + 1));
		PGB::HPB(7, n * n * (d - 'a' + 1), endtime - starttime);
		pause();
		return true;
	}
}

#endif
