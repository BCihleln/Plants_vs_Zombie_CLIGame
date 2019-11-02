#pragma once
#include "basic.h"
#include "plants.h"
#include "map.h"
#include "store.h"
#include "zombie.h"
#include "display.h"

const char version[] = "0.0.2";
/*
完成功能
	輸入信號的捕獲
		鍵盤、鼠標
*/

class GAME_SYSTEM
{
	HANDLE hStdin;//標準輸入句柄

	INPUT_RECORD	InputRecord;//Input Buffer
	DWORD				res;//IpNumbersOfEventsRead 讀取到的行爲數量
	
	DISPLAY display;
	MAP map;
	ZOMBIE zombies;
	PLANT plants[5][7];
	STORE store;

	int score;
	int clock;
	

	//返回值0 代表退出
	int interpret_key(DWORD target);
	void interpret_mouse(DWORD target);
public:
	GAME_SYSTEM();
	~GAME_SYSTEM();

	//獲取輸入信號 鼠標+鍵盤
	int get_input();

};