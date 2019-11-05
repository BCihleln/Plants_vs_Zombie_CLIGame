#include "table.h"

template<typename type>
void Table<type>::generate_table()
{
	table = new type * [row];
	for (int i = 0; i < row; ++i)
		table[i] = new type[column];
}

template <typename type>
coordinate Table<type>::Screen2Table(coordinate screen_coordinate)
{
	//橫坐標邊界檢查
	screen_coordinate.X = screen_coordinate.X > start_position.X ? screen_coordinate.X : start_position.X;
	screen_coordinate.X = screen_coordinate.X > table_length ? table_length+start_position.X : screen_coordinate.X;
	//縱坐標邊界檢查
	screen_coordinate.Y = screen_coordinate.Y > start_position.Y ? screen_coordinate.Y : start_position.Y;
	screen_coordinate.Y = screen_coordinate.Y > table_width ? table_width + start_position.Y : screen_coordinate.Y;

	coordinate target = screen_coordinate - start_position;

	target.X /= cell_length;
	target.Y /= cell_width;
	return target;
}

template<typename type>
Table<type>::Table():
	row(1), column(1),
	start_position({0,0}), cell_size({1,1}),
	table_length(column* cell_size.X), table_width(row* cell_size.Y)
{
	generate_table();
}

template <typename type>
Table<type>::Table(int row_, int column_, coordinate start_position, coordinate cell_size):
	row(row_),column(column_),
	start_position(start_position),cell_size(cell_size),
	table_length(column_ * cell_size.X),table_width(row_ * cell_size.Y)
{
	generate_table();
}

template <typename type>
Table<type>::~Table()
{
	for (int i = 0; i < row; ++i)
		delete[] table[i];
	table = NULL;
}