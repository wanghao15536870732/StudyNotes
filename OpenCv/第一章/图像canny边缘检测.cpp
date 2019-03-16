#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, int argv)
{
    //载入图像
    Mat srcImage = imread("D:\\Desktop\\pic.jpg");
    if (srcImage.empty())
    {
        cout << "can not find the img" << endl;
    }
    //显示原始图
    imshow("【原图】Canny边缘检测", srcImage);
    Mat edge, greyImage; //参数定义

    //【1】将原图像转换为灰度图像
    cvtColor(srcImage, greyImage, CV_BGR2GRAY);

    //【2】先使用3×3内核来降噪
    blur(greyImage, edge, Size(3, 3));

    //【3】运行Canny算子
    Canny(edge, edge, 3, 9, 3);

    //【4】显示效果图
    imshow("均值滤波【效果图】", edge);

    waitKey(0); //等待任意按键按下
    return 0;
}