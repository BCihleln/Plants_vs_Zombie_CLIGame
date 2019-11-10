#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define DEBUG

#include<windows.h>  
	//���ƽK��ݔ��ָ�֮λ�á��ɫ
	//�����˾��HANDLE�
#include <time.h>
	//��춮a�����Ȟ����ĕr�
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

typedef COORD coordinate;
coordinate operator-(const coordinate& A, const coordinate& B);
coordinate operator+(const coordinate& A, const coordinate& B);
ostream& operator<<(ostream& out, const coordinate& target);
bool operator==(const coordinate& A, const coordinate& B);
bool operator!=(const coordinate& A, const coordinate& B);
bool operator<(const coordinate& A, const coordinate& B);//A̎�B�����Ͻ�
bool operator<=(const coordinate& A, const coordinate& B);//A̎�B�����Ͻǻ�B�c
bool operator>(const coordinate& A, const coordinate& B);//A̎�B�����½�
bool operator>=(const coordinate& A, const coordinate& B);//A̎�B�����½ǻ�B�c
void operator-=(coordinate& A, const coordinate& target);
void operator+=(coordinate& A, const coordinate& target);
#define coordinate_out_of_border coordinate{MAXSHORT,MAXSHORT}

#include "game_info.h"