#ifndef MINE_GAME
#define MINE_GAME

namespace MaceGambit {
	const string MCName = "minecraft:mace";
	const string CustomName = "Gambit";
	const string Icon = "\
         ##     \n\
        #**# ## \n\
       #*%**### \n\
      #*%%***#  \n\
     #*%%**&**# \n\
     #****&****#\n\
      #**&**%%*#\n\
       #***%%*# \n\
      +-#**%*#  \n\
     +-+ #**#   \n\
    +-+   ##    \n\
   +-+          \n\
  +-+           \n\
##-+            \n\
#=#             \n\
###             \n";
	const string Enchantments = "\
Density V\n\
Wind burst I\n\
Unbreaking III\n\
Mending\n";
}

namespace PGB {
	const string BKfilename = "GameHistory.bin";
	const string failmark = "\\/:*?\"<>|";
	constexpr LL score_noscore = -1;
	constexpr LL time_notime = -1;
	struct GameRes { LL gamenum, score, time; string tag; };
	vector <GameRes> History;
	string nowfilename = BKfilename;
	bool testmode = 0;
	bool saveHistory() {
	    allre:ofstream fout(nowfilename, ios::binary);
	    if(!fout) {
	        printf("保存失败。\n重试(Y/N): ");
	        re:char c = getch();
	        if(c == 'y' || c == 'Y') goto allre;
	        if(c != 'n' && c != 'N') goto re;
	        return false;
	    }
	    UL size = History.size();
	    fout.write((const char*)(&size), sizeof(size));
	    for(const auto& res : History) {
	        fout.write((const char*)(&res.gamenum), sizeof(res.gamenum));
	        fout.write((const char*)(&res.score), sizeof(res.score));
	        fout.write((const char*)(&res.time), sizeof(res.time));
	        UL tagLen = res.tag.size();
	        fout.write((const char*)(&tagLen), sizeof(tagLen));
	        fout.write(res.tag.c_str(), tagLen);
	    }
	    fout.close();
	    return true;
	}
	bool loadHistory() {
	    ifstream fin(nowfilename, ios::binary);
	    if(!fin) return false;
	    History.clear();
	    UL size;
	    fin.read((char*)(&size), sizeof(size));
	    for(UL i = 0; i < size; i ++) {
	        GameRes res;
	        fin.read((char*)(&res.gamenum), sizeof(res.gamenum));
	        fin.read((char*)(&res.score), sizeof(res.score));
	        fin.read((char*)(&res.time), sizeof(res.time));
	        UL tagLen;
	        fin.read((char*)(&tagLen), sizeof(tagLen));
	        if(tagLen > 0) res.tag.resize(tagLen), fin.read(&res.tag[0], tagLen);
	        else res.tag = "";
	        History.push_back(res);
	    }
	    fin.close();
	    return true;
	}
	bool failfilename(string s) {
		if(s.front() == '.') return 1;
		if(s.size() > 4 && s.substr(s.size(), 4) == ".bin") s.erase(s.end() - 4, s.end());
		for(char c : failmark) if(s.find(c) != string::npos) return 1;
		return 0;
	}
	void HPB(LL gamenum, LL score, LL time) { if(!testmode) History.push_back({gamenum, score, time, ""}), saveHistory(); }
}

#include "Minesweeper.hpp"
#include "tic_tac_toe.hpp"
#include "Maze.hpp"
#include "_2048.hpp"
#include "TypingGame.hpp"
#include "SlidingPuzzle.hpp"
#include "PlussingGame.hpp"

namespace PGB {
	void printtitle() {
		chco(""), printf("===== ");
		chco("green"), printf("Plain ");
		chco("red"), printf("Game ");
		chco("Lblue"), printf("Box");
		chco(""), printf(" =====\n");
		chco("blue"), printf("Blue");
		chco("red"), printf("Carrot ");
		chco("yellow"), printf("studio\n\n");
		chco("");
	}
	void printMaceGambit() {
		chco("purple");
		printf("%s\n", MaceGambit::CustomName.c_str());
		chco("gray");
		printf("%s\n\n", MaceGambit::MCName.c_str());
		for(char c : MaceGambit::Icon) {
			switch(c) {
				case '#': chco("gray"); break;
				case '+': chco("blue"); break;
				case '-': chco("Lblue"); break;
				case '*': chco("cyan"); break;
				case '%': chco("gray"); break;
				case '&': chco(""); break;
				case '=': chco(""); break;
				default: chco("");
			}
			printf("%c", c);
		}
		printf("\n");
		for(char c : MaceGambit::Enchantments) {
			if(c == 'I' || c == 'V') chco("purple");
			else chco("");
			printf("%c", c);
		}
		chco("");
		printf("\n\n按回车返回主菜单...");
		pause();
	}
	bool GameRes_cmp(const GameRes& x, const GameRes& y) {
		if(x.gamenum != y.gamenum) return x.gamenum < y.gamenum;
		if(x.score != y.score) return x.score > y.score;
		if(x.time != y.time) return x.time < y.time;
		return false;
	}
	void CheckHistory() {
		re:if(History.empty()) {
			printf("未找到游戏记录。\n按回车返回主菜单...");
			pause();
			return ;
		}
		printf("编号 | 游戏                         |  分数   |  时长  | 标签\n");
		for(UL i = 0; i < History.size(); i ++) {
			string GameName;
			GameRes nd = History[i];
			switch(nd.gamenum) {
				case 1: GameName = "经典扫雷                   "; break;
				case 2: GameName = "钻石寻宝扫雷             "; break;
				case 3: GameName = "井字棋                   "; break;
				case 4: GameName = "陷阱迷宫                 "; break;
				case 5: GameName = "2048游戏                 "; break;
				case 6: GameName = "打字游戏                 "; break;
				case 7: GameName = "滑块拼图                "; break;
				case 8: GameName = "加法路径游戏             "; break;
			   default: GameName = "未知游戏                 "; break;
			}
			if(GameName.empty()) continue;
			printf("%6lld | %s | ", i + 1, GameName.c_str());
			if(nd.score == score_noscore) printf("无分数 | ");
			else printf("%8lld | ", nd.score);
			if(nd.time != time_notime) printf("%5llds | ", nd.time);
			else printf("       | ");
			printf("%s\n", nd.tag.c_str());
		}
		printf("\n历史文件名: %s\n", nowfilename.c_str());
		printf("添加标签: tag [历史编号] [标签]\n删除记录: del [历史编号]\n");
		printf("删除多条记录: delbe [起始编号] [结束编号]\n");
		printf("删除全部记录: delall\n重新加载数据: reload\n排序记录: sort\n");
		printf("交换记录: swap [第一个编号] [第二个编号]\n"); 
		printf("若需要复制记录，请使用 FilePusher。\n");
		printf("菜单: /hub\n\n操作: ");
		string op; getstr(op);
		if(op == "/hub") return ;
		if(op == "tag") {
			LL number = get();
			if(Isout) return ;
			string ntag; getlstr(ntag);
			if(number <= 0 || number > LL(History.size())) goto qu;
			History[number - 1].tag = ntag;
			saveHistory();
		} else if(op == "del") {
			LL number = get();
			if(Isout) return ;
			if(number <= 0 || number > LL(History.size())) goto qu;
			History.erase(History.begin() + number - 1);
			saveHistory();
		} else if(op == "delbe") {
			LL beg = get();
			if(Isout) return ;
			LL end = get();
			if(Isout) return ;
			if(beg <= 0 || beg > LL(History.size())) goto qu;
			if(end <= 0 || end > LL(History.size())) goto qu;
			if(end < beg) goto qu;
			History.erase(History.begin() + beg - 1, History.begin() + end);
			saveHistory();
		} else if(op == "delall") {
			system("cls");
			printf("确定要删除全部历史记录吗(Y/N)?");
			reinput:char in = getch();
			if(in == 'y' || in == 'Y') History.clear();
			else if(in == 'n' || in == 'N') goto qu;
			else goto reinput;
		} else if(op == "reload") loadHistory();
		  else if(op == "sort") stable_sort(History.begin(), History.end(), GameRes_cmp), saveHistory();
		  else if(op == "swap") {
			LL n1 = get() - 1, n2 = get() - 1;
			swap(History[n1], History[n2]);
			saveHistory();
		}
		qu:system("cls");
		goto re;
	}
	void Settings() {
		while(true) {
			system("cls");
			printf("设置:\n");
			printf("1. 护眼模式（关闭颜色变化，屏幕输出更快） ["); chco(eye_protection ? "green" : "Lblue"); printf("%s", eye_protection ? "开启" : "关闭"); chco(""); printf("]\n");
			printf("2. 设置随机种子 ["); if(randomSeed == -1) chco("Lblue"), printf("未设置"); else chco("green"), printf("当前种子: %lld", randomSeed); chco(""); printf("]\n");
			printf("3. 测试模式（不保存游戏历史） ["); chco(testmode ? "green" : "Lblue"); printf("%s", testmode ? "开启" : "关闭"); chco(""); printf("]\n");
			printf("4. 使用其他历史文件名 ["); chco(nowfilename == BKfilename ? "Lblue" : "green"); printf("%s", nowfilename == BKfilename ? "未修改" : ("当前文件名: " + nowfilename).c_str()); chco(""); printf("]\n");
			printf("__________________\n菜单: /hub\n更改选项: ");
			string in;
			getlstr(in);
			if(in == "/hub") return ;
			if(in.empty()) continue;
			switch(in.front()) {
				case '1': eye_protection ^= 1; break;
				case '2': re1: system("cls"); printf("重置（输入 0 可重置）: ");
						  LL x; x = get(); if(Isout) return ;
						  if(x < 0) goto re1; if(x == 0) setRandomSeed(); else setRandomSeed(x); break;
				case '3': testmode ^= 1; break;
				case '4': re2:system("cls"); printf("重置（留空即可重置）: ");
						  string s; getlstr(s); if(Isout) return ;
						  if(s.empty()) nowfilename = BKfilename;
						  else if(failfilename(s)) goto re2;
						  else if(s.size() < 4 || (s.size() >= 4 && s.substr(s.size() - 4, 4) != ".bin")) nowfilename = s + ".bin";
						  else nowfilename = s;
						  History.clear(); loadHistory(); break;
			}
		}
	}
	void menu() {
		loadHistory();
		while(true) {
			printtitle();
			printf("菜单\n\n1. 经典扫雷\n2. 钻石寻宝扫雷\n3. 井字棋\n");
			printf("4. 陷阱迷宫\n5. 2048 游戏\n6. 打字游戏\n7. 滑块拼图\n8. 加法路径游戏\n");
			printf("\nC. 查看历史记录\nS. 设置\nX. 退出\n____________\n选择: ");
			string s;
			getlstr(s);
			system("cls");
			for(char& i : s) if(isalpha(i)) i = tolower(i);
			if(s == "gambit" || s == "mace" || s == "macegambit") {
				printMaceGambit();
				system("cls");
				continue;
			}
			if(s.size() == 1) switch(s.front()) {
				case '1': Minesweeper::Classic.game(); break;
				case '2': Minesweeper::Diamond_finder.game(); break;
				case '3': Tictactoe::game(); break;
				case '4': TrapMaze::game(); break;
				case '5': _2048::game(); break;
				case '6': TypingGame::game(); break;
				case '7': SlidingPuzzle::game(); break;
				case '8': PlussingGame::game(); break;
				case 'c': case 'C': CheckHistory(); break;
				case 's': case 'S': Settings(); break;
				case 'x': case 'X': return ;
			} else if(s.find("gg") != string::npos) for(LL i = 1; i <= 1000; i ++) {
				printf("支持 ");
				chco("blue");
				printf("Blue");
				chco("red");
				printf("carrot ");
				chco("");
			}
			system("cls");
			Isout = false;
		}
	}
}
#endif
