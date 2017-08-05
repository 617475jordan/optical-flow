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
	//  ����������ȫ�ֺ���
	Mat tracking(Mat &frame, Mat &output);
	bool addNewPoints();
	bool acceptTrackedPoint(int i);
	double opticalFlow::computeCos(double x0, double y0, double x1, double y1);
private:
	//  ����������ȫ�ֱ���
	
	Mat gray;   // ��ǰͼƬ
	Mat gray_prev;  // Ԥ��ͼƬ
	vector<Point2f> points[2];  // point0Ϊ�������ԭ��λ�ã�point1Ϊ���������λ��
	vector<Point2f> initial;    // ��ʼ�����ٵ��λ��
	vector<Point2f> features;   // ��������
	vector<Point2f> linePoint[5000];
	int maxCount = 5000; // �������������
	int thresholdDistance = 80;
	int thresholdnum = 4;
	double qLevel = 0.01;   // �������ĵȼ�
	double minDist = 1.0;  // ��������֮�����С����
	int kDistance = 150;
	vector<uchar> status;   // ����������״̬��������������Ϊ1������Ϊ0

	bool creatImageFlag = false;
	vector<float> err;
};

