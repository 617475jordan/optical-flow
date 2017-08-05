#pragma once
#include "opencv2/opencv.hpp"
#include "opencv2/core/internal.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/legacy/compat.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv/highgui.h"
#include <ctime>
#include <time.h>
#include <math.h>
#include <iostream>
#include <ostream>
#include <cmath>
using namespace std;
using namespace cv;
double   const   PI = acos(double(-1));
class opticalFlow
{
public:
	opticalFlow();
	~opticalFlow();
	//  描述：声明全局函数
	Mat tracking(Mat &frame, Mat &output);
	bool addNewPoints();
	bool acceptTrackedPoint(int i);
	double opticalFlow::computeCos(double x0, double y0, double x1, double y1);
private:
	//  描述：声明全局变量
	
	Mat gray;   // 当前图片
	Mat gray_prev;  // 预测图片
	vector<Point2f> points[2];  // point0为特征点的原来位置，point1为特征点的新位置
	vector<Point2f> initial;    // 初始化跟踪点的位置
	vector<Point2f> features;   // 检测的特征
	vector<Point2f> linePoint[5000];
	int maxCount = 5000; // 检测的最大特征数
	int thresholdDistance = 80;
	int thresholdnum = 4;
	double qLevel = 0.01;   // 特征检测的等级
	double minDist = 1.0;  // 两特征点之间的最小距离
	int kDistance = 150;
	vector<uchar> status;   // 跟踪特征的状态，特征的流发现为1，否则为0

	bool creatImageFlag = false;
	vector<float> err;
};

