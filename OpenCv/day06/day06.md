# 访问图像像素的三类方法

+ 方法一 指针访问：C操作符[];
+ 方法二 迭代器 iterator
+ 方法三 动态地址运算

## 方法一 指针访问：C操作符[]

Mat类属性共有成员变量`cols`和`rows`,而成员函数 `channels()`返回图像的通道数

### 获取每行的像素值

```c
int colNumber = outputImage.cols * outputImage.channels(); //列数×通道数 = 每一行元素的个数
```

### Mat类提供ptr函数得到图像任意行的首地址

```c
uchar* data = outputImage.ptr<uchar>(i); //获取第i行的首地址
```

### 使用指针运算从一列移动到下一列

```c
*data++ = *data / div * div + div / 2;
```

`减少图像颜色的数量`

```c
#include <iostream>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

//全局函数声明
void colorReduce(Mat& inputImage, Mat& outputImage, int div);

int main(int argc, int argv)
{
    //【1】创建原始图并显示
    Mat srcImage = imread("D:\\Desktop\\lena.jpg");
    imshow("原始图像", srcImage);

    //【2】按原始图的参数规格来创建效果图
    Mat dstImage;
    dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());  //效果图大小、类型与原图相同

    //【3】记录起始时间
    double time0 = static_cast<double>(getTickCount());

    //【4】调用颜色空间缩减函数
    colorReduce(srcImage, dstImage, 32);

    //【5】计算时间并输出
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    cout << "此方法运行时间为：" << time0 << "秒" << endl;  //输出运行时间

    //【6】显示效果图
    imshow("效果图",dstImage);
    waitKey(0);
    return 0;
}
```

```c
//【方法一】 用指针访问像素
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
    //参数准备
    outputImage = inputImage.clone(); //复制实参到临时变量
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols * outputImage.channels(); //列数×通道数 = 每一行元素的个数

    //循环遍历
    for (int i = 0; i < rowNumber; i++)
    {
        uchar* data = outputImage.ptr<uchar>(i); //获取第i行的首地址
        for (int j = 0; j < colNumber; j++)
        {
            data[j] = data[j] / div * div + div / 2;
        }
    }
}
```

+ 获取图像矩阵的begin和end。
+ 增加迭代直至从begin到end。
+ 将*操作符添加在迭代指针前，即可访问当前指向的内容。

```c
//【方法二】 用迭代器操作像素
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
    //参数准备
    outputImage = inputImage.clone(); //复制实参到临时变量
    //获取迭代器
    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();  //初始位置的迭代器
    Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();  //终止位置的迭代器

    //存取彩色图像像素
    for (; it != itend; ++it)
    {
        //开始处理每个像素
        (*it)[0] = (*it)[0] / div * div + div / 2;
        (*it)[1] = (*it)[1] / div * div + div / 2;
        (*it)[2] = (*it)[2] / div * div + div / 2;
    }
}
```

```c
//【方法三】 动态地址计算
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
    //参数准备
    outputImage = inputImage.clone(); //复制实参到临时变量
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols; //列数

    //循环遍历
    for (int i = 0; i < rowNumber; i++)
    {
        for (int j = 0; j < colNumber; j++)
        {
            //开始处理每个像素
            outputImage.at<Vec3b>(i,j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2;  //蓝色通道
            outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2;  //绿色通道
            outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2;  //红色通道
        }
    }
}
```