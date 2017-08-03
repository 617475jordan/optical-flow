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

// parameter: frame 输入的视频帧
// output 有跟踪结果的视频帧
Mat opticalFlow::tracking(Mat &frame, Mat &output)
{
	cvtColor(frame, gray, CV_BGR2GRAY);
	frame.copyTo(output);

	// 添加特征点
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
	// l-k光流法运动估计
	calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);
	// 去掉一些不好的特征点
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

	// 显示特征点和运动轨迹
	//int  tmp = 0;
	for (size_t i = 0; i < points[1].size(); i++)
	{
		line(output, initial[i], points[1][i], Scalar(0, 0, 255));
		circle(output, points[1][i], 3, Scalar(0, 255, 0), -1);
	}


	// 把当前跟踪结果作为下一此参考
	swap(points[1], points[0]);
	swap(gray_prev, gray);
	return output;
}

// 检测新点是否应该被添加
// return: 是否被添加标志
bool opticalFlow::addNewPoints()
{
	return points[0].size() <= 10;
}

//决定哪些跟踪点被接受
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
