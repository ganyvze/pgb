#ifndef MINE_PLUSGAME
#define MINE_PLUSGAME

namespace PlussingGame {
	constexpr LL dx[] = {1, -1, 0, 0};
	constexpr LL dy[] = {0, 0, 1, -1};
	LL n, target, sum, X, Y;
	vector <vector <LL>> mp;
	vector <vector <bool>> vis;
	stack <array <LL, 2>> moved;
	void init() {
		while(moved.size()) moved.pop();
		mp.clear(); mp.resize(n + 2, vector <LL> (n + 2, 0));
		vis.clear(); vis.resize(n + 2, vector <bool> (n + 2, 0));
		target = 0, sum = 0, X = 1, Y = 1;
		moved.push({1, 1}); vis[1][1] = 1;
	}
	void new_board() {
		for(vector <LL>& i : mp) for(LL& j : i) j = random(1, 9);
		mp[1][1] = mp[n][n] = 0;
		LL x = 1, y = 1, sum = 0;
		while(x != n || y != n) {
			if(random(0, 1) && y + 1 <= n) sum += mp[x][++ y];
			else if(x + 1 <= n) sum += mp[++ x][y];
		}
		target = sum;
	}
	void printboard() {
		for(LL i = 1; i <= n; i ++, printf("\n")) for(LL j = 1; j <= n; j ++)
		if(i == X && j == Y && i != 1 && j != 1 && i != n && j != n) chco("red"), printf("[%lld]", mp[i][j]);
		else if(i == X && j == Y && i == 1 && j == 1) chco("red"), printf("[S]");
		else if(i == X && j == Y && i == n && j == n) chco("red"), printf("[E]");
		else if(i == 1 && j == 1) chco("Lblue"), printf("(S)");
		else if(i == n && j == n) chco("green"), printf(" E ");
		else if(vis[i][j]) chco("blue"), printf("(%lld)", mp[i][j]);
		else chco(""), printf(" %lld ", mp[i][j]);
		chco("");
		printf("\n按键：\nW 或 I：上\nS 或 K：下\nA 或 J：左\nD 或 L：右\n[TAB]：菜单\n");
	}
	bool move(char way) {
		LL x = X, y = Y;
		switch(way) {
			case 'w': case 'i': x --; break;
			case 's': case 'k': x ++; break;
			case 'a': case 'j': y --; break;
			case 'd': case 'l': y ++; break;
			default: return 0;
		}
		if(x < 1 || x > n || y < 1 || y > n) return 1;
		if(vis[x][y] && moved.top()[0] == x && moved.top()[1] == y)
		sum -= mp[X][Y], vis[X][Y] = 0, moved.pop();
		else if(vis[x][y]) return 1;
		else sum += mp[x][y], vis[x][y] = 1;
		if(vis[X][Y]) moved.push({X, Y});
		X = x, Y = y;
		return 1;
	}
	bool game() {
		printf("棋盘大小: "), n = get();
		while(n <= 2 && !Isout) printf("大小必须大于 2。\n棋盘大小: "), n = get();
		if(Isout) return 0;
		init();
		new_board();
		LL starttime = nulltime;
		while(sum != target || (X != n || Y != n)) {
			refresh_screen();
			printf("目标: %lld\n当前总和: %lld\n\n", target, sum);
			printboard();
			re:char c = getch();
			if(c == EOF) exit(-1);
			if(c == '\t') {
				refresh_screen();
				printf("确定要退出吗？(Y/N)");
				re2: char is = getch();
				if(is == EOF) exit(-1);
				if(is == 'y' || is == 'Y') return false;
				else if(is == 'n' || is == 'N') continue;
				else goto re2;
			} else if(!isalpha(c)) goto re;
			c = tolower(c);
			if(!move(c)) goto re;
			if(starttime == nulltime) starttime = time(0);
		}
		LL endtime = time(0);
		refresh_screen();
		printf("目标: %lld\n当前总和: %lld\n\n", target, sum);
		for(LL i = 1; i <= n; i ++, printf("\n")) for(LL j = 1; j <= n; j ++)
		if(i == X && j == Y && i != 1 && j != 1 && i != n && j != n) chco("red"), printf("[%lld]", mp[i][j]);
		else if(i == X && j == Y && i == 1 && j == 1) chco("red"), printf("[S]");
		else if(i == X && j == Y && i == n && j == n) chco("red"), printf("[E]");
		else if(i == 1 && j == 1) chco("Lblue"), printf(" S ");
		else if(i == n && j == n) chco("green"), printf(" E ");
		else if(vis[i][j]) chco("blue"), printf("(%lld)", mp[i][j]);
		else chco(""), printf(" %lld ", mp[i][j]);
		chco("green"), printf("\n你赢了！\n"), chco("");
		printf("分数: %lld 时间: %llds\n按回车返回主菜单...", n * 20, endtime - starttime);
		PGB::HPB(8, n * 20, endtime - starttime);
		pause(); return true;
	}
}

#endif
