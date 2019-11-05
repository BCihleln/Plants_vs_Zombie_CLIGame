#pragma once

#include "basic.h"
#include "plants.h"
#include "bullet.h"
#include "zombie.h"

class Map
{
	struct mapCell
	{
		ZOMBIE* zombie;//Ҳ�S���кܶ���zombie������Ҫ��vector�Y���惦һ����Ԫ���Y�������zombie
		BULLET* bullet;//��ǰ��Ԫ���Ƿ����ӏ�
	} map[map_row][map_column];

	Plant plants[map_row][map_column];
	vector<ZOMBIE> zombies[map_row];

	coordinate Screen2Map(coordinate target);


public:
	friend class GAME_SYSTEM;
	Map();
	~Map();

	void init();
		
	//mapCell* operator[](int target)
	//{
	//	if (target > map_column)
	//	{
	//		cout << "Reading map out of Range!\n";
	//		exit(0);
	//	}
	//	return map[target];
	//}//���d[]��ֱ��ȡ�Æ�Ԫ�񔵓�

	void PlantOnXY(const plant_list target_ID,coordinate position);

	Plant* select(coordinate position);

	//TODO ��Ҫ�S�o�ӏ�����ʬ�����ˣ����m�Ƅӣ�

	//��ʬ�Ĺ��� ѭ�h��У������Ľ�ʬ�����Q�պ����¼����β
};