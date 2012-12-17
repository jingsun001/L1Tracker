#pragma once
#include "stdafx.h"
#include <map>
#include <time.h>

#define MAX_TEMPLATE 10

class L1Tracker
{
public:
	L1Tracker(Mat &srcImg,Rect &ROI,int seedNums);
	~L1Tracker(void);

	void Next(Mat &frame);	//跟踪下一帧

private:
	void initTargetTemplate(Mat &srcImg,Rect &ROI);	//初始化目标模板	
	void initTrivialTemplate();	//初始化噪音模板
	void initSeed(int seedNums,Rect &ROI);	//初始化随机种子
	void CreateMatrixB();
	Mat getROI(Mat &srcImg,RotatedRect &ROI);	//从给定的框中得到矫正的图像
	vector<Mat*> targetTemplate;	//目标模板
	vector<SparseMat*> trivialTemplate;	//噪声模板
	Mat cFrame;	//当前待处理的图像帧
	SparseMat B;	//B=[Target Trivial -Trivial]
	vector<Point> seeds;	//图像中采样的种子
	double averageV;	//模板平均速率
	Size templateSize;	//模板大小
	int seedNum;	//随机种子数量
	int templateType;	//模板的opencv类型 CV_8UC1
};

