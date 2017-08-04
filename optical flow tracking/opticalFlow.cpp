#include "opticalFlow.h"


opticalFlow::opticalFlow()
{
	points[0].clear();
	points[1].clear();
	
	initial.clear();
	features.clear();
	status.clear();
	err.clear();
}


opticalFlow::~opticalFlow()
{
	points[0].clear();
	points[1].clear();
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
	int k = 0;
	for (size_t i = 0; i < points[1].size(); ++i)
	{
		bool  flagTmp;
		flagTmp = acceptTrackedPoint(i);
		//cout << "i:" << i << endl;
		//cout << "flag:" << flag << endl;
		if (flagTmp)
		{
			initial[k] = initial[i];
			//cout << "i:" << i << endl;
			//cout << "initial.x" << initial[k].x << " " << "initial.y"<<initial[k].x << endl;
			points[1][k] = points[1][i];
			linePoint[k] = linePoint[i];
			linePoint[k].push_back(points[1][k]);
			++k;
			
		}
	}
	points[1].resize(k);
	initial.resize(k);
	
	RNG rng(time(0));
	
	for ( int i = 0; i < k; i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//line(output, initial[i], points[1][i], color);
		if (linePoint[i].size() >= 8)
		{
			double width = abs(initial[i].x - linePoint[i][0].x);
			double height = abs(initial[i].y - linePoint[i][0].y);
			double distance = width*width + height*height;

			distance = sqrt(distance);
			if (distance>kDistance)
			{
				continue;
			}
			int countFlag = 0;
			for (int j = 0; j < linePoint[i].size() - 1; j++)
			{
				double width = abs(linePoint[i][j].x - linePoint[i][j+1].x);
				double height = abs(linePoint[i][j].y - linePoint[i][j + 1].y);
				double distance = width*width + height*height;

				distance = sqrt(distance);
				if (distance <= kDistance)
				{
					countFlag++;
				}
			}
			if (linePoint[i].size() - 1 == countFlag)
			{
				//cout << "Num is " << i << endl;
				line(output, initial[i], linePoint[i][0], color);
				//	cout << "X:" << initial[i].x << " " << "Y:" << initial[i].y << endl;
				circle(output, initial[i], 3, Scalar(0, 255, 0), -1);
				for (unsigned int j = 0; j < linePoint[i].size() - 1; j++)
				{
					line(output, linePoint[i][j], linePoint[i][j + 1], color,2);
					circle(output, linePoint[i][j], 3, Scalar(0, 255, 0), -1);

					//	cout << "X:" << linePoint[i][j].x << " " << "Y:" << linePoint[i][j].y<< endl;
				}
			}

		}	
	}

	// �ѵ�ǰ���ٽ����Ϊ��һ�˲ο�
	points[0].clear();
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
	double width ;
	double height;
	double sum ;
	double distance;
	for (unsigned int k = i+1; k<points[1].size()-1; k++)
	{
		width = abs(points[1][i].x - points[1][k].x);
		height = abs(points[1][i].y - points[1][k].y);
		sum = width*width + height*height;
		sum = sqrt(sum);
		
		if (sum <= thresholdDistance)
			count++;
	}
	if (count >= thresholdnum)
	{
		flag = true;
	}
	width = abs(points[0][i].x - points[1][i].x);
	height = abs(points[0][i].y - points[1][i].y);
	distance = width*width + height*height;

	distance = sqrt(distance);

	if (status[i] == 1 && (distance >= 4) && (distance <= kDistance)&& flag == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}



