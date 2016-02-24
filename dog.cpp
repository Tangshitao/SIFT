#include"dog.h"

Mat** difference_of_gaussian(Mat **src)
{
	Mat **result = new Mat*[OCTAVE];
	for (int i = 0; i < OCTAVE; i++)
	{
		result[i] = new Mat[S+2];
		for (int j = 0; j < S+2; j++)
		{
			subtract(src[i][j+ 1], src[i][j],result[i][j]);
		}
		
	}
	return result;
}