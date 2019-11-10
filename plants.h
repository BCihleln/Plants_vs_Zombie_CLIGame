#pragma once
#include "basic.h"
#include <queue>
#include "creature.h"
#include "bullet.h"

class Plant:private Creature //��ֻ���F�����ֲ��
{
	plant_ID ID_;
	int cost_; // ����ꖹ┵
	int cool_time_;// ���ٴ�ُ�I����s�r�g ��λ����
	queue<BULLET> bullets;//��ֲ�����a���ӏ����
	void attack();
public:

	Plant();
	~Plant();

	void set_type(const plant_ID ID);
	void clean();
	int cost()const;
	int cool_time()const;
	plant_ID ID()const;
	string name()const;


	virtual void next(int clock);
};

/*TODO��
���F��ʽ���^�У�
	BUFF��ֲ�eg ���տ�������
	һ����ֲ�eg ���ҡ����ϣ�
	���m������eg �ش�
*/