#ifndef MINE_TIC_TAC_TOE
#define MINE_TIC_TAC_TOE

namespace Tictactoe {
	constexpr LL N = 5;
	char mp[N][N], player, cpr, dif;
	bool again;
	LL aircnt;
	struct xandy { LL x, y; };
	void init() {
		for(LL i = 1; i <= 3; i ++) for(LL j = 1; j <= 3; j ++) mp[i][j] = '-';
		aircnt = 9, again = 0;
	}
	char checkwin() {
		for(LL i = 1; i <= 3; i ++) if(mp[i][1] == 'X' && mp[i][2] == 'X' && mp[i][3] == 'X') return 'X';
		else if(mp[i][1] == 'O' && mp[i][2] == 'O' && mp[i][3] == 'O') return 'O';
		for(LL i = 1; i <= 3; i ++) if(mp[1][i] == 'X' && mp[2][i] == 'X' && mp[3][i] == 'X') return 'X';
		else if(mp[1][i] == 'O' && mp[2][i] == 'O' && mp[3][i] == 'O') return 'O';
		if(mp[2][2] == '-') return 0;
		if(mp[1][1] == 'X' && mp[2][2] == 'X' && mp[3][3] == 'X') return 'X';
		if(mp[1][1] == 'O' && mp[2][2] == 'O' && mp[3][3] == 'O') return 'O';
		if(mp[1][3] == 'X' && mp[2][2] == 'X' && mp[3][1] == 'X') return 'X';
		if(mp[1][3] == 'O' && mp[2][2] == 'O' && mp[3][1] == 'O') return 'O';
		return 0;
	}
	void printboard() {
		printf("  1 2 3 x\n");
		for(LL i = 1; i <= 3; i ++) {
			printf("%lld ", i);
			for(LL j = 1; j <= 3; j ++) chco(mp[i][j] == player ? "blue" : ""), printf("%c ", mp[i][j]);
			chco("");
			printf("\n");
		}
		printf("y\n");
	}
	void printendboard() {
		LL w = 0;
		for(LL i = 1; i <= 3; i ++) if((mp[i][1] == 'X' && mp[i][2] == 'X' && mp[i][3] == 'X') || (mp[i][1] == 'O' && mp[i][2] == 'O' && mp[i][3] == 'O')) { w = i; goto done; }
		for(LL i = 1; i <= 3; i ++) if((mp[1][i] == 'X' && mp[2][i] == 'X' && mp[3][i] == 'X') || (mp[1][i] == 'O' && mp[2][i] == 'O' && mp[3][i] == 'O')) { w = 3 + i; goto done; }
		if((mp[1][1] == 'X' && mp[2][2] == 'X' && mp[3][3] == 'X') || (mp[1][1] == 'O' && mp[2][2] == 'O' && mp[3][3] == 'O')) { w = 7; goto done; }
		if((mp[1][3] == 'X' && mp[2][2] == 'X' && mp[3][1] == 'X') || (mp[1][3] == 'O' && mp[2][2] == 'O' && mp[3][1] == 'O')) { w = 8; goto done; }
		done:printf("  1 2 3 x\n");
		if(w <= 6) for(LL i = 1; i <= 3; i ++) {
			printf("%lld ", i);
			for(LL j = 1; j <= 3; j ++) chco(((w <= 3 ? i : j) == (w <= 3 ? w : w - 3)) ? "red" : (mp[i][j] == player ? "blue" : "")), printf("%c ", mp[i][j]);
			chco("");
			printf("\n");
		} else if(w == 7 || w == 8) for(LL i = 1; i <= 3; i ++) {
			printf("%lld ", i);
			for(LL j = 1; j <= 3; j ++) chco((w == 7 ? i == j : i + j == 4) ? "red" : (mp[i][j] == player ? "blue" : "")), printf("%c ", mp[i][j]);
			chco("");
			printf("\n");
		}
		printf("y\n");
	}
	xandy getxy() {
		chco("gray");
		printf("Menu: /hub\n");
		chco("purple");
		printf("_______________\n");
		chco("");
		printf("xy = ");
		string input;
		LL x, y;
		while(true) {
			do getlstr(input); while(input.empty());
			if(input == "/hub") {
				again = true;
				return {0, 0};
			}
			if(sscanf(input.c_str(), "%1lld%1lld", &x, &y) != 2 || x < 1 || x > 3 || y < 1 || y > 3) printf("error\nxy = "), x = y = 0;
			else if(mp[y][x] != '-') printf("This place is used.\nxy = ");
			else break;
		}
		return {y, x};
	}
	void use(LL x, LL y, char sign)
	{ mp[x][y] = sign, aircnt --; }
	xandy randomai() {
	    LL x, y;
	    do x = random(1, 3), y = random(1, 3); while(mp[x][y] != '-');
	    return {x, y};
	}
	xandy easyAI() { return randomai(); }
	xandy normalAI() {
	    for(LL i = 1; i <= 3; i ++) if(mp[i][1] == player && mp[i][2] == player && mp[i][3] == '-') return {i, 3};
	    else if(mp[i][1] == player && mp[i][3] == player && mp[i][2] == '-') return {i, 2};
	    else if(mp[i][2] == player && mp[i][3] == player && mp[i][1] == '-') return {i, 1};
	    for(LL i = 1; i <= 3; i ++) if(mp[1][i] == player && mp[2][i] == player && mp[3][i] == '-') return {3, i};
		else if(mp[1][i] == player && mp[3][i] == player && mp[2][i] == '-') return {2, i};
	    else if(mp[2][i] == player && mp[3][i] == player && mp[1][i] == '-') return {1, i};
	    if(mp[1][1] == player && mp[2][2] == player && mp[3][3] == '-') return {3, 3};
	    if(mp[1][1] == player && mp[3][3] == player && mp[2][2] == '-') return {2, 2};
	    if(mp[2][2] == player && mp[3][3] == player && mp[1][1] == '-') return {1, 1};
	    if(mp[1][3] == player && mp[2][2] == player && mp[3][1] == '-') return {3, 1};
	    if(mp[1][3] == player && mp[3][1] == player && mp[2][2] == '-') return {2, 2};
	    if(mp[2][2] == player && mp[3][1] == player && mp[1][3] == '-') return {1, 3};
	    return randomai();
	}
	xandy hardAI() {
		if(aircnt == 8 && mp[2][2] == '-') return {2, 2};
		for(LL i = 1; i <= 3; i ++) if(mp[1][i] == cpr && mp[2][i] == cpr && mp[3][i] == '-') return {3, i};
		else if(mp[1][i] == cpr && mp[2][i] == '-' && mp[3][i] == cpr) return {2, i};
		else if(mp[1][i] == '-' && mp[2][i] == cpr && mp[3][i] == cpr) return {1, i};
		else if(mp[i][1] == cpr && mp[i][2] == cpr && mp[i][3] == '-') return {i, 3};
		else if(mp[i][1] == cpr && mp[i][2] == '-' && mp[i][3] == cpr) return {i, 2};
		else if(mp[i][1] == '-' && mp[i][2] == cpr && mp[i][3] == cpr) return {i, 1};
		if(mp[2][2] != player) {
			if(mp[1][1] == cpr && mp[2][2] == cpr && mp[3][3] == '-') return {3, 3};
			else if(mp[1][1] == cpr && mp[2][2] == '-' && mp[3][3] == cpr) return {2, 2};
			else if(mp[1][1] == '-' && mp[2][2] == cpr && mp[3][3] == cpr) return {1, 1};
			else if(mp[1][3] == cpr && mp[2][2] == cpr && mp[3][1] == '-') return {3, 1};
			else if(mp[1][3] == cpr && mp[2][2] == '-' && mp[3][1] == cpr) return {2, 2};
			else if(mp[1][3] == '-' && mp[2][2] == cpr && mp[3][1] == cpr) return {1, 3};
		}
	    for(LL i = 1; i <= 3; i ++) if(mp[i][1] == player && mp[i][2] == player && mp[i][3] == '-') return {i, 3};
	    else if(mp[i][1] == player && mp[i][3] == player && mp[i][2] == '-') return {i, 2};
	    else if(mp[i][2] == player && mp[i][3] == player && mp[i][1] == '-') return {i, 1};
	    for(LL i = 1; i <= 3; i ++) if(mp[1][i] == player && mp[2][i] == player && mp[3][i] == '-') return {3, i};
		else if(mp[1][i] == player && mp[3][i] == player && mp[2][i] == '-') return {2, i};
	    else if(mp[2][i] == player && mp[3][i] == player && mp[1][i] == '-') return {1, i};
	    if(mp[1][1] == player && mp[2][2] == player && mp[3][3] == '-') return {3, 3};
	    if(mp[1][1] == player && mp[3][3] == player && mp[2][2] == '-') return {2, 2};
	    if(mp[2][2] == player && mp[3][3] == player && mp[1][1] == '-') return {1, 1};
	    if(mp[1][3] == player && mp[2][2] == player && mp[3][1] == '-') return {3, 1};
	    if(mp[1][3] == player && mp[3][1] == player && mp[2][2] == '-') return {2, 2};
	    if(mp[2][2] == player && mp[3][1] == player && mp[1][3] == '-') return {1, 3};
	    if(cpr == 'X') {
	        if(aircnt == 7 && mp[2][2] == '-') {
	        	if(mp[1][3] == player) {
	        		LL x = 1 + (random(0, 1) << 1);
					return {x, x};
				}
				if(mp[1][1] == player || mp[1][2] == player || mp[2][1] == player) if(mp[3][3] == '-') return {3, 3};
		        if(mp[3][3] == player || mp[2][3] == player || mp[3][2] == player) if(mp[1][1] == '-') return {1, 1};
		    } else if(aircnt == 7 && mp[2][2] == player) {
				if(mp[1][1] == cpr) return {3, 3};
				if(mp[1][3] == cpr) return {3, 1};
				if(mp[3][1] == cpr) return {1, 3};
				if(mp[3][3] == cpr) return {1, 1};
			} else if(aircnt == 5 && mp[2][2] == '-') {
		    	if(mp[1][1] == player || mp[3][3] == player) return {1, 3};
		    	else if(mp[1][3] == player && mp[1][1] == '-') return {1, 1};
		    	else if(mp[1][3] == player && mp[3][3] == '-') return {3, 3};
				else return {2, 2};
			}
	    } else {
	    	if(aircnt == 6 && mp[1][1] == player && mp[3][3] == player && mp[2][2] == cpr) {
				xandy side[] = {{1, 2}, {2, 1}, {2, 3}, {3, 2}};
				return side[random(0, 3)];
			}
	    	if(aircnt == 8 && mp[2][2] == player) return {1 + (random(0, 1) << 1), 1 + (random(0, 1) << 1)};
	    	if(aircnt == 6) {
	    		if(mp[1][3] == player && mp[2][1] == player) return {1, random(1, 2)};
	    		if(mp[3][3] == player && mp[2][1] == player) return {3, random(1, 2)};
	    		if(mp[3][1] == player && mp[1][2] == player) return {random(1, 2), 1};
	    		if(mp[3][3] == player && mp[1][2] == player) return {random(1, 2), 3};
	    		if(mp[1][1] == player && mp[2][3] == player) return {1, random(2, 3)};
	    		if(mp[3][1] == player && mp[2][3] == player) return {3, random(2, 3)};
	    		if(mp[1][1] == player && mp[3][2] == player) return {random(2, 3), 1};
	    		if(mp[1][3] == player && mp[3][2] == player) return {random(2, 3), 3};
	    		if(mp[2][2] == player) {
			    	if((mp[1][1] == player && mp[3][3] == cpr) || (mp[1][1] == cpr && mp[3][3] == player)) {
			    		if(random(0, 1)) return {1, 3};
			    		else return {3, 1};
					}
					if((mp[1][3] == player && mp[3][1] == cpr) || (mp[1][3] == cpr && mp[3][1] == player)) {
						if(random(0, 1)) return {1, 1};
						else return {3, 3};
					}
				}
			}
		}
	    if(mp[2][2] == '-') return {2, 2};
	    return randomai();
	}
	LL calcscore(char w) { return ((cpr == 'X') + 1) * (!w ? 50 : (w == player ? 100 : 0)) * (dif - 'a' + 1); }
	bool game() {
		init();
		string dif_, team;
		re1:printf("Difficulties:\n\nA:Easy\nB:Normal\nC:Hard\n\nChoose a difficulty: ");
		getlstr(dif_);
		if(dif_ == "/hub") return false;
		if(dif_.empty()) goto re1;
		dif = dif_.front();
		if(tolower(dif) != 'a' && tolower(dif) != 'b' && tolower(dif) != 'c') { system("cls"); goto re1; }
		dif = tolower(dif);
		re2:system("cls");
		printf("Choose a character(X/O): ");
		getlstr(team);
		if(team == "/hub") return false;
		if(team.empty()) goto re2;
		if(tolower(team.front()) == 'x') player = 'X', cpr = 'O';
		else if(tolower(team.front()) == 'o') player = 'O', cpr = 'X';
		else goto re2;
		if(cpr == 'X') {
			if(dif == 'c') use(3, 1, cpr);
			else use(2, 2, cpr);
		}
		LL starttime = nulltime;
		while(!checkwin() && aircnt) {
			system("cls");
			printboard();
			auto nd = getxy();
			if(again) return false;
			use(nd.x, nd.y, player);
			if(checkwin() || !aircnt) break;
			auto c = (dif == 'a' ? easyAI() : (dif == 'b' ? normalAI() : hardAI()));
			use(c.x, c.y, cpr);
			if(starttime == nulltime) starttime = time(0);
		}
		LL endtime = time(0);
		system("cls");
		printendboard();
		char w = checkwin();
		if(!w) printf("No winner.\n");
		else if(w == player) chco("green"), printf("You win!\n");
		else chco("red"), printf("Game over.\n");
		chco("");
		printf("Score: %lld\n\nPress enter to return to menu...", calcscore(w));
		pause();
		PGB::HPB(3, calcscore(w), endtime - starttime);
		return w == player;
	}
}

#endif
