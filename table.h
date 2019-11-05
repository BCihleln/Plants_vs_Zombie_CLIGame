#pragma once

#include "basic.h"

template <typename type>
class Table
{
	const int row;//����Д�
	const int column;//����Д�

	const coordinate start_position;
	const coordinate cell_size;//{width , length}
#define cell_width cell_size.Y
#define cell_length cell_size.X

	void generate_table();

protected:
	type** table;
	type* the_chosen_one;//ӳ�������چ�Ԫ��
	const int table_length, table_width;
	coordinate Screen2Table(coordinate screen_coordinate);

public:
	Table();
	Table(int row_, int column_, coordinate start_position, coordinate cell_size);
	~Table();

	type& operator[](int target)
	{
		if (target > max(row,column))
		{
			cout << "Reading table out of Range!\n";
			exit(0);
		}
		return table[target];
	}//���d[]��ֱ��ȡ�Æ�Ԫ�񔵓�
};