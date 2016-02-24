#ifndef OPENCV
#define OPENCV

#include<opencv.hpp>
using namespace cv;

#endif

#ifndef HEADER
#define HEADER

#include"Header.h"

#endif

#ifndef VECTOR
#define VECTOR

#include<vector>

#endif

#include"descripter.h"
using namespace std;

vector<coordinate>* generate_interest_points(Mat **);

coordinate location_implot(Mat*, int, int, int,int =5);

