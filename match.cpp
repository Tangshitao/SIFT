#include"match.h"
using namespace std;
inline double square(double a)
{
	return a*a;
}
double calc_distance(descripter &first, descripter &second)
{
	double distance = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < NUMBER_OF_BIN; k++)
			{
				distance += square(first.hist[i][j][k] - second.hist[i][j][k]);
			}
		}
	}
	return distance;
}
vector<pair<int, int>> match_points(vector<coordinate>&first, vector<coordinate>&second)
{
	vector<pair<int, int>>match;
	for (int i = 0; i < first.size(); i++)
	{
		double closest = 1e64, second_cloest = 1e64;
		int index;
		for (int j = 0; j < second.size(); j++)
		{
			double distance = calc_distance(*first[i].p, *second[j].p);
			if (distance < closest)
			{
				second_cloest = closest;
				closest = distance;
				index = j;
			}
			else if (distance < second_cloest)
			{
				second_cloest = distance;
			}
		}
		if (closest < THRESHOLD_FOR_MATCH*second_cloest)
		{
			match.push_back(make_pair(i, index));
		}
	}
	return match;
}