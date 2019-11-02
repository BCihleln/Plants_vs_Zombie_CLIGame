#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include<windows.h>  
	//控制終端輸出指針之位置、顔色
	//包含了句柄HANDLE類
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