#pragma once
#include "creature.h"

class BULLET :private Creature//�ӏ�����һ�N��������ͻȻ�뵽���}������
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
public:
	BULLET(string name, int attack,short effect);
	~BULLET();

	void next(int clock, coordinate& position);
};