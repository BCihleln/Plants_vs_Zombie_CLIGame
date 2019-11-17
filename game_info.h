#pragma once

const char version[] = "0.5.0";

enum class plant_ID
{
	None,
	Sun_Flower,
	Bean_Shooter,
	Nut_Wall
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

constexpr auto game_speed = 9;//這裏的game_speed是game_system的時鐘時長，而非真正的速度