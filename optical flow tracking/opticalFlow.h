#pragma once
#include <opencv_all.h>
class opticalFlow
{
public:
	opticalFlow();
	~opticalFlow();
	//  描述：声明全局函数
	Mat tracking(Mat &frame, Mat &output);
	bool addNewPoints();
	bool acceptTrackedPoint(int i);
private:
	//  描述：声明全局变量
	
	Mat gray;   // 当前图片
	Mat gray_prev;  // 预测图片
	vector<Point2f> points[3];  // point0为特征点的原来位置，point1为特征点的新位置
	vector<Point2f> initial;    // 初始化跟踪点的位置
	vector<Point2f> features;   // 检测的特征
	vector<Point2f> linePoint[500];
	int maxCount = 500; // 检测的最大特征数
	int thresholdDistance = 150;
	int thresholdnum = 5;
	double qLevel = 0.01;   // 特征检测的等级
	double minDist = 10.0;  // 两特征点之间的最小距离
	vector<uchar> status;   // 跟踪特征的状态，特征的流发现为1，否则为0
	vector<float> err;
};

