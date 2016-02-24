#ifndef HEADER
#define HEADER
#include"Header.h"
#endif

#ifndef OPENCV
#define OPENCV
#include<opencv.hpp>
using namespace cv;
#endif

#ifndef MATH
#define MATH
#include<math.h>
#endif


mag_and_ori calc_mag_and_ori(Mat &, int, int);

void descripter_construction(Mat &, int,int,int,double, double,descripter *);

double main_orientation(Mat&, int, int, double);

void compute_discripter(Mat &, int, int, double, descripter *);

void assign_val(descripter *, double, double, mag_and_ori);
