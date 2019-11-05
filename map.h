#pragma once

#include "basic.h"
#include "table.h"
#include "plants.h"
#include "bullet.h"
#include "zombie.h"

struct mapCell
{
	ZOMBIE* zombie;//也許會有很多個zombie，可能要用vector結構存儲一個單元格裏面的所有zombie
	BULLET* bullet;//當前單元格是否有子彈
};

class Map:public Table<mapCell>
{
 //map[map_row][map_column];

	Plant plants[map_row][map_column];
	vector<ZOMBIE> zombies[map_row];	

	coordinate Screen2Map(coordinate target);

	//TODO 處理植物、僵尸雙方攻擊
	void compute_attack();
	//TODO 維護僵尸、子彈移動坐標
	void comput_move();
	
	//僵尸的管理 循環隊列，死掉的僵尸改名換姓后重新加入隊尾
	void generate_zombie();

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
	//}//重載[]來直接取得單元格數據

	void PlantOnXY(const plant_list target_ID,coordinate position);

	//Plant* select(coordinate position);

};