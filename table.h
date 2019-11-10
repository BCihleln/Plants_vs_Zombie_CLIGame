#pragma once

#include "basic.h"

template <typename type>
class Table
{
	const short row;//表格行數
	const short column;//表格列數

	const coordinate start_point;
	const coordinate cell_size;//{width , length}
#define cell_width cell_size.Y
#define cell_length cell_size.X

	void generate_table();

	/*
	行有餘力
	添加邊框厚度設定
	*/

protected:
	type** table;
	type* the_chosen_one;//映射光標所在單元格
	const coordinate table_size;
#define table_width table_size.Y
#define table_length table_size.X
	//const int table_length, table_width;

	//強檢查用於訪問單元格之類的，弱檢查用於選擇單元格
	bool check_border(coordinate& screen, bool strong_check)const ;
	//返回對應的表格坐標
	coordinate Screen2Table(coordinate screen_coordinate, bool strong_check)const;
	//virtual void init();

	friend coordinate operator-(const coordinate& A, const coordinate& B);
	friend coordinate operator+(const coordinate& A, const coordinate& B);
	friend ostream& operator<<(ostream& out, const coordinate& target);
	friend bool operator==(const coordinate& A, const coordinate& B);
	friend bool operator!=(const coordinate& A, const coordinate& B);
	friend bool operator<(const coordinate& A, const coordinate& B);//A處於B的左上角
	friend bool operator<=(const coordinate& A, const coordinate& B);//A處於B的左上角或B點
	friend bool operator>(const coordinate& A, const coordinate& B);//A處於B的右下角
	friend bool operator>=(const coordinate& A, const coordinate& B);//A處於B的右下角或B點


public:

	Table();
	Table(short row_, short column_, coordinate start_position, coordinate cell_size);
	~Table();


	//返回對應單元格居中的屏幕坐標
	coordinate Table2Screen(coordinate table_coordinate)const ;
	coordinate Screen2Cell_middle(coordinate screen)const;

	//根據屏幕坐標選擇單元格，將選擇結果存入the_chosen_one
	void select(coordinate screen,bool strong_check);

	//coordinate table_size()const ;

	//檢查屏幕坐標是否屬於表格
	bool in_table(coordinate screen);

	//獲得單元格内數據
	type Cell(short x,short y);
	type Cell(coordinate target);

	//column 行 row 列
	//type& at(short column, short row);
	//type& at(coordinate target);
};