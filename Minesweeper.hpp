#ifndef MINE_MINESWEEPER
#define MINE_MINESWEEPER

namespace Minesweeper {
	constexpr LL dx[] = {1, -1, 1, -1, 1, -1, 0, 0};
	constexpr LL dy[] = {1, 1, -1, -1, 0, 0, 1, -1};
	struct xandy { LL x, y; char sign; };
	xandy getxy(LL n, bool& again) {
		chco("Lblue");
		printf("Open: x.y\nFlag: x/y\nClear flag: x/y\n");
		chco("gray");
		printf("Menu: /hub\n");
		chco("purple");
		printf("_______________\n");
		chco("");
		printf("x?y = ");
		string input;
		LL x, y;
		char sign = 0;
		do {
			if(sign && x >= 1 && x <= n && y >= 1 && y <= n) break;
			if(input == "/hub") {
				again = true;
				return {0, 0, 0};
			}
			if(!input.empty()) printf("Invalid number\nx?y = ");
			do getlstr(input); while(input.empty());
			if(sscanf(input.c_str(), "%lld.%lld", &x, &y) == 2) sign = '.';
			else if(sscanf(input.c_str(), "%lld/%lld", &x, &y) == 2) sign = '/';
			else continue;
		} while(x < 1 || x > n || y < 1 || y > n);
		return {y, x, sign};
	}
	bool isnear(LL ax, LL ay, LL bx, LL by) {
		if(ax == bx && ay == by) return true;
		for(LL i = 0; i < 8; i ++) if(ax + dx[i] == bx && ay + dy[i] == by) return true;
		return false;
	}
	class {
	private:
		vector <vector <char>> oboa, boa;
		LL n, boommax, starttime, endtime, signcnt;
		bool gameover, again;
		string out, space;
		void init() {
			gameover = 0, again = 0, signcnt = 0;
			oboa.clear(), boa.clear();
			boommax = n < 10 ? floor(n * 1.2) : ceil(n * n * 0.18);
			LL nlog = log10(n) + 1;
			out = "%" + to_string(nlog) + "lld";
			space = "";
			while(nlog --) space += ' ';
			oboa.resize(n + 2, vector <char> (n + 2, '-')), boa.resize(n + 2, vector <char> (n + 2, '0'));
		}
		void printboard() {
			printf((space + " ").c_str());
			chco("green");
			for(LL i = 1; i <= n; i ++) printf((out + " ").c_str(), i);
			printf("x");
			chco("");
			for(LL i = 1; i <= n; i ++) {
				chco("green");
				printf(("\n" + out + space).c_str(), i);
				chco("");
				for(LL j = 1; j <= n; j ++) if(oboa[i][j] == '+') chco("red"), printf(("+" + space).c_str()), chco("");
				else if(oboa[i][j] == '-') chco("blue"), printf(("-" + space).c_str()), chco("");
				else printf(("%c" + space).c_str(), oboa[i][j]);
			}
			chco("green");
			printf("\ny\n");
			chco("purple");
			for(LL i = 1; i <= n * 3 + 5; i ++) printf("_");
			chco("");
			printf("\n");
		}
		void printface(LL winlost) {
			LL nlog = log10(n) + 1;
			chco("yellow");
			for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= (nlog >> 1) + 1; j ++) printf(" ");
			printf(winlost == 1 ? ":D\n" : (winlost == -1 ? "X(\n" : ":|\n"));
			chco("");
		}
		void openbox(const LL sx, const LL sy) {
			queue <pair <LL, LL>> qu;
			qu.push({sx, sy});
			while(qu.size()) {
				pair <LL, LL> nd = qu.front(); qu.pop();
				LL x = nd.first, y = nd.second;
				if(x < 1 || x > n || y < 1 || y > n || !(oboa[x][y] == '-' || isdigit(oboa[x][y]))) continue;
				if(boa[x][y] == '+') {
					boa[x][y] = 'X';
					gameover = true;
					return ;
				}
				if(boa[x][y] == ' ') {
					oboa[x][y] = boa[x][y];
					for(char i = -1; i <= 1; i ++) for(char j = -1; j <= 1; j ++) if((i != 0 || j != 0) && oboa[x + i][y + j] == '-') qu.push({x + i, y + j});
				} else if(isdigit(oboa[x][y])) {
					LL cnt = 0;
					for(char i = -1; i <= 1; i ++) for(char j = -1; j <= 1; j ++) if(oboa[x + i][y + j] == '+') cnt ++;
					if(oboa[x][y] - '0' == cnt) for(char i = -1; i <= 1; i ++) for(char j = -1; j <= 1; j ++) if(oboa[x + i][y + j] == '-') qu.push({x + i, y + j});
				} else oboa[x][y] = boa[x][y];
			}
		}
		void signbox(const LL& x, const LL& y) {
			if(oboa[x][y] == '+') oboa[x][y] = '-', signcnt --;
			else if(oboa[x][y] == '-') oboa[x][y] = '+', signcnt ++;
		}
		void new_board(LL x, LL y) {
			LL cnt = 0;
			while(cnt < boommax) {
				LL xx = random(1, n), xy = random(1, n);
				if(boa[xx][xy] != '+' && !isnear(x, y, xx, xy)) boa[xx][xy] = '+', cnt ++;
			}
			for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= n; j ++) if(boa[i][j] == '0') for(char k = -1; k <= 1; k ++) for(char l = -1; l <= 1; l ++) if(k != 0 || l != 0) boa[i][j] += boa[i + k][j + l] == '+';
			for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= n; j ++) if(boa[i][j] == '0') boa[i][j] = ' ';
		}
		bool is_end() {
			if(gameover) return true;
			LL cnt = 0;
			bool end = true;
			for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= n; j ++) if((oboa[i][j] == '+' || boa[i][j] == '+') && oboa[i][j] != boa[i][j]) {
				end = false;
				break;
			}
			if(end) return true;
			for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= n; j ++) cnt += isdigit(oboa[i][j]) || oboa[i][j] == ' ';
			if(cnt + boommax != n * n) return false;
			return true;
		}
	public:
		bool game() {
			printf("Board size: ");
			n = get();
			while(n <= 3 && !Isout) printf("Number should larger than 3.\nBoard size: "), n = get();
			if(Isout) return false;
			init();
			system("cls");
			chco("blue");
			printf("Bombs left: %lld\n", boommax);
			chco("");
			printface(0);
			printboard();
			auto start = getxy(n, again);
			if(again) return false;
			new_board(start.x, start.y);
			openbox(start.x, start.y);
			starttime = nulltime;
			while(!is_end()) {
				system("cls");
				chco("blue");
				printf("Boom left: %lld\n", boommax - signcnt);
				chco("");
				printface(0);
				printboard();
				auto nd = getxy(n, again);
				if(again) return false;
				if(nd.sign == '.' || isdigit(oboa[nd.x][nd.y])) openbox(nd.x, nd.y);
				else signbox(nd.x, nd.y);
				if(starttime == nulltime) starttime = time(0);
			}
			system("cls");
			printface(gameover ? -1 : 1);
			printf((space + " ").c_str());
			chco("green");
			for(LL i = 1; i <= n; i ++) printf((out + " ").c_str(), i);
			printf("x");
			chco("");
			for(LL i = 1; i <= n; i ++) {
				chco("green");
				printf(("\n" + out + space).c_str(), i);
				chco("");
				for(LL j = 1; j <= n; j ++) if(boa[i][j] == '+') chco("red"), printf(("+" + space).c_str()), chco("");
				else if(boa[i][j] == '-') chco("blue"), printf(("-" + space).c_str()), chco("");
				else if(boa[i][j] == 'X') chco("red"), printf(("X" + space).c_str()), chco("");
				else printf(("%c" + space).c_str(), boa[i][j]);
			}
			chco("green");
			printf("\ny\n");
			chco("purple");
			for(LL i = 1; i <= n * 3 + 5; i ++) printf("_");
			chco("");
			printf("\n");
			endtime = time(0);
			if(gameover) chco("red"), printf("Game over.\n");
			else chco("green"), printf("You win!\n");
			chco("");
			LL opencnt = 0;
			if(gameover) for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= n; j ++) opencnt += ((oboa[i][j] == '+' && boa[i][j] == '+') || isdigit(oboa[i][j]));
			printf("Time: %llds\nScore: %lld\n\nPress enter to return to menu...", endtime - starttime, gameover ? opencnt : (n * n));
			pause();
			PGB::HPB(1, gameover ? opencnt : (n * n), endtime - starttime);
			return !gameover;
		}
	} Classic;
	class {
	private:
		vector <vector <char>> oboa, boa;
		LL n, boommax, starttime, endtime, tgx, tgy, signcnt;
		bool gameover, again;
		string out, space;
		struct xandy { LL x, y; char sign; };
		void init() {
			gameover = 0, again = 0, signcnt = 0;
			oboa.clear(), boa.clear();
			boommax = n * n * (n >= 10 ? 0.3 : 0.2);
			LL nlog = log10(n) + 1;
			out = "%" + to_string(nlog) + "lld";
			space = "";
			while(nlog --) space += ' ';
			oboa.resize(n + 2, vector <char> (n + 2, '-')), boa.resize(n + 2, vector <char> (n + 2, '0'));
		}
		void new_board(LL x, LL y) {
			LL cnt = 0;
			while(isnear(tgx = random(1, n), tgy = random(1, n), x, y));
			boa[tgx][tgy] = 'D';
			while(cnt < boommax) {
				LL xx = random(1, n), xy = random(1, n);
				if(boa[xx][xy] != '+' && boa[xx][xy] != 'D' && !isnear(x, y, xx, xy)) boa[xx][xy] = '+', cnt ++;
			}
			for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= n; j ++) if(boa[i][j] == '0') for(char k = -1; k <= 1; k ++) for(char l = -1; l <= 1; l ++) if(k != 0 || l != 0) boa[i][j] += boa[i + k][j + l] == '+';
			for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= n; j ++) if(boa[i][j] == '0') boa[i][j] = ' ';
		}
		void printboard() {
			printf((space + " ").c_str());
			chco("green");
			for(LL i = 1; i <= n; i ++) printf((out + " ").c_str(), i);
			printf("x");
			chco("");
			for(LL i = 1; i <= n; i ++) {
				chco("green");
				printf(("\n" + out + space).c_str(), i);
				chco("");
				for(LL j = 1; j <= n; j ++) if(oboa[i][j] == '+') chco("red"), printf(("+" + space).c_str()), chco("");
				else if(oboa[i][j] == '-') chco("blue"), printf(("-" + space).c_str()), chco("");
				else printf(("%c" + space).c_str(), oboa[i][j]);
			}
			chco("green");
			printf("\ny\n");
			chco("purple");
			for(LL i = 1; i <= n * 3 + 5; i ++) printf("_");
			chco("");
			printf("\n");
		}
		void printface(LL winlost) {
			LL nlog = log10(n) + 1;
			for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= (nlog >> 1) + 1; j ++) printf(" ");
			if(winlost == 1) chco("green"), printf(":D\n");
			else if(winlost == -1) chco("red"), printf("X(\n");
			else printf(":|\n");
		}
		void openbox(const LL x, const LL y) {
			if(x < 1 || x > n || y < 1 || y > n || !(oboa[x][y] == '-' || isdigit(oboa[x][y]))) return ;
			if(boa[x][y] == '+') {
				boa[x][y] = 'X';
				gameover = true;
				return ;
			}
			if(boa[x][y] == ' ') {
				oboa[x][y] = boa[x][y];
				for(char i = -1; i <= 1; i ++) for(char j = -1; j <= 1; j ++) {
					if((i != 0 || j != 0) && oboa[x + i][y + j] == '-') openbox(x + i, y + j);
					if(gameover) return ;
				}
			} else if(isdigit(oboa[x][y])) {
				LL cnt = 0;
				for(char i = -1; i <= 1; i ++) for(char j = -1; j <= 1; j ++) if(oboa[x + i][y + j] == '+') cnt ++;
				if(oboa[x][y] - '0' == cnt) for(char i = -1; i <= 1; i ++) for(char j = -1; j <= 1; j ++) {
					if(oboa[x + i][y + j] == '-') openbox(x + i, y + j);
					if(gameover) return ;
				}
			} else oboa[x][y] = boa[x][y];
		}
		void signbox(const LL& x, const LL& y) {
			if(oboa[x][y] == '+') oboa[x][y] = '-', signcnt --;
			else if(oboa[x][y] == '-') oboa[x][y] = '+', signcnt ++;
		}
	public:
		bool game() {
			printf("Board size: ");
			n = get();
			while(n <= 5 && !Isout) printf("Number should larger than 5.\nBoard size: "), n = get();
			if(Isout) return false;
			init();
			system("cls");
			chco("blue");
			printf("Boom left: %lld\n", boommax);
			chco("");
			printface(0);
			printboard();
			auto start = getxy(n, again);
			if(again) return false;
			new_board(start.x, start.y);
			openbox(start.x, start.y);
			starttime = nulltime;
			while(oboa[tgx][tgy] != 'D' && !gameover) {
				system("cls");
				chco("blue");
				printf("Boom left: %lld\n", boommax - signcnt);
				chco("");
				printface(0);
				printboard();
				auto nd = getxy(n, again);
				if(again) return false;
				if(nd.sign == '.' || isdigit(oboa[nd.x][nd.y])) openbox(nd.x, nd.y);
				else signbox(nd.x, nd.y);
				if(starttime == nulltime) starttime = time(0);
			}
			system("cls");
			printface(gameover ? -1 : 1);
			printf((space + " ").c_str());
			chco("green");
			for(LL i = 1; i <= n; i ++) printf((out + " ").c_str(), i);
			printf("x");
			chco("");
			for(LL i = 1; i <= n; i ++) {
				chco("green");
				printf(("\n" + out + space).c_str(), i);
				chco("");
				for(LL j = 1; j <= n; j ++) if(boa[i][j] == '+') chco("red"), printf(("+" + space).c_str()), chco("");
				else if(boa[i][j] == '-') chco("blue"), printf(("-" + space).c_str()), chco("");
				else if(boa[i][j] == 'X') chco("red"), printf(("X" + space).c_str()), chco("");
				else printf(("%c" + space).c_str(), boa[i][j]);
			}
			chco("green");
			printf("\ny\n");
			chco("purple");
			for(LL i = 1; i <= n * 3 + 5; i ++) printf("_");
			chco("");
			printf("\n");
			endtime = time(0);
			if(gameover) chco("red"), printf("Game over.\n");
			else chco("green"), printf("You win!\n");
			chco("");
			LL opencnt = 0;
			if(gameover) for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= n; j ++) opencnt += ((oboa[i][j] == '+' && boa[i][j] == '+') || isdigit(oboa[i][j]));
			printf("Time: %llds\nScore: %lld\n\nPress enter to return to menu...", endtime - starttime, gameover ? opencnt : (n * n));
			pause();
			PGB::HPB(2, gameover ? opencnt : (n * n), endtime - starttime);
			return !gameover;
		}
	} Diamond_finder;
}

#endif
