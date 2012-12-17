#include "stdafx.h"
#include "L1Tracker.h"

#define MAX_SEEDS 600

bool check_line_state=false,isInit=false;
Point p1,p2;  
Mat oriFrame,cFrame;	//oriFrame为原彩色图，cFrame为灰度图
L1Tracker *tracker=NULL;

static void onMouse(int event,int x,int y,int flag,void* param)
{
	if(!isInit)
	{
		if(event==CV_EVENT_LBUTTONDOWN)  
		{  
			//当前鼠标位置（x，y）  
			p1=p2=Point(x,y); 
			check_line_state=true;  
		}  
		else if(check_line_state&&event==CV_EVENT_MOUSEMOVE)//鼠标状态  
		{  
			//Mat workFrame;
			//workFrame=cFrame.clone();
			p2=Point(x,y);  
		}  
		else if(check_line_state&&event==CV_EVENT_LBUTTONUP)  
		{  
			Rect rect(p1.x,p1.y,abs(p2.x-p1.x),abs(p2.y-p1.y));
			tracker=new L1Tracker(cFrame,rect,MAX_SEEDS);
			isInit=true;
			p1=p2=Point_<int>(0,0);
			check_line_state=false;  
		}  
	}
}

int main( int argc, char** argv ) { 
	VideoCapture cap;
	if (argc==1)
		cap.open(0); // open the default camera
	else
		cap.open(*(new string((char *)argv)));
	if(!cap.isOpened()) 
		return -1;
	namedWindow("Frame",WINDOW_AUTOSIZE);
#ifdef USELESS
	double lastTime=getTickCount(),nowTime;
	double oneSecTick=getTickFrequency();
	int cout=0;
	stringstream ss;
	string fps;
#endif // USELESS
	setMouseCallback("Frame",onMouse,0);
	while(waitKey(30)!=27)
	{	
#ifdef USELESS

		nowTime=getTickCount();
		++cout;
		if ((nowTime-lastTime)>=oneSecTick)
		{
			ss<<(int)(((double)cout/(nowTime-lastTime))*oneSecTick);
			ss>>fps;
			if (fps=="")
				fps='0';
			lastTime=nowTime;
			cout=0;
		}
#endif
		cap.read(oriFrame); 
		cvtColor(oriFrame,cFrame,CV_RGB2GRAY);
		if (isInit)	//开始跟踪用户选择的目标
		{
			imshow("Frame", oriFrame);
		}else	//等待用户选择跟踪目标
		{
			if (!check_line_state)
				imshow("Frame", oriFrame);
			else
			{
				rectangle(oriFrame,p1,p2,CV_RGB(255,0,0),2,CV_AA,0);  
				imshow("Frame",oriFrame); 
			}
		}
	}
	destroyWindow("Frame");
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
