#pragma once
#include "basic.h"
#include "menu.h"
#include "map.h"
#include "store.h"

#include <thread>
#include <mutex>
#include <functional>
	//bind ������

/*
��ɹ���
	�����O��
		��󻯡����Ԅ�
	�؈D����ԃ ���xȡ��ӡ
	������ϴ�ӡ
	���ض����˴�ӡ
	�؈D�����c��Ļ��ӳ��
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
	
	coordinate ScreenCursor;//���λ��
	coordinate MouseCursor;//���λ��
	short last_MouseCursor_Y;

	CONSOLE_CURSOR_INFO default_cursor;
	HANDLE hStdOut;//�˜�ݔ�����

	std::mutex mutex;
	const Map* map;
	const Store* store;
	const int* score;

	void window_init();//��ʼ�����ڞ���󻯣����@ȡ��Ļ��С����λ���ַ���

	coordinate SCREEN_SIZE;//��λ���ַ���Ԫ��
#define SCREEN_LENGTH SCREEN_SIZE.X
#define SCREEN_WIDTH SCREEN_SIZE.Y


	char** MapLayer;//��Ļ���n����ӡ�r���Ա���֮ǰ��Ļ����Ϣ
	char** Zombie_BulletLayer;
	inline void ReadDataFileToScreenBuff(const char* filepath,coordinate start_position);
	void ReadStoreInfo();
	void screen_buffer_init();
	void WriteScreenBuffer(char* ScreenBuffer[],const char* target, coordinate position,bool middle_flag);
	//void CleanMapCell(coordinate target_Cell);
	void RefreshStdOut();
	void RefreshLayer();
	//void RefreshConsoleScreenBuffer();

	void HideCursor();//���ؿ���̨�Ĺ�� 
	void SetScreenCursor(coordinate target);
	void SetScreenCursor(short x, short y);

	inline void color(int a)//��ɫ����  
	{
		SetConsoleTextAttribute(hStdOut, 
			a/* | //Forground
			 BACKGROUND_INTENSITY | /* | BACKGROUND_GREEN /*|  BACKGROUND_RED |BACKGROUND_BLUE /*| BACKGROUND_INTENSITY*//*0*/);
		
		//TODO���ɫʲ��������ف�̎���
		/*
		Background : 0 ��ɫ

		*/
	}

	//void PrintLine();
	//void PrintLine(const string& target);
	void PrintOnMouse();
	void PrintOnXY(const string& target, coordinate position);
	void PrintOnXY(const coordinate& target, short x, short y);
	void PrintOnXY(const coordinate& target, coordinate position);
	//��������ȵ���ʼλ�ã����ؾ��к������
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