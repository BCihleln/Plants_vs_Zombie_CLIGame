#pragma once
#include "basic.h"

/*
完成功能
	窗口設定
		最大化、不捲動
	地圖、咨詢 的讀取打印
	在鼠標上打印
	在特定坐標打印
	地圖坐標與屏幕的映射
*/

class DISPLAY
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

	CONSOLE_CURSOR_INFO default_cursor;
	HANDLE hStdOut;//標準輸出句柄

	void window_init();//初始化窗口為最大化，并獲取屏幕大小（單位：字符）

	coordinate SCREEN_SIZE;//單位：字符單元格
#define SCREEN_LENGTH SCREEN_SIZE.X
#define SCREEN_WIDTH SCREEN_SIZE.Y
	char** SCREEN_BUFFER;//屏幕緩衝，打印時可以保存之前屏幕的信息
	inline void ReadDataFileToScreenBuff(const char* filepath,int position_x,int position_y);
	void screen_buffer_init();
	void WriteScreenBuffer(const char* target, coordinate position);
	void CleanMapCell(int x, int y);
	void RefreshStdOut();


	void HideCursor();//隐藏控制台的光标 
	void SetScreenCursor(coordinate target);
	void SetScreenCursor(int x, int y);

	inline void color(int a)//颜色函数  
	{
		SetConsoleTextAttribute(hStdOut, a | BACKGROUND_GREEN);//TODO：顔色什麽的後面再來處理吧
	}

	//void ReadMap();
	//void ReadInfo();
	void PrintLine();
	void PrintLine(const string& target);
	void PrintOnXY(const string& target, short x, short y);
	void PrintOnXY(const string& target, coordinate position);
	void PrintOnXY(const coordinate& target, short x, short y);
	void PrintOnXY(const coordinate& target, coordinate position);

	coordinate Map2Screen(short x, short y);//地圖坐標轉屏幕坐標


public:
	//friend class GAME_SYSTEM;
	DISPLAY();
	~DISPLAY();

	void SetMousePosition(coordinate target);
	void ShowCursor();

	void PrintOnMouse(const string& target);
	
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

};