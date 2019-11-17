#pragma once
#include "basic.h"
#include <queue>
#include "creature.h"
#include "bullet.h"

class Plant:public Creature //��ֻ���F�����ֲ��
{
	plant_ID ID_;
	int attack_range_;//������������λ����Ļ�ַ�����
	int cost_; // ����ꖹ┵
	int cool_time_;// ���ٴ�ُ�I����s�r�g ��λ����
	queue<Bullet> bullets;//��ֲ�����a���ӏ����
	void attack();
	void die()override;
public:

	Plant();
	~Plant();

	//void operator=(const Plant& target)
	//{
	//	this->ATK_ = target.ATK_;
	//	this->ATK_SPD_ = target.ATK_SPD_;
	//	this->cool_time_ = target.cool_time_;
	//	this->cost_ = target.cost_;
	//	this->DEF_ = target.DEF_;
	//	this->direction = target.direction;
	//	this->ID_ = target.ID_;
	//	this->name_ = target.name_;
	//}

	void set_type(const plant_ID ID);
	void clean();
	int cost()const;
	int cool_time()const;
	plant_ID ID()const;
	string name()const;

	virtual void next(int clock);
};