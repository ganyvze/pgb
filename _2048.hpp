#ifndef MINE_2048
#define MINE_2048

namespace _2048 {
	LL mp[6][6], score;
	void init() {
		score = 0;
		memset(mp, 0, sizeof mp);
		LL ax, ay, x, y;
		mp[ax = random(1, 4)][ay = random(1, 4)] = random(1, 2) << 1;
		do x = random(1, 4), y = random(1, 4); while(x == ax && y == ay);
		mp[x][y] = random(1, 2) << 1;
	}
	void printnumber(LL number) {
		LL length = to_string(number).size();
		chco(LL(log2(number)) % 10);
		printf("%lld", number);
		for(LL i = 1; i <= 5 - length; i ++) printf(" ");
	}
	void printMP() {
		printf("Score: %lld\n\n", score);
		for(LL i = 1; i <= 4; i ++, printf("\n")) for(LL j = 1; j <= 4; j ++) if(mp[i][j]) printnumber(mp[i][j]);
		else chco(0), printf("-    ");
		chco("");
		printf("\nPress:\nW or I for up\nS or K for down\nA or J for left\nD or L for right\n[TAB] for menu\n");
	}
	bool win() {
		for(LL i = 1; i <= 4; i ++) for(LL j = 1; j <= 4; j ++) if(mp[i][j] == 2048) return true;
		return false;
	}
	bool canMove() {
        for(LL i = 1; i <= 4; i ++) for(LL j = 1; j <= 4; j ++) if(!mp[i][j]) return true;
        for(LL i = 1; i <= 4; i ++) for(LL j = 1; j <= 3; j ++) {
            if(mp[i][j] == mp[i][j + 1]) return true;
            if(mp[j][i] == mp[j + 1][i]) return true;
        }
        return false;
    }
    void addRandomTile() {
        vector <pair <LL, LL>> empty;
        for(LL i = 1; i <= 4; i ++) for(LL j = 1; j <= 4; j ++) if(!mp[i][j]) empty.push_back({i, j});
        if(empty.empty()) return;
        auto p = empty[random(0, empty.size() - 1)];
        LL x = p.first, y = p.second;
        mp[x][y] = (random(1, 10) == 1) ? 4 : 2;
    }
	void Left() {
	    bool changed = false;
	    for(LL i = 1; i <= 4; i ++) {
	        vector <LL> row;
	        for(LL j = 1; j <= 4; j ++) if(mp[i][j] != 0) row.push_back(mp[i][j]);
	        vector <bool> merged(row.size(), false);
	        vector <LL> newRow;
 	        for(UL k = 0; k < row.size(); k ++) if(k < row.size() - 1 && !merged[k] && row[k] == row[k + 1])
			 	newRow.push_back(row[k] << 1), merged[k] = true, merged[k + 1] = true, changed = true, score += (row[k] << 1);
	        else if(!merged[k]) newRow.push_back(row[k]);
	        while(newRow.size() < 4) newRow.push_back(0);
	        for(LL j = 1; j <= 4; j ++) {
	            if(mp[i][j] != newRow[j - 1]) changed = true;
	            mp[i][j] = newRow[j - 1];
	        }
	    }
	    if(changed) addRandomTile();
	}
	void Right() {
	    bool changed = false;
	    for(LL i = 1; i <= 4; i ++) {
	        vector <LL> row;
	        for(LL j = 4; j >= 1; j --) if(mp[i][j] != 0) row.push_back(mp[i][j]);
	        vector <bool> merged(row.size(), false);
	        vector <LL> newRow;
	        for(UL k = 0; k < row.size(); k ++) if(k < row.size() - 1 && !merged[k] && row[k] == row[k + 1])
				newRow.push_back(row[k] << 1), merged[k] = true, merged[k + 1] = true, changed = true, score += (row[k] << 1);
	        else if(!merged[k]) newRow.push_back(row[k]);
	        while(newRow.size() < 4) newRow.push_back(0);
	        for(LL j = 4; j >= 1; j --) {
	            if(mp[i][j] != newRow[4 - j]) changed = true;
	            mp[i][j] = newRow[4 - j];
	        }
	    }
	    if(changed) addRandomTile();
	}
	void Up() {
	    bool changed = false;
	    for(LL j = 1; j <= 4; j ++) {
	        vector <LL> col;
	        for(LL i = 1; i <= 4; i ++) if(mp[i][j] != 0) col.push_back(mp[i][j]);
	        vector <bool> merged(col.size(), false);
	        vector <LL> newCol;
	        for(UL k = 0; k < col.size(); k ++) if(k < col.size() - 1 && !merged[k] && col[k] == col[k + 1])
				newCol.push_back(col[k] << 1), merged[k] = true, merged[k + 1] = true, changed = true, score += (col[k] << 1);
	        else if(!merged[k]) newCol.push_back(col[k]);
	        while(newCol.size() < 4) newCol.push_back(0);
	        for(LL i = 1; i <= 4; i ++) {
	            if(mp[i][j] != newCol[i - 1]) changed = true;
	            mp[i][j] = newCol[i - 1];
	        }
	    }
	    if(changed) addRandomTile();
	}
	void Down() {
	    bool changed = false;
	    for(LL j = 1; j <= 4; j ++) {
	        vector <LL> col;
	        for(LL i = 4; i >= 1; i --) if(mp[i][j] != 0) col.push_back(mp[i][j]);
	        vector <bool> merged(col.size(), false);
	        vector <LL> newCol;
	        for(UL k = 0; k < col.size(); k ++) if(k < col.size() - 1 && !merged[k] && col[k] == col[k + 1])
				newCol.push_back(col[k] << 1), merged[k] = true, merged[k + 1] = true, changed = true, score += (col[k] << 1);
			else if(!merged[k]) newCol.push_back(col[k]);
	        while(newCol.size() < 4) newCol.push_back(0);
	        for(LL i = 4; i >= 1; i --) {
	            if(mp[i][j] != newCol[4 - i]) changed = true;
	            mp[i][j] = newCol[4 - i];
	        }
	    }
	    if(changed) addRandomTile();
	}
	bool move(char way) {
		switch(way) {
			case 'w': case 'W': case 'i': case 'I': Up(); break;
			case 's': case 'S': case 'k': case 'K': Down(); break;
			case 'a': case 'A': case 'j': case 'J': Left(); break;
			case 'd': case 'D': case 'l': case 'L': Right(); break;
			default: return false;
		}
		return true;
	}
	bool game() {
		init();
		printf("Welcome to 2048 game.\nPress enter to start...");
		pause();
		bool iswin = true, cont = false;
		LL starttime = nulltime;
		while(true) {
			system("cls");
			printMP();
			if(win() && !cont) {
				cont = 1;
				printf("\nPerfect! You've finally synthesized a 2048 tile.\n");
				printf("Would you like to continue to try? (Y/N)");
				re3: char is = getch();
				if(is == EOF) exit(-1);
				if(is == 'y' || is == 'Y') continue;
				else if(is == 'n' || is == 'N') break;
				else goto re3;
			}
			re: char c = getch();
			if(c == EOF) exit(-1);
			if(c == '\t') {
				system("cls");
				printf("Are you sure you are going to quit? (Y/N)");
				re2: char is = getch();
				if(is == EOF) exit(-1);
				if(is == 'y' || is == 'Y') return 0; 
				else if(is == 'n' || is == 'N') continue;
				else goto re2;
			}
			if(!move(c)) goto re;
			if(!canMove()) { iswin = 0; break; }
			if(starttime == nulltime) starttime = time(0);
		}
		LL endtime = time(0);
		system("cls");
		printf("Score: %lld\n\n", score);
		for(LL i = 1; i <= 4; i ++, printf("\n")) for(LL j = 1; j <= 4; j ++) if(mp[i][j]) printnumber(mp[i][j]);
		else chco(0), printf("-    ");
		chco("");
		if(!iswin) printf("\nGame over. You have no place to move.\n");
		printf("Time: %llds", endtime - starttime);
		printf("\n\nPress enter to return to menu...");
		pause();
		PGB::HPB(5, score, endtime - starttime);
		return iswin;
	}
}

#endif
