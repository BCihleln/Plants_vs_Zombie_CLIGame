#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include<windows.h>  
	//���ƽK��ݔ��ָ�֮λ�á��ɫ
	//�����˾��HANDLE�
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#define coordinate COORD
coordinate operator-(const coordinate& A, const coordinate& B);
coordinate operator+(const coordinate& A, const coordinate& B);
ostream& operator<<(ostream& out, const coordinate& target);
bool operator==(const coordinate& A, const coordinate& B);
bool operator!=(const coordinate& A, const coordinate& B);