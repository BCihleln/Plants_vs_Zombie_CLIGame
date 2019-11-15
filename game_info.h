#pragma once

const char version[] = "0.4.0";

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

#define map_file "map.txt"
#define info_file "info.txt"

#define game_speed 1