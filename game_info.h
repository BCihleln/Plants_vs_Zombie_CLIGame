#pragma once

const char version[] = "0.6.0";

enum class plant_ID
{	//TODO 把所有屬性資料寫在csv文件中，啓動游戲時讀取
	None,

	//Buff
	Sun_Flower,
	Nut_Wall,
	Thorns,//荊棘地刺
	Garlic,
	Fire_chunk,//火炬樹

	//Shooter
	Bean_Shooter,
	Double_Bean_Shooter,
	Triple_Bean_Shooter,
	Bean_Gatlin,
	Ice_Bean_Shooter,

	//Explosive
	Cherry_Bomb,
	Potato_Mine,
	Melon,
	Corn_Nuke
};

//enum class zombie_list
//{
//	None,
//	zombie,
//	Bucket_zombie,
//	Dancer
//};

#define map_row 5
#define map_column 7
#define map_cell_length 18
#define map_cell_width 10

constexpr auto game_speed = 99;//這裏的game_speed是game_system的時鐘時長，而非真正的速度