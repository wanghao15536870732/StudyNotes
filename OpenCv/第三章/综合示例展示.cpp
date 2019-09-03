#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    //图像的载入和使用
    Mat girl = imread("D:\\Desktop\\girl.jpg"); //载入图像到Mat
    namedWindow("【1】动漫图");                 //创建一个名为"【1】动漫图"的窗口
    imshow("【1】动漫图", girl);                //显示窗口

    //初级图像混合
    Mat background = imread("D:\\Desktop\\back.png", 199);
    Mat cat = imread("D:\\Desktop\\cat.jpg");

    //载入后先显示
    namedWindow("【2】背景图");
    imshow("【2】背景图", background);

    namedWindow("【3】小猫图");
    imshow("【3】小猫图", cat);

    //定义一个Mat类型，用于存放图像的ROI
    Mat imageROI;

    //方法一
    imageROI = background(Rect(800, 350, cat.cols, cat.rows));

    //将cat加到gril上
    addWeighted(imageROI, 0.5, cat, 0.3, 0., imageROI);

    //显示结果
    namedWindow("【4】cat + gril");
    imshow("【4】猫加上女孩", background);

    //输出图片到指定工程目录下
    imwrite("D:\\Desktop\\由imwrite生成的图片.jpg", background);

    waitKey(); //等待键盘输入
    return 0;
}