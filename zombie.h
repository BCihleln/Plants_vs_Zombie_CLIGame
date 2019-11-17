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
private:
	int DEF_;//�����~��Ѫ����Ҳ���ǵ��ߵ�Ѫ��
	tool_type tool;

	void Skill();
protected:
	int SPD_;//�Ƅ��ٶ� ��λ���ַ���/��
	coordinate direction_;//ǰ�M����

	void move(coordinate& position);
	void die()override;
public:
	Zombie();
	~Zombie();

	void change_type(tool_type target);

	//���خ�ǰ�r϶��ʬ�Ĺ���������map��̎�������Č���
	int next(int clock,coordinate& position, bool obstacle);
};
