#pragma once
#include "basic.h"
#include <queue>
#include "creature.h"
#include "bullet.h"

class Plant:protected Creature //��ֻ���F�����ֲ��
{
	plant_list ID;
protected:
	int cost; // ����ꖹ┵
	queue<BULLET> bullets;//��ֲ�����a���ӏ����
public:
	Plant();
	~Plant();

	void set_type(const plant_list ID);

	void attack();
};

/*TODO��
���F��ʽ���^�У�
	BUFF��ֲ�eg ���տ�������
	һ����ֲ�eg ���ҡ����ϣ�
	���m������eg �ش�
*/