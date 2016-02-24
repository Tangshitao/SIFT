

#ifndef HEADER
#define HEADER
#include"Header.h"
#endif

#ifndef VECTOR
#define VECTOR
#include<vector>
#endif
#include"scale_space.h"
#include"dog.h"
#include<math.h>
#include<iostream>
#include"generate_interest_points.h"
#include<algorithm>
#include<highgui.hpp>
#include<opencv.hpp>
using namespace std;
using namespace cv;


vector<coordinate>* SIFT(string);