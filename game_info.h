#pragma once

const char version[] = "0.6.0";

enum class plant_ID
{	//TODO �����Ќ����Y�ό���csv�ļ��У������Α�r�xȡ
	None,

	//Buff
	Sun_Flower,
	Nut_Wall,
	Thorns,//�G���ش�
	Garlic,
	Fire_chunk,//����

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

constexpr auto game_speed = 99;//�@�Y��game_speed��game_system�ĕr犕r�L�������������ٶ�