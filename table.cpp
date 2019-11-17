#pragma once
#include "table.h"


template<class type>
void Table<type>::generate_table()
{
	table = new type * [row];
	for (int i = 0; i < row; ++i)
		table[i] = new type[column];
}

//�����Ƿ�̎춽���
template<typename type>
bool Table<type>::check_border(coordinate& screen, bool strong_check) const
{
	if (!strong_check)//���z�飺�����Ԓ�Ƅӵ�����
	{
		//�M����߅��z��
		screen.X = max(start_point.X + 1, screen.X);//��߅��
		screen.X = min(start_point.X + table_length - cell_length, screen.X);//��߅��
		
		//�v����߅��z��
		screen.Y = max(start_point.Y + 1, screen.Y);//��߅��
		screen.Y = min(start_point.Y + table_width - 1, screen.Y);//��߅��
		return true;//����
	}
	else
	{
		//if (screen.X <start_point.X+1 || screen.X > start_point.X + table_length-1 ||
		//	screen.Y < start_point.Y+1 || screen.Y > start_point.Y + table_width-1)
		//{
		//	return false;
		//}
		//else return true;
		if (screen < start_point + table_size && screen >= start_point)
			return true;
		else
			return false;
	}
	return false;//�ǽ��ڣ�����
}


//return {table_row_index, table_column_index}
template <typename type>
coordinate Table<type>::Screen2Table(coordinate screen_coordinate, bool strong_check)const
{
	//TODO ���]������ֵ������������Ч�ʣ��Ͳ���Ҫ���͵��}�u�����N���f��׃����
	//cout << __FUNCTION__ << endl;
	//cout << table_length << "," << table_width << endl;
	//cout << screen_coordinate << endl;

	if (check_border(screen_coordinate, strong_check))//δ�����Ԓ
	{
		coordinate target = screen_coordinate - start_point;
		//cout << target << endl;

		target.X /= cell_length;
		target.Y /= cell_width;
		//cout << "Table coordinate: " << target << endl;
		return coordinate{ target.Y,target.X };
	}
	else
	{
		return coordinate_out_of_border;
	}
}

/*
input {table_row_index, table_column_index}
output {screen_length_index, screen_width_index}
*/
template<typename type>
coordinate Table<type>::Table2Screen(const coordinate& table_coordinate)const
{
	coordinate target =
	{
		table_coordinate.Y * cell_length + (cell_length >> 1),
		table_coordinate.X * cell_width + (cell_width >> 1)
	};

	target = this->start_point+target;
	return target;//���؆�Ԫ��������c
}

template<typename type>
coordinate Table<type>::Screen2Cell_middle(coordinate screen) const
{
	coordinate tmp = Screen2Table(screen, true);
	if (tmp != coordinate_out_of_border)
		return Table2Screen(tmp);
	else
		return screen;
}

template<typename type>
type* Table<type>::select(coordinate screen,bool strong_check) 
{
	coordinate tmp = Screen2Table(screen, strong_check);
	if (tmp != coordinate_out_of_border)
	{
		return &table[tmp.X][tmp.Y];
	}
	else
		return  nullptr;
}

template<typename type>
bool Table<type>::in_table(coordinate screen)
{
	return check_border(screen, true);
}

//template<typename type>
//coordinate Table<type>::table_size() const
//{
//	return coordinate{table_length,table_width};
//}

//template<typename type>
//type Table<type>::Cell(short x, short y)
//{
//	if (x > this->column || y > this->table_row ||
//		x < 0 || y < 0)
//	{
//		cout << "table visit out of range!" << endl;
//		exit(0);
//	}
//	return table[y][x];
//}
//template<typename type>
//type Table<type>::Cell(coordinate target)
//{
//	return Cell(target.X, target.Y);
//}

//template<typename type>
//type& Table<type>::at(short column, short row)
//{
//	if(column>this->column || row > this->table_row ||
//		column <0 || row<0)
//	{
//		cout << "table visit out of range!" << endl;
//		exit(0);
//	}
//	return table[row][column];
//}
//template<typename type>
//type& Table<type>::at(coordinate target)
//{
//	return at(target.X, target.Y);
//}

template<typename type>
Table<type>::Table() :
	row(1), column(1),
	start_point({ 0,0 }), 
	cell_size({ 1,1 }),
	table_size({ column * cell_size.X,row * cell_size.Y })
{
	generate_table();
}

template <typename type>
Table<type>::Table(short row_, short column_, coordinate start_point, coordinate cell_size) :
	row(row_), column(column_),
	start_point(start_point), 
	cell_size(cell_size),
	table_size({ column * cell_size.X,row * cell_size.Y })
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
