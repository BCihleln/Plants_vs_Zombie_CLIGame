#pragma once

#include "basic.h"
#include "table.cpp"
//	//��Ҫ�ҵ�ģ�廯��ɆT�����Ķ��x���ʰ���cpp
#include "plants.h"
#include "bullet.h"
#include "zombie.h"

class Map
{
	Table<Plant> yard;//�Nֲ���Ժ��

	struct zombie_on_screen
	{
		Zombie zombie;//��zombie������ù��������
		coordinate screen;//��Ļ����
	};
	vector<zombie_on_screen> zombies[map_row];

	struct bullet_on_screen
	{
		Bullet bullet;
		coordinate screen;
	};
	vector<bullet_on_screen> bullets[map_row];

	clock_t clock;
	int SunFlower_amount;

	//yard position
	bool has_plant(const coordinate position);

	void generate_zombie();
	int manage_zombie();
	void plant_attack();
	void manage_bullet();

	void init();
public:	
	friend class Display;
	Map();
	~Map();

	//���r�odisplay��ã�TODO ����Ҫ�h������Ӌ��ֱ��׌display�ʹ��tableָ�
	coordinate Screen2Cell_middle(coordinate screen_position)const
	{
		return yard.Screen2Cell_middle(screen_position);
	}

	string PlantOnXY(const Plant* target,coordinate position);

	int next(clock_t game_clock);
};