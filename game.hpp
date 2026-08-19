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
	        printf("Failed to save file.\nTry again(Y or N): ");
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
		printf("\n\nPress enter to return to menu...");
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
			printf("No game history was found.\nPress enter to return to menu...");
			pause();
			return ;
		}
		printf("Number | Game                         |  Score   |  Time  | Tag\n");
		for(UL i = 0; i < History.size(); i ++) {
			string GameName;
			GameRes nd = History[i];
			switch(nd.gamenum) {
				case 1: GameName = "Minesweeper - Classic       "; break;
				case 2: GameName = "Minesweeper - Diamond finder"; break;
				case 3: GameName = "Tic tac toe                 "; break;
				case 4: GameName = "Trap maze                   "; break;
				case 5: GameName = "2048 game                   "; break;
				case 6: GameName = "Typing game                 "; break;
				case 7: GameName = "Sliding puzzle              "; break;
				case 8: GameName = "Plussing game               "; break;
			   default: GameName = "Unknown game                "; break;
			}
			if(GameName.empty()) continue;
			printf("%6lld | %s | ", i + 1, GameName.c_str());
			if(nd.score == score_noscore) printf("No score | ");
			else printf("%8lld | ", nd.score);
			if(nd.time != time_notime) printf("%5llds | ", nd.time);
			else printf("       | ");
			printf("%s\n", nd.tag.c_str());
		}
		printf("\nHistory file name: %s\n", nowfilename.c_str());
		printf("Add tag: tag [history number] [tag]\nDelete game history: del [history number]\n");
		printf("Delete more game history: delbe [begin number] [end number]\n");
		printf("Delete all game history: delall\nReload data: reload\nSort histories: sort\n");
		printf("Swap histories: swap [Swap history number] [Swap history number]\n"); 
		printf("If you need to copy the histories, please use the FilePusher.\n");
		printf("Menu: /hub\n\nOperate: ");
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
			printf("Are you sure you are going to delete all of the history(Y or N)?");
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
			printf("Settings:\n");
			printf("1. Eye protection mode (no color change, screen output faster) ["); chco(eye_protection ? "green" : "Lblue"); printf("%s", eye_protection ? "OPEN" : "CLOSE"); chco(""); printf("]\n");
			printf("2. Set random seed ["); if(randomSeed == -1) chco("Lblue"), printf("Unset"); else chco("green"), printf("Current seed: %lld", randomSeed); chco(""); printf("]\n");
			printf("3. Testing mode (no game history saving) ["); chco(testmode ? "green" : "Lblue"); printf("%s", testmode ? "OPEN" : "CLOSE"); chco(""); printf("]\n");
			printf("4. Use other history file names ["); chco(nowfilename == BKfilename ? "Lblue" : "green"); printf("%s", nowfilename == BKfilename ? "Unchanged" : ("Current file name: " + nowfilename).c_str()); chco(""); printf("]\n");
			printf("__________________\nMenu: /hub\nChange which one: ");
			string in;
			getlstr(in);
			if(in == "/hub") return ;
			if(in.empty()) continue;
			switch(in.front()) {
				case '1': eye_protection ^= 1; break;
				case '2': re1: system("cls"); printf("reset (enter 0 to reset): ");
						  LL x; x = get(); if(Isout) return ;
						  if(x < 0) goto re1; if(x == 0) setRandomSeed(); else setRandomSeed(x); break;
				case '3': testmode ^= 1; break;
				case '4': re2:system("cls"); printf("reset (enter nothing to reset): ");
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
			printf("Menu\n\n1. Minesweeper - Classic\n2. Minesweeper - Diamond finder\n3. Tic tac toe\n");
			printf("4. Trap maze\n5. 2048 game\n6. Typing game\n7. Sliding puzzle\n8. Plussing game\n");
			printf("\nC. Check history score\nS. Settings\nX. Exit\n____________\nChoose: ");
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
				printf("Support ");
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
