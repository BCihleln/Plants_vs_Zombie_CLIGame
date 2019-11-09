#pragma once
#include "basic.h"
#include <queue>
#include "creature.h"
#include "bullet.h"

class Plant:public Creature //��ֻ���F�����ֲ��
{
	plant_ID ID;
	int cost; // ����ꖹ┵
	int cool_time;// ���ٴ�ُ�I����s�r�g ��λ����
	queue<BULLET> bullets;//��ֲ�����a���ӏ����
public:

	Plant();
	~Plant();

	void set_type(const plant_ID ID);
	void clean();
	int get_cost()const;
	int get_cool_time()const;
	plant_ID get_ID()const;

	void attack();

	virtual void next(int clock,coordinate& position);
};

/*TODO��
���F��ʽ���^�У�
	BUFF��ֲ�eg ���տ�������
	һ����ֲ�eg ���ҡ����ϣ�
	���m������eg �ش�
*/