


const int NUMBER_OF_BIN = 8, OCTAVE=6, S=3;
const double PI=3.1415926,SIGMA=1.6,THRESHOLD_FOR_MATCH=0.5;
extern int total1, total2;
struct descripter
{
	double hist[4][4][NUMBER_OF_BIN];
	descripter();
	~descripter();
	void normalize();
};
struct coordinate
{
	int x, y, intval,octave;
	descripter *p;
	coordinate();
	coordinate(int, int);
	~coordinate();
	bool operator<(coordinate)const;
	bool operator==(coordinate)const;
};



struct mag_and_ori
{
	double mag, ori;
	mag_and_ori();
	mag_and_ori(double, double);
};