// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

//#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <sstream>
#include <vector>


using namespace std;
using namespace cv;

// TODO: 在此处引用程序需要的其他头文件
#ifdef _DEBUG
//Debug Mode
  
#pragma comment(lib,"opencv_core243d.lib")
#pragma comment(lib,"opencv_imgproc243d.lib")
#pragma comment(lib,"opencv_highgui243d.lib")
#pragma comment(lib,"opencv_imgproc243d.lib")
#pragma comment(lib,"opencv_objdetect243d.lib")
#else
//Release Mode

#pragma comment(lib,"opencv_core243.lib")
#pragma comment(lib,"opencv_imgproc243.lib")
#pragma comment(lib,"opencv_highgui243.lib")
#pragma comment(lib,"opencv_imgproc243.lib")
#pragma comment(lib,"opencv_objdetect243.lib")
#endif