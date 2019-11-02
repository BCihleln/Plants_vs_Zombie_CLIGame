#pragma once
#include "basic.h"
#include "plants.h"
#include "map.h"
#include "store.h"
#include "zombie.h"
#include "display.h"

const char version[] = "0.0.2";
/*
��ɹ���
	ݔ����̖�Ĳ��@
		�I�P�����
*/

class GAME_SYSTEM
{
	HANDLE hStdin;//�˜�ݔ����

	INPUT_RECORD	InputRecord;//Input Buffer
	DWORD				res;//IpNumbersOfEventsRead �xȡ�����Р�����
	
	DISPLAY display;
	MAP map;
	ZOMBIE zombies;
	PLANT plants[5][7];
	STORE store;

	int score;
	int clock;
	

	//����ֵ0 �����˳�
	int interpret_key(DWORD target);
	void interpret_mouse(DWORD target);
public:
	GAME_SYSTEM();
	~GAME_SYSTEM();

	//�@ȡݔ����̖ ���+�I�P
	int get_input();

};