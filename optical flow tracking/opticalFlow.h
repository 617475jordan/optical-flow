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

