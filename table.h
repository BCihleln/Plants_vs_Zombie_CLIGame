#pragma once

#include "basic.h"

template <typename type>
class Table
{
	const int row;//����Д�
	const int column;//����Д�

	const coordinate start_point;
	const coordinate cell_size;//{width , length}
#define cell_width cell_size.Y
#define cell_length cell_size.X

	void generate_table();

protected:
	type** table;
	type* the_chosen_one;//ӳ�������چ�Ԫ��
	const int table_length, table_width;
	
	//virtual void init();

public:
	Table();
	Table(int row_, int column_, coordinate start_position, coordinate cell_size);
	~Table();

	//���z������L����Ԫ��֮ģ����z������x���Ԫ��
	bool check_border(coordinate& screen, bool strong_check)const ;
	coordinate Screen2Table(coordinate screen_coordinate,bool strong_check)const ;
	coordinate Table2Screen(coordinate table_coordinate)const ;


	//�@�Æ�Ԫ���ڔ���
	type Cell(short x,short y);
	type Cell(coordinate target);
};