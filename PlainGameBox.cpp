#include "heads.hpp"
#include "tools.hpp"
#include "game.hpp"

int main() {
	init_console_encoding();
	load_update_check_setting();
	chco("Lblue"), put("正在检查更新...\n");
	if(check_for_updates()) {
		chco("green"), put("发现新版本！\n");chco("");
		put("是否安装更新(Y/N)? ");
		char choice;
		do choice = getch(); while(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');
		put("\n");
		if(choice == 'y' || choice == 'Y') {
			if(install_update()) return 0;
			chco("red"), put("更新失败！\n");chco("");
			pause();
		}
	}
	chco("");refresh_screen();
	PGB::menu();
	return 0;
}