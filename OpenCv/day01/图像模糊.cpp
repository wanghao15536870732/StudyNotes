#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

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
    imshow("均值滤波【原图】",srcImage);
    //进行均值滤波操作
    Mat dstImage;
    //使用7×7内核来降噪
    blur(srcImage, dstImage, Size(7, 7));
    //显示效果图
    imshow("均值滤波【效果图】",dstImage);
    waitKey(0);  //等待任意按键按下
    return 0;
}