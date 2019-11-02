#pragma once

#include "basic.h"
#include "plants.h"
#include "zombie.h"

const int width = 5;
const int length = 7;

class MAP
{
	struct mapCell
	{
		PLANT* plant;
		ZOMBIE** zombie;//Ҳ�S���кܶ���zombie������Ҫ��vector�Y���惦һ����Ԫ���Y�������zombie
		bool bullet;//��ǰ��Ԫ���Ƿ����ӏ�
	} map[width][length];

public:
	friend class GAME_SYSTEM;
	MAP();

	
	mapCell* operator[](int target)
	{
		if (target > length)
		{
			cout << "Reading map out of Range!\n";
			exit(0);
		}
		return map[target];
	}//���d[]��ֱ��ȡ�Æ�Ԫ�񔵓�
};