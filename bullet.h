#pragma once
#include "creature.h"
#include "zombie.h"

class Bullet :public Zombie//�ӏ�����һ�N��������ͻȻ�뵽���}������
{	//TODO���^��Zombie
	//�ӏ��������ڵ؈D��й���
	
	short effect;//�ӏ���ɵ�Ч����̖
		/*
		0: �o����Ч��
		1: �p�٣����ǃ��Y������ȵȣ�
		2: ���ף��oҕ���R��
		3: ����
		4: ���m�����������ж��������ȵȣ�
		5: ���
		����
		*/

	int hit();
public:
	Bullet(string name, int attack,short effect);
	~Bullet();

	//void next(int clock, coordinate& position);
};