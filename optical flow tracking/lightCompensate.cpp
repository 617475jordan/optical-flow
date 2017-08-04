#include "lightCompensate.h"


lightCompensate::lightCompensate()
{
}


lightCompensate::~lightCompensate()
{
}

/***���ݸ߹�����ֱ��ͼ������й��߲���***/
Mat  lightCompensate::Compensate(Mat dst)
{
	//whiteBalance(dst);
	medianBlur(dst, dst, (3, 3));
	int histogram[256] = { 0 };
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			int b = dst.at<Vec3b>(i, j)[0];
			int g = dst.at<Vec3b>(i, j)[1];
			int r = dst.at<Vec3b>(i, j)[2];
			//����Ҷ�ֵ
			int gray = (r * 299 + g * 587 + b * 113) / 1000;
			histogram[gray]++;
		}
	}
	int calnum = 0;
	int total = dst.rows * dst.cols;
	int num;
	//�����ѭ���õ�����ϵ��thresholdco���ٽ�Ҷȼ�
	for (int i = 0; i < 256; i++)
	{
		if ((float)calnum / total < thresholdco) //�õ�ǰ5%�ĸ������ء�
		{
			calnum += histogram[255 - i];//histogram�������ĳһ�Ҷ�ֵ�����ظ���,calnum�Ǳ߽�Ҷ�֮�ϵ�������
			num = i;
		}
		else
			break;
	}
	int averagegray = 0;
	calnum = 0;
	//�õ����������������ܵĻҶ�ֵ
	for (int i = 255; i >= 255 - num; i--)
	{
		averagegray += histogram[i] * i; //�ܵ����صĸ���*�Ҷ�ֵ
		calnum += histogram[i]; //�ܵ�������
	}
	averagegray /= calnum;
	//�õ����߲�����ϵ��
	alpha = 255.0 / (float)averagegray;//�Աȶ�����
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			dst.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(alpha*dst.at<Vec3b>(i, j)[0] + beta);
			dst.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(alpha*dst.at<Vec3b>(i, j)[1] + beta);
			dst.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(alpha*dst.at<Vec3b>(i, j)[2] + beta);
		}
	}
	return  dst;
}

Mat lightCompensate::whiteBalance(Mat g_srcImage)
{
	//����ͨ��
	split(g_srcImage, g_vChannels);
	Mat imageBlueChannel = g_vChannels.at(0);
	Mat imageGreenChannel = g_vChannels.at(1);
	Mat imageRedChannel = g_vChannels.at(2);

	double imageBlueChannelAvg = 0;
	double imageGreenChannelAvg = 0;
	double imageRedChannelAvg = 0;

	//���ͨ����ƽ��ֵ
	imageBlueChannelAvg = mean(imageBlueChannel)[0];
	imageGreenChannelAvg = mean(imageGreenChannel)[0];
	imageRedChannelAvg = mean(imageRedChannel)[0];

	//�����ͨ����ռ����
	double K = (imageRedChannelAvg + imageGreenChannelAvg + imageRedChannelAvg) / 3;
	double Kb = K / imageBlueChannelAvg;
	double Kg = K / imageGreenChannelAvg;
	double Kr = K / imageRedChannelAvg;

	//���°�ƽ���ĸ�ͨ��BGRֵ
	addWeighted(imageBlueChannel, Kb, 0, 0, 0, imageBlueChannel);
	addWeighted(imageGreenChannel, Kg, 0, 0, 0, imageGreenChannel);
	addWeighted(imageRedChannel, Kr, 0, 0, 0, imageRedChannel);

	merge(g_vChannels, dstImage);//ͼ���ͨ���ϲ�
	return dstImage;
}