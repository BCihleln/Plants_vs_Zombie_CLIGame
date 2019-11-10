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
	//A是否在B的左上角(以B點爲原點的第一象限)
	if (A.X <= B.X && A.Y <= B.Y)
		return true;
	else
		return false;
}

bool operator>(const coordinate& A, const coordinate& B)
{
	//A在B的右下角
	if (A.X > B.X && A.Y > B.Y)
		return true;
	else
		return false;
}
bool operator>=(const coordinate& A, const coordinate& B)
{
	//A是否在B的右下角（以B點為原點的第三象限）
	if (A.X >= B.X && A.Y >= B.Y)
		return true;
	else
		return false;
}