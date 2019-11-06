#pragma once

#include "basic.h"

template <typename type>
class Table
{
	const int row;//表格行數
	const int column;//表格列數

	const coordinate start_point;
	const coordinate cell_size;//{width , length}
#define cell_width cell_size.Y
#define cell_length cell_size.X

	void generate_table();

protected:
	type** table;
	type* the_chosen_one;//映射光標所在單元格
	const int table_length, table_width;
	
	//virtual void init();

public:
	Table();
	Table(int row_, int column_, coordinate start_position, coordinate cell_size);
	~Table();

	//強檢查用於訪問單元格之類的，弱檢查用於選擇單元格
	bool check_border(coordinate& screen, bool strong_check)const ;
	coordinate Screen2Table(coordinate screen_coordinate,bool strong_check)const ;
	coordinate Table2Screen(coordinate table_coordinate)const ;


	//獲得單元格内數據
	type Cell(short x,short y);
	type Cell(coordinate target);
};