#pragma once
#include "basic.h"
//#include "map.h"

class Creature
{
protected:
	string name_;
	int
		HP_,
		ATK_, ATK_SPD_,//ATK Speed ���� ��λ����/��
		SPD_,//�Ƅ��ٶ� ��λ���ַ���/��
		DEF_;//�ٷֱȷ��R�����99%

	//coordinate ATK_direction;
	coordinate direction;//ǰ�M����
public:

	//Creature();
	Creature(string name);
	//~Creature();

	//string get_name();

	//virtual void move(coordinate& position);

	//virtual void attack();

	//����ӏ�����ʬǰ�M
	//bool check_obstacle(const mapCell& front);

	void injure(int damage);
	void die();

	//virtual void next(int clock,coordinate& position);
};