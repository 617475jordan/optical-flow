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
#include "opticalFlow.h"
using namespace std;
using namespace cv;
int thresholdArea = 100;
Mat frame, result;


///-------------------------------------------------------------------------------------------------
/// <summary>	Color convert. </summary>
///
/// <remarks>	Admin, 2017/8/4. </remarks>
///
/// <param name="src"> 	Source for the. </param>
/// <param name="out"> 	The out. </param>
/// <param name="flag">	The flag. </param>
///
/// <returns>	A Mat. </returns>
///-------------------------------------------------------------------------------------------------

Mat colorConvert(Mat src, Mat out, int flag);

int main()
{
	opticalFlow opticalFlow;

	VideoCapture capture;
	capture.open("..\\video\\gesture.avi");
	//capture.open(0);
	if (!capture.isOpened())
	{
		return -1;
	}
	
	Mat tmpFrame, outFrame;
	BackgroundSubtractorMOG2 mog;
	Mat foreground;
	Mat background;

	while (1)
	{
	//char filename[100];

	//for (int i = 1; i <= 539; i++)
	//{
	//	sprintf(filename, "..\\image(li)\\image%d.jpg", i);
	//	frame = imread(filename);
		int t = clock();
		capture >> frame;
		if (frame.empty())
		{
		//	i = 1; 
		//	continue;
			return -1;
		}
		cvtColor(frame, frame, CV_RGBA2GRAY);
		cvtColor(frame, frame, CV_GRAY2RGB);
		//flip(frame, frame, -1);
		//frame = imageEnhancement.SimplestCB(frame,1);
		//frame = lightCompensate.Compensate(frame);
		//frame = lightCompensate.whiteBalance(frame);
		//frame = imageEnhancement.SimplestCB(frame, 1);
		frame.copyTo(tmpFrame);
		frame.copyTo(outFrame);
		outFrame.setTo(0);
		mog(frame, foreground, 0.001);
		// 腐蚀  
		erode(foreground, foreground, cv::Mat());
		// 膨胀  
		//dilate(foreground, foreground, cv::Mat());
		mog.getBackgroundImage(background);   // 返回当前背景图像  
		imshow("for", foreground);
		/*********连通区域查找****************/
		vector<vector<Point>> contours;
		vector<vector<Point>> filterContours;
		vector<Vec4i> hierarchy;
		hierarchy.clear();
		contours.clear();
		filterContours.clear();
		findContours(foreground, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		/*********求面积************/
		vector<vector<Point>> maxContour;
		int flag = -1;
		int maxArea = -1;
		for (size_t a = 0; a < contours.size(); a++)
		{
			double area = cv::contourArea(contours[a]);
			
			if (area >= thresholdArea/*&&area>maxArea*/)
			{
				flag = a;
				//maxArea = area;
				filterContours.push_back(contours[flag]);
			}
		}
		if (flag >= 0)
		{
			
			drawContours(tmpFrame, filterContours, -1, Scalar(255, 255, 255), CV_FILLED);
			outFrame = colorConvert(tmpFrame, outFrame, 1);
			imshow("outFrame", outFrame);

			result = opticalFlow.tracking(outFrame, result);
			frame = colorConvert(result, frame, 2);

			imshow("out", frame);
			waitKey(2);
		}
		else
		{
			imshow("outFrame", outFrame);
			imshow("out", frame);
			waitKey(2);
		}
		cout << "Time is :" << clock() - t << endl;
	}
}

Mat colorConvert(Mat src, Mat out,int flag)
{
	switch (flag)
	{
	case 1:
		for (int i = 0; i < src.rows; i++)
		{
			for (int j = 0; j < src.cols; j++)
			{
				if (src.at<Vec3b>(i, j)[0] == 255 && src.at<Vec3b>(i, j)[1] == 255
					&& src.at<Vec3b>(i, j)[2] == 255)
				{
					out.at<Vec3b>(i, j)[0] = frame.at<Vec3b>(i, j)[0];
					out.at<Vec3b>(i, j)[1] = frame.at<Vec3b>(i, j)[1];
					out.at<Vec3b>(i, j)[2] = frame.at<Vec3b>(i, j)[2];
				}
			}
		}
		break;
	case 2:
		for (int i = 0; i < src.rows; i++)
		{
			for (int j = 0; j < src.cols; j++)
			{
				if (src.at<Vec3b>(i, j)[0] >0 && src.at<Vec3b>(i, j)[1] >0
					&& src.at<Vec3b>(i, j)[2] > 0)
				{
					out.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, j)[0];
					out.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, j)[1];
					out.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, j)[2];
				}
			}
		}
		break;
	default:
		out = src;
		break;
	}
	
	return out;
}



