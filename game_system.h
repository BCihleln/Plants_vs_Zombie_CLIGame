#pragma once
#include "basic.h"

const char version[] = "0.0.1";

class GAME_SYSTEM
{
	HANDLE hStdin;//標準輸入句柄

	INPUT_RECORD	InputRecord;//Input Buffer
	DWORD				res;//IpNumbersOfEventsRead 讀取到的行爲數量

	coordinate mouse_position;

	DISPLAY display;
	//MAP map;
	//ZOMBIE zombies
	//PLANTS plants
	//STORE store

	int score;
	

	//返回值0 代表退出
	int interpret_key(DWORD target);
	void interpret_mouse(DWORD target);
public:
	MAP map;
	GAME_SYSTEM();
	~GAME_SYSTEM();

	//獲取輸入信號 鼠標+鍵盤
	int get_input();

};