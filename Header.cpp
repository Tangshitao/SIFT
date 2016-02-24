#ifndef HEADER
#define HEADER
#include"Header.h"
#endif
int total1 = 0,total2=0;
coordinate::coordinate(){ intval =octave= -1; p = nullptr; }
coordinate::coordinate(int _x, int _y) :x(_x), y(_y)
{
	intval=octave = -1;
	p = nullptr;
}

coordinate::~coordinate(){ 
	delete p;
}
bool coordinate::operator<(coordinate a)const
{
	if (a.x != x)
		return x < a.x;
	return y < a.y;

}
bool coordinate::operator==(coordinate a)const
{
	if (a.x == x&&a.y == y)
		return 1;
	return 0;
}

descripter::descripter()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < NUMBER_OF_BIN; k++)
			{
				hist[i][j][k] = 0;
			}
		}
	}
}

descripter::~descripter()
{
}

void descripter::normalize()
{
	double _max = -1e64, _min = 1e64;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < NUMBER_OF_BIN; k++)
			{
				if (hist[i][j][k]>_max)
				{
					_max = hist[i][j][k];
				}
				if (hist[i][j][k] < _min)
				{
					_min = hist[i][j][k];
				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < NUMBER_OF_BIN; k++)
			{
				hist[i][j][k] = (hist[i][j][k] - _min) / (_max - _min);
			}
		}
	}
}
mag_and_ori::mag_and_ori(){}
mag_and_ori::mag_and_ori(double _mag, double _ori) :mag(_mag), ori(_ori)
{}