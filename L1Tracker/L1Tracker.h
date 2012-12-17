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

	void Next(Mat &frame);	//������һ֡

private:
	void initTargetTemplate(Mat &srcImg,Rect &ROI);	//��ʼ��Ŀ��ģ��	
	void initTrivialTemplate();	//��ʼ������ģ��
	void initSeed(int seedNums,Rect &ROI);	//��ʼ���������
	void CreateMatrixB();
	Mat getROI(Mat &srcImg,RotatedRect &ROI);	//�Ӹ����Ŀ��еõ�������ͼ��
	vector<Mat*> targetTemplate;	//Ŀ��ģ��
	vector<SparseMat*> trivialTemplate;	//����ģ��
	Mat cFrame;	//��ǰ�������ͼ��֡
	SparseMat B;	//B=[Target Trivial -Trivial]
	vector<Point> seeds;	//ͼ���в���������
	double averageV;	//ģ��ƽ������
	Size templateSize;	//ģ���С
	int seedNum;	//�����������
	int templateType;	//ģ���opencv���� CV_8UC1
};

