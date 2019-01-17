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
    //显示图像
    imshow("【原图】腐蚀操作",srcImage);
    //进行腐蚀操作
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    Mat dstImage;
    erode(srcImage, dstImage,element);
    //显示效果图
    imshow("【效果图】腐蚀操作",dstImage);
    waitKey(0);  //等待任意按键按下
    return 0;
}