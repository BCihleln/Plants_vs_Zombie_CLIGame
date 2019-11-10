#pragma once

#include "basic.h"

template <typename type>
class Table
{
	const short row;//����Д�
	const short column;//����Д�

	const coordinate start_point;
	const coordinate cell_size;//{width , length}
#define cell_width cell_size.Y
#define cell_length cell_size.X

	void generate_table();

	/*
	�����N��
	���߅�����O��
	*/

protected:
	type** table;
	type* the_chosen_one;//ӳ�������چ�Ԫ��
	const coordinate table_size;
#define table_width table_size.Y
#define table_length table_size.X
	//const int table_length, table_width;

	//���z������L����Ԫ��֮ģ����z������x���Ԫ��
	bool check_border(coordinate& screen, bool strong_check)const ;
	//���،����ı������
	coordinate Screen2Table(coordinate screen_coordinate, bool strong_check)const;
	//virtual void init();

	friend coordinate operator-(const coordinate& A, const coordinate& B);
	friend coordinate operator+(const coordinate& A, const coordinate& B);
	friend ostream& operator<<(ostream& out, const coordinate& target);
	friend bool operator==(const coordinate& A, const coordinate& B);
	friend bool operator!=(const coordinate& A, const coordinate& B);
	friend bool operator<(const coordinate& A, const coordinate& B);//A̎�B�����Ͻ�
	friend bool operator<=(const coordinate& A, const coordinate& B);//A̎�B�����Ͻǻ�B�c
	friend bool operator>(const coordinate& A, const coordinate& B);//A̎�B�����½�
	friend bool operator>=(const coordinate& A, const coordinate& B);//A̎�B�����½ǻ�B�c


public:

	Table();
	Table(short row_, short column_, coordinate start_position, coordinate cell_size);
	~Table();


	//���،�����Ԫ����е���Ļ����
	coordinate Table2Screen(coordinate table_coordinate)const ;
	coordinate Screen2Cell_middle(coordinate screen)const;

	//������Ļ�����x���Ԫ�񣬌��x��Y������the_chosen_one
	void select(coordinate screen,bool strong_check);

	//coordinate table_size()const ;

	//�z����Ļ�����Ƿ��춱��
	bool in_table(coordinate screen);

	//�@�Æ�Ԫ���ڔ���
	type Cell(short x,short y);
	type Cell(coordinate target);

	//column �� row ��
	//type& at(short column, short row);
	//type& at(coordinate target);
};