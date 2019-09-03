#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

static void on_ContrastAndBright(int, void *);

int g_nContrastValue; //对比度值
int g_nBrightValue;  //亮度值
Mat g_srcImage, g_dstImage;

int main(int argc, int argv)
{
	g_srcImage = imread("D:\\Desktop\\lena.jpg");
	if (!g_srcImage.data)
	{
		cout << "读取图片错误！" << endl;
		return false;
	}
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	g_nContrastValue = 80;
	g_nBrightValue = 80;

	//创建效果窗口
	namedWindow("【效果图窗口】", 1);

	//创建轨迹条
	createTrackbar("对比度：", "【效果图窗口】",&g_nContrastValue, 300, on_ContrastAndBright);
	createTrackbar("亮  度：", "【效果图窗口】", &g_nBrightValue, 200, on_ContrastAndBright);

	//【5】进行回调函数初始化
	on_ContrastAndBright(g_nContrastValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);

	//按下'q'键时，程序退出
	while (char(waitKey(1)) != 'q') {}

	return 0;
}

static void on_ContrastAndBright(int, void *)
{
	//新建窗口
	namedWindow("【原始图窗口】", 1);
	for (int i = 0; i < g_srcImage.rows; i++)
	{
		for (int j = 0; j < g_srcImage.cols; j++)
		{
			for (int c = 0; c < 3; c++)
			{
				g_dstImage.at<Vec3b>(i, j)[c] = saturate_cast<uchar>
					((g_nContrastValue * 0.01) * g_srcImage.at<Vec3b>(i, j)[c] + g_nBrightValue);
			}
		}
	}
	imshow("【原始图窗口】", g_srcImage);
}