#include "map.h"

MAP::MAP()
{
	for (int i = 0; i < width;++i)
	{
		for (int j = 0; j < length;++j)
		{
			map[i][j] = { NULL,NULL,false };
		}
	}
}
