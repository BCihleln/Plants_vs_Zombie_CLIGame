#pragma once

#include "basic.h"

template <typename type>
class Table
{
	/*
	�����N��
	���߅�����O��
	*/

	const short row;//����Д�
	const short column;//����Д�

	const coordinate start_point;
	const coordinate cell_size;//{width , length}
#define cell_width cell_size.Y
#define cell_length cell_size.X

	//type* the_chosen_one;//ӳ�������چ�Ԫ��
	const coordinate table_size;
#define table_width table_size.Y
#define table_length table_size.X
	
	friend coordinate operator-(const coordinate& A, const coordinate& B);
	friend coordinate operator+(const coordinate& A, const coordinate& B);
	friend ostream& operator<<(ostream& out, const coordinate& target);
	friend bool operator==(const coordinate& A, const coordinate& B);
	friend bool operator!=(const coordinate& A, const coordinate& B);
	friend bool operator<(const coordinate& A, const coordinate& B);//A̎�B�����Ͻ�
	friend bool operator<=(const coordinate& A, const coordinate& B);//A̎�B�����Ͻǻ�B�c
	friend bool operator>(const coordinate& A, const coordinate& B);//A̎�B�����½�
	friend bool operator>=(const coordinate& A, const coordinate& B);//A̎�B�����½ǻ�B�c

	void generate_table();
	//���z������L����Ԫ��֮ģ����z������x���Ԫ��
	bool check_border(coordinate& screen, bool strong_check)const ;
protected:
	type** table;
public:

	/*
	intput coordinate{row_index, column_index} 
	make sure you input a valid table coordinate
	*/
	type& operator[](const coordinate& target)const
	{
		if (target < coordinate{0, 0} || target > coordinate{row, column})//check border
		{
			system("cls");
			cout << "Told you check coordinate before using this Function!" << endl;
			exit(0);
		}
		return table[target.X][target.Y];
	}
	////�@�Æ�Ԫ���ڔ���
	//type Cell(short x, short y);
	//type Cell(coordinate target);

	Table();
	Table(short row_, short column_, coordinate start_position, coordinate cell_size);
	~Table();


	//���،�����Ԫ����е���Ļ����
	coordinate Table2Screen(const coordinate& table_coordinate)const ;
	//���؂�����Ļ�����������Æ�Ԫ�񣬾��к����Ļ����
	coordinate Screen2Cell_middle(coordinate screen)const;
	//���،����ı������
	coordinate Screen2Table(coordinate screen_coordinate, bool strong_check)const;

	//������Ļ�����x���Ԫ�񣬌��x��Y������the_chosen_one
	type* select(coordinate screen,bool strong_check);

	//coordinate table_size()const ;

	//�z����Ļ�����Ƿ��춱��
	bool in_table(coordinate screen);
	
	//column �� row ��
	//type& at(short column, short row);
	//type& at(coordinate target);
};