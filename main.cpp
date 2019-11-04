#include "game_system.h"

/**
行有餘力：
根據屏幕大小動態生成地圖，按比例縮放

**/
#ifdef DEBUG

int main(void)
{
	GAME_SYSTEM game_system;
	while (true)
	{
		int code = game_system.get_input();

		if (code == 0)
			break;
	}

	return 0;
	//game_system.~GAME_SYSTEM();
	//exit(0);
		/*
		2019 11 02 return 0錯誤
		暫時先這樣頂著
		emmm 用return 0 的話
			在return 之前析構game_system，~game_system中
				調用35次plant[5][7]的析構函數，
				之後再依次析構其他成員
			正常返回到main 並return 0
			但最後程序要退出時似乎檢查了game_system的棧是否超界，
			然後就報錯超界……
				目前觀察到在game_system中添加了plants[5][7]這個類成員后才發生這樣的錯誤
					原本以爲是因爲釋放這個成員時，調用析構函數超過了35次
					逐步調試后發現調用次數正常
					不知道問題出在哪
			可能的話要看匯編語言了

		2019 11 03
		return 0 又沒有錯誤了……真是莫名其妙呢
		*/
}

#else
int main() //速度測試
{
}
#endif // !DEBUG
