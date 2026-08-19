#ifndef MINE_MAZE
#define MINE_MAZE

namespace TrapMaze {
	LL n, airmin, airmax, nx, ny, trapcnt, health, maxhealth, newtrytime;
	vector <vector <char>> mp;
	vector <vector <bool>> vis, open, trap;
	bool again;
	double dif;
	char diff;
	constexpr LL dx[] = {1, -1, 0, 0};
	constexpr LL dy[] = {0, 0, 1, -1};
	void init() {
		mp.clear(), vis.clear(), open.clear(), trap.clear();
		mp.resize(n + 2, vector <char> (n + 2, '#'));
		vis.resize(n + 2, vector <bool> (n + 2, 0));
		open.resize(n + 2, vector <bool> (n + 2, 0));
		trap.resize(n + 2, vector <bool> (n + 2, 0));
		again = false;
		nx = 1, ny = 1;
		LL inner_total = (n - 2) * (n - 2);
		airmin = inner_total * 0.65;
		airmax = inner_total * 0.80;
		trapcnt = max(inner_total * dif, 1.0);
		maxhealth = min(max(trapcnt / 3, 1ll), 10ll);
		health = maxhealth;
	}
	void randomtrap() {
	    vector<pair<LL, LL>> positions;
	    for(LL i = 2; i < n; i ++) for(LL j = 2; j < n; j ++) if(mp[i][j] == ' ') positions.push_back({i, j});
	    for(UL i = positions.size() - 1; i > 0; i --) {
	        UL j = random(0, i);
	        swap(positions[i], positions[j]);
	    }
	    LL placed = 0;
	    for(UL i = 0; i < positions.size() && placed < trapcnt; i ++) {
	        LL x = positions[i].first;
	        LL y = positions[i].second;
	        mp[x][y] = 'T';
	        placed ++;
	    }
	}
	void new_maze() {
	    init();
	    stack <pair <LL, LL>> st;
	    for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= n; j ++) vis[i][j] = false; 
	    LL startX = 2, startY = 2;
	    mp[startX][startY] = ' ';
	    vis[startX][startY] = true;
	    st.push({startX, startY});
	    LL airCount = 1;
	    while(!st.empty()) {
	    	if(newtrytime + 20 < time(0)) return ;
	        LL x = st.top().first;
	        LL y = st.top().second;
	        vector <pair <LL, LL>> neighbors;
	        if(x - 2 >= 1 && !vis[x - 2][y] && mp[x - 2][y] == '#') neighbors.push_back({x - 2, y});
	        if(x + 2 <= n && !vis[x + 2][y] && mp[x + 2][y] == '#') neighbors.push_back({x + 2, y});
	        if(y - 2 >= 1 && !vis[x][y - 2] && mp[x][y - 2] == '#') neighbors.push_back({x, y - 2});
	        if(y + 2 <= n && !vis[x][y + 2] && mp[x][y + 2] == '#') neighbors.push_back({x, y + 2});
	        if(!neighbors.empty()) {
	            LL idx = random(0, neighbors.size() - 1);
	            LL nx = neighbors[idx].first;
	            LL ny = neighbors[idx].second;
	            LL wallX = (x + nx) / 2;
	            LL wallY = (y + ny) / 2;
	            mp[wallX][wallY] = ' ';
	            mp[nx][ny] = ' ';
	            vis[nx][ny] = true;
	            st.push({nx, ny});
	            airCount += 2;
	        } else st.pop();
	    }
	    printf("[30%%]DFS create done.\n");
	    if(airCount < airmin) {
	        LL needed = airmin - airCount;
	        vector <pair <LL, LL>> walls;
	        for(LL i = 2; i < n; i ++) for(LL j = 2; j < n; j ++) if(mp[i][j] == '#') {
                LL airNeighbors = 0;
				for(LL d = 0; d < 4; d ++) {
                    LL ni = i + dx[d];
                    LL nj = j + dy[d];
                    if(ni >= 1 && ni <= n && nj >= 1 && nj <= n && mp[ni][nj] == ' ') airNeighbors ++;
                }
                if(airNeighbors >= 2) walls.push_back({i, j});
	        }
	        while(needed > 0 && !walls.empty()) {
	        	if(newtrytime + 20 < time(0)) return ;
	            LL idx = random(0, walls.size() - 1);
	            LL x = walls[idx].first;
	            LL y = walls[idx].second;
	            mp[x][y] = ' ';
	            airCount ++;
	            needed --;
	            walls.erase(walls.begin() + idx);
	        }
	    }
	    mp[1][1] = ' ';
	    mp[n][n] = ' ';
	    for(LL i = -1; i <= 1; i ++) for(LL j = -1; j <= 1; j ++) if(i || j) {
            if(mp[1 + i][1 + j] == '#') mp[1 + i][1 + j] = ' ';
	        if(mp[n + i][n + j] == '#') mp[n + i][n + j] = ' ';
	    }
	    randomtrap();
	    printf("[80%%]Map created.\n");
	    for(LL i = 1; i <= n; i ++) for(LL j = 1; j <= n; j ++) vis[i][j] = false; 
	    vector <vector <bool>> trapvis(n + 2, vector <bool> (n + 2, false));
	    queue <pair <LL, LL>> qu;
	    qu.push({1, 1});
	    vis[1][1] = true;
	    bool reachable = false;
	    LL thealth = maxhealth;
	    while(!qu.empty()) {
	    	if(newtrytime + 20 < time(0)) return ;
	        auto nd = qu.front(); qu.pop();
	        LL x = nd.first, y = nd.second;
	        if(x == n && y == n) {
	            reachable = true;
	            break;
	        }
	        if(mp[x][y] == 'T' && !trapvis[x][y]) {
			    trapvis[x][y] = true;
			    if(thealth <= 1) {
			        mp[x][y] = ' ';
			        for(LL i = 1; i <= n && thealth <= 1; i ++) for(LL j = 1; j <= n && thealth <= 1; j ++) if(trapvis[i][j] && mp[i][j] == 'T') { mp[i][j] = ' ', thealth ++; break; }
			    } else thealth --;
			}
	        for(LL d = 0; d < 4; d ++) {
	            LL nx = x + dx[d];
	            LL ny = y + dy[d];
	            if(nx >= 1 && nx <= n && ny >= 1 && ny <= n && !vis[nx][ny] && (mp[nx][ny] == ' ' || mp[nx][ny] == 'T')) vis[nx][ny] = true, qu.push({nx, ny});
	        }
	    }
	    mp[1][1] = '.', mp[n][n] = 'E';
	    if(!reachable || airCount < airmin || airCount > airmax || thealth <= 0) again = true;
	    printf("[100%%]Map check complete.\n");
	}
	void printmaze() {
	    for(LL i = 1; i <= n; i ++) {
	        for(LL j = 1; j <= n; j ++) {
	            if(i == nx && j == ny) chco("red"), printf(" *");
	            else if(i == n && j == n) chco("green"), printf(" E");
	            else if(open[i][j] && mp[i][j] == 'T') chco("red"), printf(" %c", mp[i][j]);
	            else if(open[i][j]) chco(""), printf(" %c", mp[i][j]);
				else chco("blue"), printf(" -");
	        }
	        printf("\n");
	    }
	    chco("");
	}
	bool move(char cmd) {
		LL tx = nx, ty = ny;
		switch(cmd) {
			case 'w': case 'W': case 'i': case 'I': tx = nx - 1; break;
			case 's': case 'S': case 'k': case 'K': tx = nx + 1; break;
			case 'a': case 'A': case 'j': case 'J': ty = ny - 1; break;
			case 'd': case 'D': case 'l': case 'L': ty = ny + 1; break;
			default: return false;
		}
		if(tx >= 1 && tx <= n && ty >= 1 && ty <= n && mp[tx][ty] != '#') {
			nx = tx;
			ny = ty;
			if(mp[nx][ny] == 'T') health --, mp[nx][ny] = ' ';
			for(LL i = -1; i <= 1; i ++) for(LL j = -1; j <= 1; j ++) if(i || j) open[nx + i][ny + j] = 1;
			return true;
		} else return false;
	}
	bool game() {
		printf("迷宫大小: ");
		n = get();
		while(n <= 8 && !Isout) {
			printf("大小必须大于 8。\n");
			printf("迷宫大小: ");
			n = get();
		}
		if(Isout) return false;
		string dif_;
		re1:system("cls");
		printf("难度：\n\nA: 简单\nB: 普通\nC: 困难\n\n请选择难度: ");
		getlstr(dif_);
		if(dif_ == "/hub") return false;
		if(dif_.empty()) goto re1;
		diff = dif_.front();
		if(tolower(diff) != 'a' && tolower(diff) != 'b' && tolower(diff) != 'c') { system("cls"); goto re1; }
		dif = (diff == 'a' ? 0.12 : (diff == 'b' ? 0.20 : 0.30));
		newtrytime = time(0);
		system("cls");
		printf("正在生成地图...\n");
		do {
			again = false, new_maze();
			if(newtrytime + 20 < time(0)) {
				printf("\n地图生成耗时过长。\n请下次输入更小的数字。\n");
				printf("\n按回车返回主菜单...");
				pause();
				return false;
			}
			if(again) printf("[0%%]重新生成地图中...\n");
		} while(again);
		for(LL i = -1; i <= 1; i ++) for(LL j = -1; j <= 1; j ++) if(i || j) open[nx + i][ny + j] = 1;
		LL starttime = nulltime, endtime = 0;
		while(true) {
			system("cls");
			printf("找到出口 \"E\"。\n生命值: %lld / %lld\n", health, maxhealth);
			printmaze();
			printf("移动：W 或 I(上) S 或 K(下) A 或 J(左) D 或 L(右)\n菜单：[TAB]\n");
			printf("输入: ");
			in:char input = getch();
			if(input == EOF) exit(-1);
			if(input == '\t') {
				system("cls");
				printf("确定要退出吗(Y/N): ");
				reask:input = getch();
				if(input == EOF) exit(-1);
				if(input == 'y' || input == 'Y') return false;
				if(input == 'n' || input == 'N') continue;
				goto reask;
			}
			if(!move(input)) goto in;
			if(nx == n && ny == n) {
				endtime = time(0);
				system("cls");
				printmaze();
				chco("green");
				printf("你赢了！\n生命值: %lld", health);
				chco("");
				break;
			}
			if(health <= 0) {
				endtime = time(0);
				system("cls");
				printmaze();
				printf("游戏失败\n按回车返回主菜单...");
				pause();
				PGB::HPB(4, 0, endtime - starttime);
				return false;
			}
			if(starttime == nulltime) starttime = time(0);
		}
		printf("\n按回车返回主菜单...");
		pause();
		PGB::HPB(4, 100.0 * health / maxhealth, endtime - starttime);
		return true;
	}
}

#endif
