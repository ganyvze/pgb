#include "heads.hpp"
#include "tools.hpp"
namespace PGB {
	const string BKfilename = "GameHistory.bin";
	constexpr LL score_noscore = -1;
	constexpr LL time_notime = -1;
	struct GameRes { LL gamenum, score, time; string tag; };
	vector <GameRes> History;
	string nowfilename = BKfilename;
	bool testmode = 0;
	bool saveHistory() {
	    allre:ofstream fout(nowfilename, ios::binary);
	    if(!fout) {
		        put("保存失败。\n重试(Y/N): ");
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
	void HPB(LL gamenum, LL score, LL time) { if(!testmode) History.push_back({gamenum, score, time, ""}), saveHistory(); }
}
void finish() {
	put("文件合并完成。");
	put("感谢使用。\n");
	put("按任意键关闭...");
	pause();
}
void errorout() {
	put("未找到该文件。");
	put("请将历史文件放在同一目录中。 ");
	finish();
	exit(0);
}
void CheckName(string& fn) {
	UL lst = fn.size();
	while(fn.back() == ' ' ||
		  fn.back() == '\n' ||
		  fn.back() == '\t' ||
		  fn.back() == '\r') fn.pop_back();
	if(fn.substr(lst - 4, lst - 1) != ".bin") {
		put("历史文件名必须以 \".bin\" 结尾。");
		finish();
		exit(0);
	}
}
int main() {
	init_console_encoding();
	put("欢迎使用文件推送器。 ");
	put("请输入历史文件名: ");
	string s; getlstr(s);
	CheckName(s);
	PGB::nowfilename = s;
	if(!PGB::loadHistory()) errorout();
	auto HistoryPusher = PGB::History;
	PGB::nowfilename = PGB::BKfilename;
	if(!PGB::loadHistory()) errorout();
	auto HistoryChange = PGB::History;
	for(auto i : HistoryPusher) HistoryChange.push_back(i);
	PGB::History = HistoryChange;
	PGB::saveHistory();
	finish();
	return 0;
}
