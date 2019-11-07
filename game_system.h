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

//根據玩家所處的模式，決定按鍵調用的功能
	enum player_mode{menu,normal_play,selecting,selected} mode;
	/*
	menu : 上下左右wasd、左鍵選擇選項，Enter確認進入選項，esc退出程序
	normal_play ：特定字母、鼠標移動到商店區域 -> selecting mode
	selecting ：
		商店範圍内左鍵且滿足選中條件 -> selected mode
		esc鍵 -> normal_play mode
	selected ：鼠標上打印選中物
		地圖範圍内 左鍵（放置選中物） -> normal_play mode
		右鍵 取消選中 -> normal_play mode
	*/
	

	//返回值0 代表退出
	int interpret_key(DWORD target);
	int interpret_mouse(DWORD target, coordinate position);
	void interpret_position_set_mode(coordinate position);
public:
	GAME_SYSTEM();
	~GAME_SYSTEM();

	//獲取輸入信號 鼠標+鍵盤
	int get_input();
	void next();
};