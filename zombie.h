#pragma once
#include "basic.h"
#include "creature.h"


enum class tool_type
{
	None,
	Flag,
	Barrel, Bucket,
	Newspaper,
	Dancer_King
};

//���߹������_���У�ÿ�r϶ֻ�܈�������һ��
class Zombie:public Creature
{
	int
		SPD_,//�Ƅ��ٶ� ��λ���ַ���/��
		DEF_;//���~��Ѫ����Ҳ���ǵ��ߵ�Ѫ��
	coordinate direction;//ǰ�M����

	tool_type tool;

	void Skill();
	void move(coordinate& position);
public:
	Zombie();
	~Zombie();

	void change_type(tool_type target);

	//���خ�ǰ�r϶��ʬ�Ĺ���������map��̎�������Č���
	int next(int clock,coordinate& position, bool obstacle);
};
