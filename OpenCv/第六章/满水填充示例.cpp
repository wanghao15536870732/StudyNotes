#include "opencv2/core/core.hpp""
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

//全局变量声明
Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage; //原始图、目标图、灰度图、掩模图
int g_nFillMode = 1; //满水填充的模式
int g_nLowDifference = 20, g_nUpDifference = 20; //负差最大值、正差最大值
int g_nConnectivity = 4;  //floodFill()函数标识符低八位的连通值
bool g_bIsColor = true;  //是否为彩色图的标识符
bool g_bUseMask = false;  //是否显示掩模窗口
int g_nNewMaskVal = 255;  //新的重绘窗口的像素值

//鼠标消息的回调函数
static void onMouse(int event, int x, int y, int, void*)
{
	//若鼠标左键没有按下，便返回
	if (event != EVENT_LBUTTONDOWN)
		return;
	//参数准备过程
	Point seed = Point(x,y);
	//空范围的满水填充
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;

	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;

	//标识符的0~7位为g_nConnectivity,8~15位为g_nNewMaskVal左移8位的值;16~23位为FLOODFILL_FIXED_RANGE或者0
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

	//随机生成bgr值
	int b = (unsigned)theRNG() & 255; //随即返回一个0~255之间的值
	int g = (unsigned)theRNG() & 255; //随即返回一个0~255之间的值
	int r = (unsigned)theRNG() & 255; //随即返回一个0~255之间的值
	Rect ccomp;  //定义重绘区域的最小边界矩形区域

	//在重绘区域像素的新值，若是彩色模式，取Scalar(b,g,r);若是灰度图模式，取Scalar(r*0.299 + g * 0.587 + b * 0.114)
	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g * 0.587 + b * 0.114);

	//目标图的赋值
	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;

	int area;

	//调用FloodFIll()函数
	if (g_bUseMask)
	{
		threshold(g_maskImage, g_maskImage, 1, 128, THRESH_BINARY);

		area = floodFill(dst, g_maskImage, seed, newVal, &ccomp,
			Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference,UpDifference,UpDifference), flags);
		imshow("mask", g_maskImage);
	}
	else
	{
		area = floodFill(dst,seed,newVal,&ccomp,Scalar(UpDifference,UpDifference,UpDifference),
			Scalar(UpDifference,UpDifference,UpDifference),flags);
	}
	imshow("效果图", dst);
	cout << area << "个像素值被重绘" << endl;
}

int main()
{
	//D:\\Desktop\\picture\\img_nice.jpg  D:\\Desktop\\lena.jpg
	g_srcImage = imread("D:\\Desktop\\lena.jpg");
	if (!g_srcImage.data) {
		cout << "读取srcImage错误" << endl;
		return false;
	}
	g_srcImage.copyTo(g_dstImage);  //复制源图到目标图
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);  //转换三通道的image0到灰度图
	g_maskImage.create(g_srcImage.rows + 2, g_srcImage.cols + 2, CV_8UC1);  //利用image0的尺寸来初始化掩模mask

	namedWindow("效果图", WINDOW_AUTOSIZE);

	//创建Trackbar
	createTrackbar("负差最大值","效果图",&g_nLowDifference,255,0);
	createTrackbar("正差最大值","效果图",&g_nUpDifference,255,0);

	//鼠标回调函数
	setMouseCallback("效果图",onMouse,0);
	
	//循环轮询按键
	while (1)
	{
		//先显示效果图
		imshow("效果图", g_bIsColor ? g_dstImage : g_grayImage);

		//获取键盘按键
		int c = waitKey(0);
		//判断ESC是否按下
		if ((c & 255) == 27)
		{
			cout << "程序退出......." << endl;
			break;
		}
		//根据按键的不同，进行各种操作
		switch ((char) c)
		{
		case '1':  //键盘按键'1'用于在灰度图与彩色图之间切换
			if (g_bIsColor)  //若原来为彩色，转为灰度图，并将掩模mask所有元素设置为0
			{
				cout << "键盘'1'按下，切换为彩色/灰度模式，当前操作为将【彩色模式】切换为【灰度模式】" << endl;
				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
				g_maskImage = Scalar::all(0);  //将mask的所有元素设置为0
				g_bIsColor = false;  //将标识符置为false,当前为灰度
			}
			else  //若原来为灰度图，便将原来的彩色图image0再次复制给image,并将mask所有元素置为0
			{
				cout << "键盘'1'按下，切换为彩色/灰度模式，当前操作为将【灰度模式】切换为【彩色模式】" << endl;
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true; //将标识符置为false,当前为彩色
			}
			break;
		case '2':  //键盘'2'用于 显示/隐藏掩模窗口
			if (g_bUseMask)
			{
				destroyWindow("mask");
				g_bUseMask = false;
			}
			else
			{
				namedWindow("mask", 0);
				g_maskImage = Scalar::all(0);
				imshow("mask", g_maskImage);
				g_bUseMask = true;
			}
			break;
		case '3':  //键盘'3'用于恢复原始图像
			cout << "键盘3被按下，恢复原始图像" << endl;
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
			g_maskImage = Scalar::all(0);
			break;
		case '4':  //使用空范围的满水填充
			cout << "使用空范围的满水填充" << endl;
			g_nFillMode = 0;
			break;
		case '5':  //使用渐变、固定范围的满水填充
			cout << "使用渐变、固定范围的满水填充" << endl;
			g_nFillMode = 1;
			break;
		case '6':  //使用渐变、浮动范围的满水填充
			cout << "使用渐变、浮动范围的满水填充" << endl;
			g_nFillMode = 2;
			break;
		case '7':  //操作标志符的低八位使用4位的连接模式
			cout << "操作标志符的低八位使用4位的连接模式" << endl;
			g_nConnectivity = 4;
			break;
		case '8':  //操作标志符的低八位使用8位的连接模式
			cout << "操作标志符的低八位使用8位的连接模式" << endl;
			g_nConnectivity = 8;
			break;
		default:
			break;
		}
	}
	return 0;
}