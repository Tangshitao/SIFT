#include"SIFT.h"
#include"match.h"
#include<vector>


int main()
{
	std::vector<coordinate>*first = SIFT("key1.jpg"), *second = SIFT("key2.jpg");
	std::vector<pair<int, int>> matching_point = match_points(*first,*second);
	cout << matching_point.size();
	return 0;
}