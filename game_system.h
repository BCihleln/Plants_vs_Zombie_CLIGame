#pragma once
#include "basic.h"
#include <vector>
#include "plants.h"
#include "map.h"
#include "store.h"
#include "zombie.h"
#include "display.h"

/*
完成功能
	輸入信號的捕獲
		鍵盤、鼠標
*/

/*
行有餘力：難度變更
難度隨回合數增加而增加，考慮是難度是回合數的指數函數
*/

class GAME_SYSTEM
{
	HANDLE hStdin;//標準輸入句柄

	INPUT_RECORD	InputRecord;//Input Buffer
	DWORD				res;//IpNumbersOfEventsRead 讀取到的行爲數量
	
	Map map;//map中包含了所有植物、與僵尸vector
	Store store;

	DISPLAY display;

	int score;
	int clock;

	//返回值0 代表退出
	int interpret_key(DWORD target);
	int interpret_mouse(DWORD target);
	void mode_change();


//根據玩家所處的模式 
	enum class player_mode { normal, store_selecting,map_selecting } mode;
	enum class signal {move,left_click,right_click} mouse;
	int key_stroke;
	coordinate mouse_position;
	bool selected;
	plant_ID selected_plant;//拿起的植物ID

	//根據這個時隙發生的輸入事件與系統狀態，做出相應動作
	void action();
public:
	GAME_SYSTEM();
	~GAME_SYSTEM();

	//獲取輸入信號 鼠標+鍵盤
	int get_input();
	void next();
};