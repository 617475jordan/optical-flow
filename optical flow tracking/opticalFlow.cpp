#include "opticalFlow.h"


opticalFlow::opticalFlow()
{
	points[0].clear();
	points[1].clear();
	points[2].clear();
	initial.clear();
	features.clear();
	status.clear();
	err.clear();
}


opticalFlow::~opticalFlow()
{
	points[0].clear();
	points[1].clear();
	points[2].clear();
	initial.clear();
	features.clear();
	status.clear();
	err.clear();
}

// parameter: frame �������Ƶ֡
// output �и��ٽ������Ƶ֡
Mat opticalFlow::tracking(Mat &frame, Mat &output)
{
	cvtColor(frame, gray, CV_BGR2GRAY);
	frame.copyTo(output);

	// ���������
	if (addNewPoints())
	{
		goodFeaturesToTrack(gray, features, maxCount, qLevel, minDist);
		points[0].insert(points[0].end(), features.begin(), features.end());
		initial.insert(initial.end(), features.begin(), features.end());
	}

	if (gray_prev.empty())
	{
		gray.copyTo(gray_prev);
	}
	// l-k�������˶�����
	calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);
	// ȥ��һЩ���õ�������
	int k = 0,linek=0;
	for (size_t i = 0; i < points[1].size(); i++)
	{
		if (acceptTrackedPoint(i))
		{
			initial[k] = initial[i];
			points[1][k] = points[1][i];
			k++;
		/*	while (linek>k)
			{
				linePoint[linek].pop_back();
				linek--;
			}
			
			k++;*/
			//cout << "i:" << i << endl;
		}
		//linek++;
	}
	points[1].resize(k);
	initial.resize(k);

	// ��ʾ��������˶��켣
	//int  tmp = 0;
	for (size_t i = 0; i < points[1].size(); i++)
	{
		line(output, initial[i], points[1][i], Scalar(0, 0, 255));
		circle(output, points[1][i], 3, Scalar(0, 255, 0), -1);
	}


	// �ѵ�ǰ���ٽ����Ϊ��һ�˲ο�
	swap(points[1], points[0]);
	swap(gray_prev, gray);
	return output;
}

// ����µ��Ƿ�Ӧ�ñ����
// return: �Ƿ���ӱ�־
bool opticalFlow::addNewPoints()
{
	return points[0].size() <= 10;
}

//������Щ���ٵ㱻����
bool opticalFlow::acceptTrackedPoint(int i)
{
	int count = 0;
	bool flag = false;
	for (int k = i + 1; k<points[1].size()-1; k++)
	{
		double width = abs(points[1][i].x - points[1][i + 1].x);
		double height = abs(points[1][i].y - points[1][i + 1].y);
		double sum = width*width + height*height;
		sum = sqrt(sum);
		if (sum <= thresholdDistance)
			count++;
	}
	if (count >= thresholdnum)
	{
		flag = true;
	}
	//cout << "flag" << flag << endl;
	return status[i] && ((abs(points[0][i].x - points[1][i].x) + abs(points[0][i].y - points[1][i].y)) > 2) && flag;
}
