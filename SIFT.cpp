#include"SIFT.h"

vector<coordinate>*SIFT(string name)
{


	
	Mat src = imread(name),gray,gray_64F,gray_normalized, **scale_space ,**dog,**dog_normalized ;
	
	resize(src, src,Size(200,160));
	
	cvtColor(src, gray, CV_BGR2GRAY);
	
	resize(gray, gray, Size(src.cols*2,src.rows*2 ));
	gray.convertTo(gray_64F, CV_64FC1);
	normalize(gray_64F, gray_normalized, 0, 1, NORM_MINMAX);

	GaussianBlur(gray_normalized, gray_normalized, Size(7, 7), sqrt(SIGMA*SIGMA - 1), sqrt(SIGMA*SIGMA - 1));

	scale_space = generate_scale_space(gray_normalized);
	dog = difference_of_gaussian(scale_space);
	
	vector<coordinate>*interest_points = generate_interest_points(dog);
	
	
	for (int i = 0; i < interest_points->size(); i++)
	{
		(*interest_points)[i].p = new descripter();
		int octave = (*interest_points)[i].octave, intval = (*interest_points)[i].intval;
		int x = (*interest_points)[i].x << octave, y = (*interest_points)[i].y << octave;
		x /= 2, y /= 2;
		circle(src, Point(y, x), 5, 0);
		
	}
	imshow(name, src);
	waitKey(0);
	
	for (int i = 0; i < interest_points->size(); i++)
	{
		int octave = (*interest_points)[i].octave, intval =(* interest_points)[i].intval;
		compute_discripter(dog[octave][intval],
			(*interest_points)[i].x, (*interest_points)[i].y, SIGMA*pow(2, intval / S),(*interest_points)[i].p);
	}
	
	return interest_points;

}