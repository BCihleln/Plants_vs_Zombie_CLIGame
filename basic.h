#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define DEBUG

#include<windows.h>  
	//控制終端輸出指針之位置、顔色
	//包含了句柄HANDLE類
#include <time.h>
	//用於產生精度為毫秒的時鐘
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
bool operator<(const coordinate& A, const coordinate& B);//A處於B的左上角
bool operator<=(const coordinate& A, const coordinate& B);//A處於B的左上角或B點
bool operator>(const coordinate& A, const coordinate& B);//A處於B的右下角
bool operator>=(const coordinate& A, const coordinate& B);//A處於B的右下角或B點
void operator-=(coordinate& A, const coordinate& target);
void operator+=(coordinate& A, const coordinate& target);
#define coordinate_out_of_border coordinate{MAXSHORT,MAXSHORT}

#include "game_info.h"