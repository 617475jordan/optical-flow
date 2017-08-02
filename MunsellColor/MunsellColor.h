#pragma once
#include <opencv_all.h>

//��������ɫϵͳ�Ŀռ���³�һ��Բ���Σ�
//�ϱ��� = ���ȣ�value������ȫ�ڣ�1����ȫ�ף�10����
//���� = ɫ�ࣨhue������һ�ܾ��ֳ�������ɫ���������м�ɫ����(R)�����(YR)����(Y)������(GY)����(G)��
// ����(BG)����(B)������(PB)����(P)���Ϻ�(RP)�����ڵ�����λ��֮���پ���10�ݣ���100�ݡ�
// 
//����ľ��� = ɫ�ȣ�chroma������ʾɫ���Ĵ��ȡ�����ֵ���м䣨0����������ɫ���Ĵ������ӣ�
// û�������ϵ����ޣ���ͨ����ɫʵ������Ϊ10���ң����⡢ӫ��Ȳ��Ͽɸߴ�30����
// �������۶Ը�����ɫ�ĵ����жȲ�ͬ��ɫ�Ȳ�һ����ÿ��ɫ�������������ƥ�䡣
//������ɫ�ı�ʶ��ʽΪ��ɫ�� + ���� + ɫ��
class MunsellColor
{
public:
	MunsellColor();
	~MunsellColor();
public:
	void makecolorwheel(vector<Scalar> &colorwheel);
	void motionToColor(Mat flow, Mat &color);
	Mat run(Mat src);
private:
	Mat prevgray, gray, flow,  frame;
	Mat motion2color;
#define UNKNOWN_FLOW_THRESH 1e9  
};