#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main()
{
    /*
	//【1】从摄像头读入视频
	VideoCapture capture(0);

	//【2】循环显示每一帧
	while (1)
	{
		//【1】读入图像
		Mat frame; //定义一个Mat变量，用于储存每一帧的图像
		capture >> frame;  //读取当前帧
		threshold(frame, frame, 255,255, CV_THRESH_BINARY);
		
		Mat dstImage = Mat::zeros(frame.rows, frame.cols, CV_8UC3);

		//定义轮廓和层次结构
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		findContours(frame, contours, hierarchy, RETR_CCOMP,CHAIN_APPROX_SIMPLE);

		int index = 0;
		for (; index >= 0; index = hierarchy[index][0])
		{
			Scalar color(rand() & 255, rand() & 255, rand() & 255);
			drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
		}
		imshow("轮廓图", dstImage); //显示当前帧
		if (waitKey(30) >= 0) break;  //延时30秒
	}*/
    Mat frame = imread("D:\\Desktop\\lena.jpg", 0);
    imshow("【原始图】", frame);
    Mat dstImage = Mat::zeros(frame.rows, frame.cols, CV_8UC3);

    frame = frame > 119;
    imshow("【取阈值后的图像】", frame);
    //定义轮廓和层次结构
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(frame, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    int index = 0;
    for (; index >= 0; index = hierarchy[index][0])
    {
        Scalar color(rand() & 255, rand() & 255, rand() & 255);
        drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
    }
    imshow("轮廓图", dstImage); //显示当前帧
    waitKey(0);
    return 0;
}
