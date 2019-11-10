#pragma once
#include "basic.h"
#include "plants.h"
#include "map.h"
#include "store.h"
#include "zombie.h"
#include "display.h"

/*
��ɹ���
	ݔ����̖�Ĳ��@
		�I�P�����
*/

/*
�����N�����y��׃��
�y���S�غϔ����Ӷ����ӣ����]���y���ǻغϔ���ָ������
*/

class GAME_SYSTEM
{
	HANDLE hStdin;//�˜�ݔ����

	INPUT_RECORD	InputRecord;//Input Buffer
	DWORD				res;//IpNumbersOfEventsRead �xȡ�����Р�����
	
	Map map;//map�а���������ֲ��c��ʬvector
	Store store;

	DISPLAY display;

	int score;
	clock_t clock_start;//�Α��_ʼ�r�g

	//����ֵ0 �����˳�
	char interpret_key(DWORD target);
	void interpret_mouse(DWORD target);
	void mode_change();


//���������̎��ģʽ 
	enum class player_mode { normal, store_selecting,map_selecting } mode;
	enum class signal {move,left_click,right_click} mouse;
	char key_stroke;
	coordinate mouse_position;
	bool selected;
	Plant* selected_plant;//�����ֲ��

	//�����@���r϶�l����ݔ���¼��cϵ�y��B��������������
	void action();
public:
	clock_t game_clock;//�Α��ڕr�g ��λ������
	GAME_SYSTEM();
	~GAME_SYSTEM();

	//�@ȡݔ����̖ ���+�I�P
	int get_input();
	void next();
};