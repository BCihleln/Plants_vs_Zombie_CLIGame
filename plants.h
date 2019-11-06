#pragma once
#include "basic.h"
#include <queue>
#include "creature.h"
#include "bullet.h"

class Plant:private Creature //��ֻ���F�����ֲ��
{
	int cost; // ����ꖹ┵
	int cool_time;// ���ٴ�ُ�I����s�r�g ��λ����
	queue<BULLET> bullets;//��ֲ�����a���ӏ����
public:
	plant_list ID;

	Plant();
	~Plant();

	void set_type(const plant_list ID);
	int get_cost()const;
	int get_cool_time()const;

	void attack();
};

/*TODO��
���F��ʽ���^�У�
	BUFF��ֲ�eg ���տ�������
	һ����ֲ�eg ���ҡ����ϣ�
	���m������eg �ش�
*/