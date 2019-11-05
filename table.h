#pragma once

#include "basic.h"

template <typename type>
class Table
{
	const int row;//表格行數
	const int column;//表格列數

	const coordinate start_position;
	const coordinate cell_size;//{width , length}
#define cell_width cell_size.Y
#define cell_length cell_size.X

	void generate_table();

protected:
	type** table;
	const int table_length, table_width;

	//virtual void init();

public:
	Table();
	Table(int row_, int column_, coordinate start_position, coordinate cell_size);
	~Table();

	coordinate Screen2Table(coordinate screen_coordinate);

	//type& operator[](int target)
	//{
	//	if (target > max(row,column))
	//	{
	//		cout << "Reading table out of Range!\n";
	//		exit(0);
	//	}
	//	return table[target];
	//}//重載[]來直接取得單元格數據
};