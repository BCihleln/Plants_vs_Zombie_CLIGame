#pragma once
#include "basic.h"

/*
��ɹ���
	�����O��
		��󻯡����Ԅ�
	�؈D����ԃ ���xȡ��ӡ
	������ϴ�ӡ
	���ض����˴�ӡ
	�؈D�����c��Ļ��ӳ��
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
	
	coordinate ScreenCursor;//���λ��
	coordinate MouseCursor;//���λ��

	CONSOLE_CURSOR_INFO default_cursor;
	HANDLE hStdOut;//�˜�ݔ�����

	void window_init();//��ʼ�����ڞ���󻯣����@ȡ��Ļ��С����λ���ַ���

	coordinate SCREEN_SIZE;//��λ���ַ���Ԫ��
#define SCREEN_LENGTH SCREEN_SIZE.X
#define SCREEN_WIDTH SCREEN_SIZE.Y
	char** SCREEN_BUFFER;//��Ļ���n����ӡ�r���Ա���֮ǰ��Ļ����Ϣ
	inline void ReadDataFileToScreenBuff(const char* filepath,int position_x,int position_y);
	void screen_buffer_init();
	void WriteScreenBuffer(const char* target, coordinate position);
	void CleanMapCell(int x, int y);
	void RefreshStdOut();


	void HideCursor();//���ؿ���̨�Ĺ�� 
	void SetScreenCursor(coordinate target);
	void SetScreenCursor(int x, int y);

	inline void color(int a)//��ɫ����  
	{
		SetConsoleTextAttribute(hStdOut, a | BACKGROUND_GREEN);//TODO���ɫʲ��������ف�̎���
	}

	//void ReadMap();
	//void ReadInfo();
	void PrintLine();
	void PrintLine(const string& target);
	void PrintOnXY(const string& target, short x, short y);
	void PrintOnXY(const string& target, coordinate position);
	void PrintOnXY(const coordinate& target, short x, short y);
	void PrintOnXY(const coordinate& target, coordinate position);

	coordinate Map2Screen(short x, short y);//�؈D�����D��Ļ����


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