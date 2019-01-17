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
    Mat src = imread("D:\\Desktop\\pic.jpg");
    if (src.empty())
    {
        cout << "can not find the img" << endl;
    }
    //显示图像
    imshow("【原始图】",src);
    waitKey(0); //等待任意按键按下
    return 0;
}