#pragma once
#include <opencv_all.h>
class opticalFlow
{
public:
	opticalFlow();
	~opticalFlow();
	//  ����������ȫ�ֺ���
	Mat tracking(Mat &frame, Mat &output);
	bool addNewPoints();
	bool acceptTrackedPoint(int i);
private:
	//  ����������ȫ�ֱ���
	
	Mat gray;   // ��ǰͼƬ
	Mat gray_prev;  // Ԥ��ͼƬ
	vector<Point2f> points[3];  // point0Ϊ�������ԭ��λ�ã�point1Ϊ���������λ��
	vector<Point2f> initial;    // ��ʼ�����ٵ��λ��
	vector<Point2f> features;   // ��������
	vector<Point2f> linePoint[500];
	int maxCount = 500; // �������������
	int thresholdDistance = 150;
	int thresholdnum = 5;
	double qLevel = 0.01;   // �������ĵȼ�
	double minDist = 10.0;  // ��������֮�����С����
	vector<uchar> status;   // ����������״̬��������������Ϊ1������Ϊ0
	vector<float> err;
};

