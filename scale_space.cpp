#include"scale_space.h"

void resize(Mat &src, Mat &dst)
{
	int rows = src.rows, cols = src.cols, new_rows = rows + 1 >> 1, new_cols = cols + 1 >> 1;
	dst = Mat(new_rows, new_cols, CV_64FC1);
	for (int i = 0; i < new_rows; i++)
	{
		for (int j = 0; j < new_cols; j++)
		{
			dst.at<double>(i, j) = src.at<double>(i * 2, j * 2);
		}
	}
}

Mat** generate_scale_space(Mat &src)
{
	Mat **result =new  Mat*[OCTAVE];
	double *sigma = new double[S+3], k = pow(2, 1.0 / S);
	sigma[0] = SIGMA;
	sigma[1] = sigma[0] * sqrt(k*k - 1);
	for (int i = 2; i < S + 3; i++)
	{
		sigma[i] = sigma[i - 1] * k;
	}
	for (int i = 0; i < OCTAVE; i++)
	{
		
		result[i] = new Mat[S+3];
		if (i == 0)
		{
			result[i][0] = src;
		}
		else
		{
			resize(result[i - 1][S], result[i][0]);
		}
		for (int j = 1; j < S+3; j++)
		{
			GaussianBlur(result[i][j - 1], result[i][j], Size(7, 7), sigma[j], sigma[j]);
		}
	}
	delete []sigma;
	return result;
}

