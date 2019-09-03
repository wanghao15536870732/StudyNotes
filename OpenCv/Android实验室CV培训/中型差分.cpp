#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#define WINDOW_NAME "【程序窗口】"

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    /*
	VideoCapture video(0);
	while (true)
	{
		Mat frame;//视频的每一帧
		video >> frame;  //将视频写入每一帧
		cvtColor(frame,frame,COLOR_RGB2GRAY);
		cvNamedWindow("frame", WINDOW_AUTOSIZE);
		imshow("frame",frame);

		waitKey(30); 
	}
	*/

    Mat srcImage = imread("D:\\Desktop\\lena.jpg", 1); //读取图片
    cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);      //转为灰度图像

    namedWindow("srcImage", WINDOW_AUTOSIZE); //新建窗口
    imshow("srcImage", srcImage);             //显示图像
    //waitKey(0);  //图像显示为一帧

    //由于中型差分的原因，输出图像比原始图象少了两列
    Mat dImage = Mat(srcImage.rows, srcImage.cols - 2, CV_8UC1);

    //循环遍历整个图像
    for (int i = 0; i < srcImage.rows; i++)
    {
        for (int j = 1; j < srcImage.cols - 1; j++)
        {
            //对整型数据类型进行运算,进行中型差分
            dImage.at<uchar>(i, j - 1) = srcImage.at<uchar>(i, j + 1) - srcImage.at<uchar>(i, j - 1);
        }
    }
    namedWindow("dImage", WINDOW_AUTOSIZE); //处理后图像窗口
    imshow("dImage", dImage);               //显示处理后的图像

    waitKey(0); //图像显示为一帧
    return 0;
}