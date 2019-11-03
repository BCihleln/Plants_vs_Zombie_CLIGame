#pragma once

#include "basic.h"
#include "plants.h"
#include "zombie.h"

class MAP
{
	struct mapCell
	{
		PLANT* plant;
		ZOMBIE** zombie;//Ҳ�S���кܶ���zombie������Ҫ��vector�Y���惦һ����Ԫ���Y�������zombie
		bool bullet;//��ǰ��Ԫ���Ƿ����ӏ�
	} map[map_width][map_length];

	PLANT plants[map_width][map_length];
	vector<ZOMBIE> zombies[map_width];

public:
	friend class GAME_SYSTEM;
	MAP();
	~MAP();

	void init();

	
	mapCell* operator[](int target)
	{
		if (target > map_length)
		{
			cout << "Reading map out of Range!\n";
			exit(0);
		}
		return map[target];
	}//���d[]��ֱ��ȡ�Æ�Ԫ�񔵓�

	void PlantOnXY(PLANT& target, int x, int y);

	//TODO ��Ҫ�S�o�ӏ�����ʬ�����ˣ����m�Ƅӣ�

	//��ʬ�Ĺ��� ѭ�h��У������Ľ�ʬ�����Q�պ����¼����β
};