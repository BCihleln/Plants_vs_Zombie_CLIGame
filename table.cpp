//#include "table.h"
//
//coordinate Table::Screen2Table(coordinate screen_coordinate)
//{
//	coordinate target = screen_coordinate - start_position;
//	target.X /= cell_length;
//	target.Y /= cell_width;
//	return target;
//}
//
//Table::Table(int row_, int column_, coordinate start_position, coordinate cell_size):
//	row(row_),column(column_),
//	start_position(start_position),cell_size(cell_size)
//{
//	table = new void*[row];
//	for (int i = 0; i < row; ++i)
//		table[i] = new void*[column];
//}
//
//Table::~Table()
//{
//	for (int i = 0; i < row; ++i)
//		delete[] table[i];
//	table = NULL;
//}
