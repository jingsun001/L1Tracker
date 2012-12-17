#include "stdafx.h"
#include "L1Tracker.h"



L1Tracker::L1Tracker(Mat &srcImg,Rect &ROI,int seedNums)
{
	averageV=0;
	templateType=srcImg.type();
	templateSize=ROI.size();
	cFrame=srcImg;
	initTargetTemplate(srcImg,ROI);
	initTrivialTemplate();
	initSeed(seedNums,ROI);
}


L1Tracker::~L1Tracker(void)
{
}

void  L1Tracker::Next(Mat &frame)
{
	//计算
}

Mat L1Tracker::getROI(Mat &srcImg,RotatedRect &ROI)
{
	// matrices we'll use
	Mat M, rotated, cropped;
	// get angle and size from the bounding box
	float angle = ROI.angle;
	Size rect_size = ROI.size;
	// thanks to http://felix.abecassis.me/2011/10/opencv-rotation-deskewing/
	if (ROI.angle < -45.) {
		angle += 90.0;
		swap(rect_size.width, rect_size.height);
	}
	// get the rotation matrix
	M = getRotationMatrix2D(ROI.center, angle, 1.0);
	// perform the affine transformation
	warpAffine(srcImg, rotated, M, srcImg.size(), INTER_CUBIC);
	// crop the resulting image
	getRectSubPix(rotated, rect_size, ROI.center, cropped);
	return cropped;
}

//根据用户输入初始化目标模板，分别为原位置，以及8个方向的随机位移构成
void L1Tracker::initTargetTemplate(Mat &srcImg,Rect &ROI)
{
	Rect rect=ROI;
	targetTemplate.push_back(new Mat(srcImg,rect)); //(0,0)
	rect.x+=1;	//(1,0)
	targetTemplate.push_back(new Mat(srcImg,rect));
	rect.y+=1;	//(1,1)
	targetTemplate.push_back(new Mat(srcImg,rect));
	rect.x-=1;	//(0,1)
	targetTemplate.push_back(new Mat(srcImg,rect));
	rect.x-=1;	//(-1,1)
	targetTemplate.push_back(new Mat(srcImg,rect));
	rect.y-=1;	//(-1,0)
	targetTemplate.push_back(new Mat(srcImg,rect));
	rect.y-=1;	//(-1,-1)
	targetTemplate.push_back(new Mat(srcImg,rect));
	rect.x+=1;	//(0,-1)
	targetTemplate.push_back(new Mat(srcImg,rect));
}

void L1Tracker::initTrivialTemplate()
{
	int size[]={templateSize.height,templateSize.width},idx[2];
	for (int i=0;i<templateSize.height;++i)
	{
		idx[0]=i;
		for (int j=0;j<templateSize.width;++j)
		{
			idx[1]=j;
			SparseMat *tmp=new SparseMat(2,size,CV_8UC1);
			tmp->ref<uchar>(idx)=255;
			trivialTemplate.push_back(tmp);
		}
	}

}

//生成种子后，检索窗为以种子为中点的360度旋窗
void L1Tracker::initSeed(int seedNums,Rect &ROI)
{
	int totalPix=(cFrame.cols-templateSize.width/2)*(cFrame.rows-templateSize.height/2);
	seedNum=seedNums>totalPix?totalPix:seedNums;
	//RNG rng1((unsigned)time(0)),rng2((unsigned)time(1));	//利用RNG生成高斯分布N（0,1）的随机数
	//rng1.gaussian(cFrame.rows/2);
	//rng2.gaussian(cFrame.cols/2);
	srand((unsigned)time(0));
	Partical *p;
	int rpos,cpos;
	set<string> tmp;
	string rcpos;
	stringstream ss;
	while (seeds.size()<seedNums)
	{
		rpos=rand()%(cFrame.rows-templateSize.height-1)+templateSize.height/2+1;
		cpos=rand()%(cFrame.cols-templateSize.width-1)+templateSize.width/2+1;
		ss.clear();
		ss<<rpos<<','<<cpos;
		ss>>rcpos;
		if (tmp.find(rcpos)==tmp.end())
		{
			p=new Partical();
			p->roi=new RotatedRect(Point(rpos,cpos),Size(templateSize.width,templateSize.height),0);
			p->scale=1.;
			p->q=0;
			seeds.push_back(*p);
			tmp.insert(rcpos);
			cFrame.at<uchar>(rpos,cpos)=255;
		}
	}
	imshow("",cFrame);
}
