#include "basic.h"


coordinate operator-(const coordinate& A, const coordinate& B)
{
	return { A.X - B.X,A.Y - B.Y };
}
void operator-=(coordinate& A, const coordinate& target)
{
	A.X -= target.X;
	A.Y -= target.Y;
}
coordinate operator+(const coordinate& A, const coordinate& B)
{
	return { A.X + B.X,A.Y + B.Y };
}
void operator+=(coordinate& A, const coordinate& target)
{
	A.X += target.X;
	A.Y += target.Y;
}
ostream& operator<<(ostream& out, const coordinate& target)
{
	out << "{" << target.X << "," << target.Y << "}";
	return out;
}
bool operator==(const coordinate& A, const coordinate& B)
{
	if (A.X == B.X && A.Y == B.Y)
		return true;
	else
		return false;
}
bool operator!=(const coordinate& A, const coordinate& B)
{
	return !(A == B);
}

bool operator<(const coordinate& A, const coordinate& B)
{
	if (A.X < B.X && A.Y < B.Y)
		return true;
	else
		return false;
}
bool operator<=(const coordinate& A, const coordinate& B)
{
	//A�Ƿ���B�����Ͻ�(��B�c��ԭ�c�ĵ�һ����)
	if (A.X <= B.X && A.Y <= B.Y)
		return true;
	else
		return false;
}

bool operator>(const coordinate& A, const coordinate& B)
{
	//A��B�����½�
	if (A.X > B.X && A.Y > B.Y)
		return true;
	else
		return false;
}
bool operator>=(const coordinate& A, const coordinate& B)
{
	//A�Ƿ���B�����½ǣ���B�c��ԭ�c�ĵ������ޣ�
	if (A.X >= B.X && A.Y >= B.Y)
		return true;
	else
		return false;
}