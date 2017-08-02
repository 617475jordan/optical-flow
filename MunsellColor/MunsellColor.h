#pragma once
#include <opencv_all.h>

//孟塞尔颜色系统的空间大致成一个圆柱形：
//南北轴 = 明度（value），从全黑（1）到全白（10）。
//经度 = 色相（hue）。把一周均分成五种主色调和五种中间色：红(R)、红黄(YR)、黄(Y)、黄绿(GY)、绿(G)、
// 绿蓝(BG)、蓝(B)、蓝紫(PB)、紫(P)、紫红(RP)。相邻的两个位置之间再均分10份，共100份。
// 
//距轴的距离 = 色度（chroma），表示色调的纯度。其数值从中间（0）向外随着色调的纯度增加，
// 没有理论上的上限（普通的颜色实际上限为10左右，反光、荧光等材料可高达30）。
// 由于人眼对各种颜色的的敏感度不同，色度不一定与每个色调和明度组合相匹配。
//具体颜色的标识形式为：色相 + 明度 + 色度
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