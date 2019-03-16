#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#define WINDOW_WIDTH 600 //定义窗口大小的宏
#define WINDOW_NAME1 "【绘制图1】"
#define WINDOW_NAME2 "【绘制图2】"

using namespace std;
using namespace cv;

/*
自定义的绘图函数，实现不同角度、相同尺寸的椭圆
@param img 图像
@param angle 椭圆角度
*/
void DrawEllipse(Mat img, double angle)
{
    int thickness = 2;
    int lineType = 8;

    ellipse(img,
            Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), //椭圆的中心点
            Size(WINDOW_WIDTH / 8, WINDOW_WIDTH / 32), //大小位于矩形[WINDOW_WIDTH / 4, WINDOW_WIDTH / 16]内
            angle,                                     //旋转角度
            0,                                         //扩展开始弧度
            360,                                       //扩展结束弧度
            //Scalar(255, 129, 0),  //图像颜色，代表蓝色
            Scalar(0, 0, 255), //红色
            thickness,         //线的宽度
            lineType);         //线的类型
}

void DrawEllipse2(Mat img, double angle)
{
    int thickness = 2;
    int lineType = 8;

    ellipse(img,
            Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), //椭圆的中心点
            Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 8),  //大小位于矩形[WINDOW_WIDTH / 4, WINDOW_WIDTH / 16]内
            angle,                                     //旋转角度
            0,                                         //扩展开始弧度
            360,                                       //扩展结束弧度
            Scalar(0, 0, 255),                         //红色
            thickness,                                 //线的宽度
            lineType);                                 //线的类型
}

/*
自定义的绘图函数，实现实心圆的绘制
@param img 图像
@param center 圆心
*/
void DrawFilledCircle(Mat img, Point center)
{
    int thickness = -1;
    int lineType = 8;
    circle(img,
           center,
           WINDOW_WIDTH / 64, //圆的半径
           Scalar(0, 0, 255), //图像颜色 红色
           thickness,         //线的宽度
           lineType);         //线的类型
}

/*
自定义的绘图函数，实现凹多边形的绘制
*/

void DrawPolygon(Mat img)
{
    int lineType = 8;
    //创建一些点
    Point rookPoints[1][20];
    rookPoints[0][0] = Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
    rookPoints[0][1] = Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
    rookPoints[0][2] = Point(3 * WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
    rookPoints[0][3] = Point(11 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
    rookPoints[0][4] = Point(19 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
    rookPoints[0][5] = Point(3 * WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
    rookPoints[0][6] = Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
    rookPoints[0][7] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
    rookPoints[0][8] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
    rookPoints[0][9] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
    rookPoints[0][10] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
    rookPoints[0][11] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
    rookPoints[0][12] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
    rookPoints[0][13] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
    rookPoints[0][14] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
    rookPoints[0][15] = Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
    rookPoints[0][16] = Point(WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
    rookPoints[0][17] = Point(13 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
    rookPoints[0][18] = Point(5 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
    rookPoints[0][19] = Point(WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);

    const Point *ppt[1] = {rookPoints[0]}; //定义一个指针数组
    int npt[] = {20};

    fillPoly(img,
             ppt,                   //多边形的顶点集
             npt,                   //多边形的顶点数目
             1,                     //多边形数量为1
             Scalar(255, 255, 255), //图像颜色  白色
             lineType);             //线的类型
}

/*
自定义的绘图函数，实现线的绘制
*/
void DrawLine(Mat img, Point start, Point end)
{
    int thickness = 2;
    int lineType = 8;
    line(img,
         start,           //线的顶端
         end,             //线的末端
         Scalar(0, 0, 0), //线的颜色 黑色
         thickness,
         lineType);
}

int main(int argc, int argv)
{

    /*

	//创建空白的Mat图像
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	//【1.1】先绘制出椭圆
	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);
	DrawEllipse2(atomImage, 0);

	//【1.2】再绘制圆心
	DrawFilledCircle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));

	//【2.1】先绘制出多边形
	DrawPolygon(rookImage);

	//【2.2】绘制矩形
	rectangle(rookImage,
		Point(0, 7 * WINDOW_WIDTH / 8),
		Point(WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar(0, 255, 255),
		-1,
		8);

	//【2.3】绘制一些线段
	DrawLine(rookImage, Point(0, 15 * WINDOW_WIDTH / 16),Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 4,7 * WINDOW_WIDTH / 8),Point(WINDOW_WIDTH / 4,WINDOW_WIDTH));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 2, 7 * WINDOW_WIDTH / 8),Point(WINDOW_WIDTH / 2,WINDOW_WIDTH));
	DrawLine(rookImage, Point(3 * WINDOW_WIDTH / 4,7 * WINDOW_WIDTH / 8),Point(3 * WINDOW_WIDTH / 4,WINDOW_WIDTH));


	//【3】显示图像
	imshow(WINDOW_NAME1, atomImage);
	moveWindow(WINDOW_NAME1, 0, 200);
	imshow(WINDOW_NAME2, rookImage);
	moveWindow(WINDOW_NAME2, WINDOW_WIDTH, 200);
	waitKey(0);


	*/

    /*
	//【1】从摄像头读入视频
	VideoCapture capture(0);
	Mat edges;

	//【2】循环显示每一帧
	while (1)
	{
		//【1】读入图像
		Mat frame; //定义一个Mat变量，用于储存每一帧的图像
		capture >> frame;  //读取当前帧

		//【2】将原图像转换为灰度图
		cvtColor(frame, edges, COLOR_BGR2GRAY);  //转化RGB彩色图为灰度图

		//【3】使用3×3内核来降噪(2×3+1=7)
		blur(edges, edges, Size(7, 7));

		//【4】进行canny边缘检测并显示
		Canny(edges, edges, 0, 30, 3);

		imshow("被canny后的视频", edges); //显示当前帧
		if (waitKey(30)
		>= 0) break;  //延时30秒
	}

	*/

    return 0;
}