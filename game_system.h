#pragma once
#include "basic.h"
#include <vector>
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
	int clock;

//���������̎��ģʽ���Q�����I�{�õĹ���
	enum player_mode{menu,normal_play,selecting,selected} mode;
	/*
	menu : ��������wasd�����I�x���x헣�Enter�_�J�M���x헣�esc�˳�����
	normal_play ���ض���ĸ������Ƅӵ��̵�^�� -> selecting mode
	selecting ��
		�̵깠�������I�ҝM���x�Зl�� -> selected mode
		esc�I -> normal_play mode
	selected ������ϴ�ӡ�x����
		�؈D������ ���I�������x��� -> normal_play mode
		���I ȡ���x�� -> normal_play mode
	*/
	

	//����ֵ0 �����˳�
	int interpret_key(DWORD target);
	int interpret_mouse(DWORD target, coordinate position);
	void interpret_position_set_mode(coordinate position);
public:
	GAME_SYSTEM();
	~GAME_SYSTEM();

	//�@ȡݔ����̖ ���+�I�P
	int get_input();
	void next();
};