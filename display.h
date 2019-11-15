#pragma once
#include "basic.h"
#include "menu.h"
#include "map.h"
#include "store.h"

#include <thread>
#include <mutex>
#include <functional>
	//bind 綁定器

/*
完成功能
	窗口設定
		最大化、不捲動
	地圖、咨詢 的讀取打印
	在鼠標上打印
	在特定坐標打印
	地圖坐標與屏幕的映射
*/

class Display
{


	enum color_type {//foreground color
		black, blue,
		green, lakeblue,
		red, purple,
		yellow, white,
		gray, light_blue,
		light_green, super_light_green,
		light_red, light_purple,
		light_yellow, light_white
	};
	
	coordinate ScreenCursor;//光標位置
	coordinate MouseCursor;//鼠標位置
	short last_MouseCursor_Y;

	CONSOLE_CURSOR_INFO default_cursor;
	HANDLE hStdOut;//標準輸出句柄

	std::mutex mutex;
	const Map* map;
	const Store* store;
	const int* score;

	void window_init();//初始化窗口為最大化，并獲取屏幕大小（單位：字符）

	coordinate SCREEN_SIZE;//單位：字符單元格
#define SCREEN_LENGTH SCREEN_SIZE.X
#define SCREEN_WIDTH SCREEN_SIZE.Y


	char** MapLayer;//屏幕緩衝，打印時可以保存之前屏幕的信息
	char** Zombie_BulletLayer;
	inline void ReadDataFileToScreenBuff(const char* filepath,coordinate start_position);
	void ReadStoreInfo();
	void screen_buffer_init();
	void WriteScreenBuffer(char* ScreenBuffer[],const char* target, coordinate position,bool middle_flag);
	//void CleanMapCell(coordinate target_Cell);
	void RefreshStdOut();
	void RefreshLayer();
	//void RefreshConsoleScreenBuffer();

	void HideCursor();//隐藏控制台的光标 
	void SetScreenCursor(coordinate target);
	void SetScreenCursor(short x, short y);

	inline void color(int a)//颜色函数  
	{
		SetConsoleTextAttribute(hStdOut, 
			a/* | //Forground
			 BACKGROUND_INTENSITY | /* | BACKGROUND_GREEN /*|  BACKGROUND_RED |BACKGROUND_BLUE /*| BACKGROUND_INTENSITY*//*0*/);
		
		//TODO：顔色什麽的後面再來處理吧
		/*
		Background : 0 黑色

		*/
	}

	//void PrintLine();
	//void PrintLine(const string& target);
	void PrintOnMouse();
	void PrintOnXY(const string& target, coordinate position);
	void PrintOnXY(const coordinate& target, short x, short y);
	void PrintOnXY(const coordinate& target, coordinate position);
	//傳入最左側的起始位置，返回居中后的坐標
	coordinate middle(const string& target, coordinate left_side);
	
public:
	string MouseDisplay;
	Display(const Map& target_map, const Store& target_store, int* score);
	~Display();

	void SetMousePosition(coordinate target);
	void ShowCursor();
	
	void NewPlant(coordinate screen_position,const string& name);
	
	void Info();

	void Start();

	void Pause(bool mode);

	void Continue(coordinate position)
	{
		//gotoxy(position);
		//color(light_blue);
		//cout << "Press Space to Continue";
	}

	void GameOver();

	bool continue_flag;
	void UpdateStore();
	void UpdateSun();
	void UpdateScore();
	void UpdateZombie();
	void UpdateBullet();
	void next();
};