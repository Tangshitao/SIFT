
#ifndef HEADER
#define HEADER
#include"Header.h"
#endif

#ifndef OPENCV
#define OPENCV
#include<opencv.hpp>
using namespace cv;
#endif


void resize(Mat&, Mat&);

Mat** generate_scale_space(Mat&);