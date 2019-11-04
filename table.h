#pragma once

#include "basic.h"

class Table
{
	const int row;//表格行數
	const int column;//表格列數

	const coordinate start_position;
	const coordinate cell_size;//{width , length}
#define cell_width cell_size.Y
#define cell_length cell_size.X
protected:
	void** table;
	coordinate Screen2Table(coordinate screen_coordinate);

public:
	Table(int length,int width,coordinate start_position,coordinate cell_size);
	~Table();

	void* operator[](int target)
	{
		if (target > max(row,column))
		{
			cout << "Reading table out of Range!\n";
			exit(0);
		}
		return table[target];
	}//重載[]來直接取得單元格數據
};