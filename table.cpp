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
		screen.X = max(start_point.X + 1, screen.X);//��߅��z��
		screen.X = min(start_point.X + table_length - cell_length, screen.X);//��߅��z��
		
		//�v����߅��z��
		screen.Y = max(start_point.Y + 1, screen.Y);//��߅��z��
		screen.Y = min(start_point.Y + table_width - 1, screen.Y);//��߅��z��
		return true;//����
	}
	else
	{
		if (screen.X <start_point.X+1 || screen.X > start_point.X + table_length-1 ||
			screen.Y < start_point.Y+1 || screen.Y > start_point.Y + table_width-1)
		{
			return false;
		}
		else return true;
	}
	return false;//�ǽ��ڣ�����
}

template <typename type>
coordinate Table<type>::Screen2Table(coordinate screen_coordinate, bool strong_check)const
{
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
		return target;
	}
	else
	{
		return coordinate_out_of_border;
	}
}

template<typename type>
coordinate Table<type>::Table2Screen(coordinate table_coordinate)const
{
	coordinate target =
	{
		table_coordinate.X * cell_length + (cell_length >> 1),
		table_coordinate.Y * cell_width + (cell_width >> 1)
	};

	target = this->start_point+target;
	return target;//���؆�Ԫ��������c
}

template<typename type>
type Table<type>::Cell(short x, short y)
{
	return table[y][x];
}
template<typename type>
type Table<type>::Cell(coordinate target)
{
	return Cell(target.X, target.Y);
}

template<typename type>
Table<type>::Table() :
	row(1), column(1),
	start_point({ 0,0 }), cell_size({ 1,1 }),
	table_length(column* cell_size.X), table_width(row* cell_size.Y)
{
	generate_table();
}

template <typename type>
Table<type>::Table(int row_, int column_, coordinate start_point, coordinate cell_size) :
	row(row_), column(column_),
	start_point(start_point), cell_size(cell_size),
	table_length(column_* cell_size.X), table_width(row_* cell_size.Y)
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
