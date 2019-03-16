#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

bool MultiChannelBlending();

int main(int argc, int argv)
{
    system("color 9F");

    if (MultiChannelBlending())
    {
        cout << "\n运行成功，得出了需要的图像 ！" << endl;
    }
    waitKey(0);
    return 0;
}

//多通道混合实现
bool MultiChannelBlending()
{
    //【0】定义相关变量
    Mat srcImage;
    Mat logoImage;
    vector<Mat> channels;
    Mat imageBlueChannel;

    //蓝色通道部分
    //【1】读入图片
    logoImage = imread("D:\\Desktop\\cat.png", 0);
    srcImage = imread("D:\\Desktop\\lena.jpg");

    if (!logoImage.data)
    {
        cout << "读取logoImage错误！" << endl;
        return false;
    }
    if (!srcImage.data)
    {
        cout << "读取srcImage错误！" << endl;
        return false;
    }

    //【2】把一个3通道图像转换成3个单通道图像
    split(srcImage, channels); //分离彩色通道

    imageBlueChannel = channels.at(0);

    addWeighted(imageBlueChannel(Rect(50, 25, logoImage.cols, logoImage.rows)), 1.0,
                logoImage, 0.5, 0, imageBlueChannel(Rect(50, 25, logoImage.cols, logoImage.rows)));

    //将三个通道重新合并成一个三通道

    merge(channels, srcImage);

    namedWindow("<1>原画 + cat蓝色通道");
    imshow("<1>原画 + cat蓝色通道", srcImage);

    Mat imageGreenChannel;

    //【1】重新读读入图片

    logoImage = imread("D:\\Desktop\\cat.png", 0);
    srcImage = imread("D:\\Desktop\\lena.jpg");

    if (!logoImage.data)
    {
        cout << "读取logoImage错误！" << endl;
        return false;
    }
    if (!srcImage.data)
    {
        cout << "读取srcImage错误！" << endl;
        return false;
    }

    //【2】把一个3通道图像转换成3个单通道图像
    split(srcImage, channels); //分离彩色通道

    imageGreenChannel = channels.at(1);

    addWeighted(imageGreenChannel(Rect(50, 25, logoImage.cols, logoImage.rows)), 1.0,
                logoImage, 0.5, 0, imageGreenChannel(Rect(50, 25, logoImage.cols, logoImage.rows)));

    merge(channels, srcImage);

    namedWindow("<2>原画 + cat绿色通道");
    imshow("<2>原画 + cat绿色通道", srcImage);

    Mat imageRedChannel;

    //【1】重新读读入图片

    logoImage = imread("D:\\Desktop\\cat.png", 0);
    srcImage = imread("D:\\Desktop\\lena.jpg");

    if (!logoImage.data)
    {
        cout << "读取logoImage错误！" << endl;
        return false;
    }
    if (!srcImage.data)
    {
        cout << "读取srcImage错误！" << endl;
        return false;
    }

    //【2】把一个3通道图像转换成3个单通道图像
    split(srcImage, channels); //分离彩色通道

    imageRedChannel = channels.at(2);

    addWeighted(imageRedChannel(Rect(50, 25, logoImage.cols, logoImage.rows)), 1.0,
                logoImage, 0.5, 0, imageRedChannel(Rect(50, 25, logoImage.cols, logoImage.rows)));

    merge(channels, srcImage);

    namedWindow("<3>原画 + cat红色通道");
    imshow("<3>原画 + cat红色通道", srcImage);

    //【1】读入图像
    srcImage = imread("D:\\Desktop\\lena.jpg");
    logoImage = imread("D:\\Desktop\\cat.png");
    if (!srcImage.data)
    {
        cout << "读取srcImage错误" << endl;
        return false;
    }
    if (!logoImage.data)
    {
        cout << "读取logoImage出错" << endl;
        return false;
    }
    //【2】定义一个Mat类型并给其设定ROI区域
    Mat imageROI = srcImage(Rect(50, 25, logoImage.cols, logoImage.rows));

    //【3】加载掩模
    Mat mask = imread("D:\\Desktop\\cat.png", 0);

    //【4】将掩模复制到ROI
    logoImage.copyTo(imageROI, mask);

    //显示结果
    namedWindow("<0>原图");
    imshow("<0>原图", srcImage);
    return true;
}
