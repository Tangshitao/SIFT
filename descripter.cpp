#include"descripter.h"

void compute_discripter(Mat &src, int x, int y, double sigma, descripter *hist)
{
	double main_ori = main_orientation(src, x, y, sigma);
	descripter_construction(src, 4,x,y, sigma, main_ori,hist);
	hist->normalize();
}

double main_orientation(Mat &src, int x, int y, double sigma)
{
	double radius = 3 * sigma, exp_de = sigma*sigma * 2, hist[8] = { 0 };
	for (int i =(int) -radius; i < radius; i++)
	{
		for (int j =(int) -radius; j < radius; j++)
		{
			mag_and_ori temp = calc_mag_and_ori(src, x + i, y + j);
			if (temp.mag != -1)
			{
				int bin=(int)temp.ori*4/PI +0.5;
				hist[bin] += temp.mag*exp(-(i*i + j*j) / exp_de);
			}
		}
	}

	int result=0;
	for (int i = 0; i < 8; i++)
	{
		if (hist[i]>hist[result])
		{
			result = i;
		}
	}
	return (double)result*PI / 4;
}

void descripter_construction(Mat &src, int d,int x,int y, double sigma, double theta,  descripter *hist)
{
	double width = 3*sigma;
	double radius = ((d + 1)*width * sqrt(2) + 1) / 2, exp_de = 0.5*sigma*sigma;
	double sin_theta = sin(theta), cos_theta = cos(theta);
	for (int i = (int)-radius; i < radius; i++)
	{
		for (int j = (int)-radius; j < radius; j++)
		{
			double xx = (i*cos_theta + j*sin_theta) / width+(d-1)/2 , yy = (-i*sin_theta + j*cos_theta) / width + (d-1)/2;
			mag_and_ori temp= calc_mag_and_ori(src, i+x, j+y);
			if (temp.mag<0)
				continue;
			if (x>-1 && x < 1)
			{
				int u = 0;
			}
			temp.ori += theta;
			temp.mag *= exp(-(i*i + j*j) / exp_de);
			while (temp.ori < 0)
			{
				temp.ori += 2 * PI;
			}
			while (temp.ori>2 * PI)
			{
				temp.ori -= 2 * PI;
			}
			assign_val(hist, xx, yy, temp);
		}
	}

}
inline double calc(double val, int mark)
{
	if (mark)
	{
		return 1 - val;
	}
	else
	{
		return val;
	}
}

void assign_val(descripter *hist, double x, double y,mag_and_ori temp)
{
	double bin = temp.ori * 4 / PI + 0.5;
	if (bin > 8)
	{
		bin -= 8;
	}
	int x_floor = floor(x), y_floor = floor(y), bin_floor = floor(bin);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				int xx = x_floor + i, yy = y_floor + j, _bin = bin_floor + k;
				if (_bin == 0)
				{
					int u = 0;
				}
				if (xx >= 0 && xx < 4 && yy >= 0 && yy < 4 && _bin >= 0 && _bin < NUMBER_OF_BIN)
				{
					hist->hist[xx][yy][_bin] += (calc(x - x_floor, i)*calc(y - y_floor, j)*calc(bin - bin_floor, k))*temp.mag;		
				}
			}
		}
	}
}



mag_and_ori calc_mag_and_ori(Mat &src, int x, int y)
{
	double Ix,Iy,mag=-1, ori=-1;

	if (x > 0 && x<src.rows-1&&y>0 && y < src.cols-1)
	{
		Ix = src.at<double>(x + 1, y) - src.at<double>(x - 1, y);
		Iy = src.at<double>(x, y + 1) - src.at<double>(x, y - 1);
		ori = atan(Ix / Iy);
		mag = sqrt(Ix*Ix + Iy*Iy);
	}

	return mag_and_ori(mag, ori);
}

