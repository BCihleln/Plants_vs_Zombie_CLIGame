#pragma once
#include "basic.h"

const char version[] = "0.0.1";

class GAME_SYSTEM
{
	HANDLE hStdin;//�˜�ݔ����

	INPUT_RECORD	InputRecord;//Input Buffer
	DWORD				res;//IpNumbersOfEventsRead �xȡ�����Р�����

	coordinate mouse_position;

	DISPLAY display;
	//MAP map;
	//ZOMBIE zombies
	//PLANTS plants
	//STORE store

	int score;
	

	//����ֵ0 �����˳�
	int interpret_key(DWORD target);
	void interpret_mouse(DWORD target);
public:
	MAP map;
	GAME_SYSTEM();
	~GAME_SYSTEM();

	//�@ȡݔ����̖ ���+�I�P
	int get_input();

};