#include"generate_interest_points.h"

bool is_extrema(Mat *src, int intval, int x, int y)
{
	double val = src[intval].at<double>(x, y);
	if (val > 0)
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				for (int k = -1; k < 2; k++)
				{
					if (val < src[intval + i].at<double>(x + j, y + k))
					{
						return 0;
					}
				}
			}
		}
	}
	else
	{
		for(int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				for (int k = -1; k < 2; k++)
				{
					if (val > src[intval + i].at<double>(x + j, y + k))
					{
						return 0;
					}
				}
			}
		}
	}
	return 1; 
}
vector<coordinate>* generate_interest_points(Mat **src)
{
	int total = 0;
	vector<coordinate>*result = new vector<coordinate>;
	for (int i = 0; i < OCTAVE; i++)
	{
		for (int j = 1; j <= S; j++)
		{			
			for (int x = 1; x < src[i][j].rows-1; x++)
			{
				for (int y = 1; y < src[i][j].cols-1; y++)
				{
					
					if (is_extrema(src[i],j,x,y))
					{
						total++;
						coordinate temp = location_implot(src[i], x, y, j);
						temp.intval = j;
						temp.octave = i;
						if (temp.x != -1)
						{
							result->push_back(temp);
						}
					}
				}
			}
		}
	}
	
	
	return result;
}

coordinate location_implot(Mat*dog_normalized,int x,int y, int index,int max_step)
{
	
	Mat Hessian(3, 3, CV_64FC1), Dervative(3, 1, CV_64FC1);
	double dx, dy, ds, dx2, dy2, dxdy, dxds, dyds, ds2;
	int rows = dog_normalized[0].rows, cols = dog_normalized[0].cols;

	

	while (max_step--&&index>0&&index<=S&&x>0&&x<rows-1&&y>0&&y<cols-1)
	{

		dx = (dog_normalized[index].at<double>(x + 1, y) - dog_normalized[index].at<double>(x - 1, y)) / 2;
		dy = (dog_normalized[index].at<double>(x, y + 1) - dog_normalized[index].at<double>(x, y - 1)) / 2;
		ds = (dog_normalized[index + 1].at<double>(x, y) - dog_normalized[index - 1].at<double>(x, y)) / 2;
		dx2 = (-2 * dog_normalized[index].at<double>(x, y) + dog_normalized[index].at<double>(x + 1, y) 
			+ dog_normalized[index].at<double>(x - 1, y));
		dy2 = (-2 * dog_normalized[index].at<double>(x, y) + dog_normalized[index].at<double>(x , y+1)
			+ dog_normalized[index].at<double>(x, y - 1));
		ds2 = (-2 * dog_normalized[index].at<double>(x, y) + dog_normalized[index+1].at<double>(x, y)
			+ dog_normalized[index - 1].at<double>(x, y));
		dxdy = (dog_normalized[index].at<double>(x - 1, y - 1) + dog_normalized[index].at<double>(x + 1, y + 1)
			- dog_normalized[index].at<double>(x + 1, y - 1) - dog_normalized[index].at<double>(x - 1, y + 1)) / 4;
		dxds = (dog_normalized[index + 1].at<double>(x + 1, y) + dog_normalized[index - 1].at<double>(x - 1, y)
			- dog_normalized[index - 1].at<double>(x + 1, y) + dog_normalized[index + 1].at<double>(x - 1, y)) / 4;
		dyds = (dog_normalized[index + 1].at<double>(x, y + 1) + dog_normalized[index - 1].at<double>(x, y - 1)
			- dog_normalized[index + 1].at<double>(x, y - 1) - dog_normalized[index - 1].at<double>(x, y + 1)) / 4;

		Hessian.at<double>(0, 0) = dx2;
		Hessian.at<double>(0, 1) = dxdy;
		Hessian.at<double>(0, 2) = dxds;
		Hessian.at<double>(1, 0) = dxdy;
		Hessian.at<double>(1, 1) = dy2;
		Hessian.at<double>(1, 2) = dyds;
		Hessian.at<double>(2, 0) = dxds;
		Hessian.at<double>(2, 1) = dyds;
		Hessian.at<double>(2, 2) = ds2;
		Dervative.at<double>(0, 0) = dx;
		Dervative.at<double>(1, 0) = dy;
		Dervative.at<double>(2, 0) = ds;

		/*for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << inv.at<double>(i, j) << ' ';
			}
			cout << endl;
		}*/
		Mat X= Hessian.inv()*Dervative;
		double delta_x = X.at<double>(0, 0), delta_y = X.at<double>(1, 0), delta_s = X.at<double>(2, 0);

		if (abs(delta_x) < 0.5&&abs(delta_y) < 0.5&&abs(delta_s) < 0.5)
		{
			double o = dog_normalized[index].at<double>(x, y);
			double DX =  o+0.5*(delta_x*dx+delta_y*dy+delta_s*ds), det = dx2*dy2 - dxdy*dxdy, trace = dx2 + dy2;
			int r = 10;

			if (abs(DX)>0.03/S&&trace*trace/det<(double)(r + 1)*(r + 1)/r)
			{
				return coordinate(x, y);
			}
			else
			{
				return coordinate(-1, -1);
			}
		}

		if (abs(delta_x)>0.5)
		{
			x += round(delta_x);
		}
		if (abs(delta_y)>0.5)
		{
			y+=round(delta_y);
		}
		if (abs(delta_s) > 0.5)
		{
			index += round(delta_s);
		}
	}
	
	return coordinate(-1, -1);
}
