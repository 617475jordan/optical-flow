#pragma once
#include <opencv_all.h>
class lightCompensate
{
public:
	lightCompensate();
	~lightCompensate();
public:
	Mat  Compensate(Mat dst);
	Mat whiteBalance(Mat g_srcImage);
public:
	const double thresholdco = 0.1;
	const int thresholdnum = 100;
	const int threshold = 128;
	double beta = 0.5;
	double alpha; 
public:
	Mat dstImage;
	vector<Mat> g_vChannels;
};

