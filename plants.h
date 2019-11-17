#pragma once
#include "basic.h"
#include <queue>
#include "creature.h"
#include "bullet.h"

class Plant:public Creature //先只實現射擊型植物
{
protected:
	plant_ID ID_;
	//int attack_range_;//攻擊範圍，單位：屏幕字符寬度
	int cost_; // 消耗陽光數
	int cool_time_;// 能再次購買的冷卻時間 單位：秒
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
	queue<Bullet> bullets;//由植物生產的子彈隊列
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
-> Melon 倭瓜
-> Corn Nuke
*/

	int explode_range_;//爆炸半徑

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
	-> thorns 荊棘
	-> Garlic 
	-> Fire Chunk 火炬樹
	*/
	virtual void attack()override;
public:
	Buff_Plant();

	void set_type(const plant_ID& ID)override;
	virtual void next(int clock)override;
};