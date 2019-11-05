#pragma once

const char version[] = "0.0.3";

enum plant_list
{
	None,
	Sun_Flower,
	Bean_Shooter,
	Nut_Wall
};

//enum zombie_list
//{
//	None,
//	zombie,
//	Bucket_zombie,
//	Dancer
//};

#define map_row 5
#define map_column 7
#define cell_length 18
#define cell_width 10


#define store_row 2
#define store_column map_column

#define map_file "map.txt"
#define info_file "info_test.txt"