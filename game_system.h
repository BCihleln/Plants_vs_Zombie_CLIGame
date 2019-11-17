#pragma once
#include "basic.h"
#include "plants.h"
#include "map.h"
#include "store.h"
#include "zombie.h"
#include "display.h"
#include <thread>
#include <functional>
	//bind ������

#define map_file_path "map.txt"
#define info_file_path "info.txt"

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
	
	//INPUT_RECORD	InputRecord;//Input Buffer
	//DWORD				res;//IpNumbersOfEventsRead �xȡ�����Р�����

	HANDLE hStdin;//�˜�ݔ����	
	ifstream info_file;
	ifstream map_file;

	int score;
	bool continued_flag;

	//����ֵ0 �����˳�
	char interpret_key(DWORD target);
	void interpret_mouse(DWORD target);
	void mode_change();


//���������̎��ģʽ 
	enum class player_mode { normal, pause,store_selecting,map_selecting } mode;
	enum class signal {move,left_click,right_click} mouse;
	coordinate mouse_position;
	char key_stroke;
	bool selected;
	Plant* selected_plant;//�����ֲ��


	Map map;//map�а���������ֲ��c��ʬvector
	Store store;
	Display display;

	//�����@���r϶�l����ݔ���¼��cϵ�y��B��������������
	void action();
public:
	friend class Display;
	clock_t game_clock;//�Α��ڕr�g ��λ������
	GAME_SYSTEM();
	~GAME_SYSTEM();

	//�@ȡݔ����̖ ���+�I�P
	int get_input();
	bool next();
};