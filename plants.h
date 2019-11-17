#pragma once
#include "basic.h"
#include <queue>
#include "creature.h"
#include "bullet.h"

class Plant:public Creature //��ֻ���F�����ֲ��
{
protected:
	plant_ID ID_;
	//int attack_range_;//������������λ����Ļ�ַ�����
	int cost_; // ����ꖹ┵
	int cool_time_;// ���ٴ�ُ�I����s�r�g ��λ����
	virtual void attack()=0;
	void die()override;//override from creature
public:

	Plant();
	~Plant();

	virtual void set_type(const plant_ID& ID)=0;
	void clean();
	int cost()const;
	int cool_time()const;
	plant_ID ID()const;
	string name()const;

	virtual void next(int clock)=0;
};

class Shooting_Plant :public Plant
{
	/*
	Type
	-> Bean Shooter Series
	-> Ice_Shooter
	*/
	int attack_range_;
	queue<Bullet> bullets;//��ֲ�����a���ӏ����
	virtual void attack()override;
public:
	Shooting_Plant();

	void set_type(const plant_ID& ID)override;
	virtual void next(int clock)override;
};

class Explosive_Plant :public Plant
{
	/*
Type
-> Cherry Bomb
-> Potato Mine
-> Melon ����
-> Corn Nuke
*/

	int explode_range_;//��ը�돽

	virtual void attack()override;
public:
	Explosive_Plant();

	void set_type(const plant_ID& ID)override;
	virtual void next(int clock)override;
};

class Buff_Plant :public Plant
{
	/*
	Type
	-> Sun flower
	-> Nut wall
	-> thorns �G��
	-> Garlic 
	-> Fire Chunk ����
	*/
	virtual void attack()override;
public:
	Buff_Plant();

	void set_type(const plant_ID& ID)override;
	virtual void next(int clock)override;
};