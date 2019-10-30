#include "basic.h"


coordinate operator-(const coordinate& A, const coordinate& B)
{
	return { A.X - B.X,A.Y - B.Y };
}
coordinate operator+(const coordinate& A, const coordinate& B)
{
	return { A.X + B.X,A.Y + B.Y };
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