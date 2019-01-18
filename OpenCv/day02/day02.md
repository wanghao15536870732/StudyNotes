# Continue CV

## 1.调用摄像头采集图像

```c++
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
        cvtColor(frame,edges,COLOR_BGR2GRAY);  //转化RGB彩色图为灰度图

        //【3】使用3×3内核来降噪(2×3+1=7)
        blur(edges, edges, Size(7, 7));

        //【4】进行canny边缘检测并显示
        Canny(edges, edges, 0, 30, 3);

        imshow("被canny后的视频",edges); //显示当前帧
        if (waitKey(30) >= 0) break;  //延时30秒
    }
    return 0;
}
```

![ng](https://upload-images.jianshu.io/upload_images/9140378-21aa8e19be20b46f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/440)

## 2.Mat类简析

Mat类是用于保存图像以及其他矩阵数据的数据结构

```c++
Mat srcImage = imread("dota.jpg");
```

这表示从指定路径下的图片载入到Mat类型的srcImage变量当中

`图像的载入：imread()函数`

函数的原型

```c++
Mat imread(const string& filename,int flags = 1);
```

+ 第一个参数，const string&类型的filename,填写我们需要载入到图片路径
+ 第二个参数：int 类型的flags,为载入标值，他指定一个图像的颜色类型，自带默认值1
  + flags > 0 返回一个3通道的彩色图像
  + falgs = 0 返回灰度图像
  + flags < 0 返回包含Alpha通道的加载图像

`图像的显示：imshow()函数`

函数的原型

```c++
void imshow(const strings& winname,intoutArray mat);
```

+ 第一个参数：const string& 类型的winname,填需要显示的窗口的标识名称
+ 第二个参数：ImputArray类型的mat,填需要显示的图像

`创建窗口：namedWindow()函数`

namedWindow()函数用于创建一个窗口，如是简单的显示图片就可以忽略掉这个函数，但是要在显示窗口之前显示窗口名时，就会用到该函数

函数的原型

```c++
void namedWindow(const string& winname,int flags=WINDOW_AUTOSIZE);
```

+ 第一个参数：const string&类型的name，表示窗口名称
+ 第二个参数：int 类型的flags,窗口的标识
  + WINDOW_NORMAL 用户可以改变窗口的大小。
  + WINDOW_AUTOSIZE 窗口会自动调整以适应所显示的图像。
  + WINDOW_OPENGL 窗口创建的时候会支持OpenGL。

`输出图像到文件`

函数的原型

```c++
bool imwrite(const string& filename,InputArray img,const vector<int>& params=vector<int>());
```

+ 一个参数：文件名，记得加后缀。
+ 第二个参数：InputArray类型的img,一般填写一个Mat类型的图像数据。
+ const vector<int>& 类型的params,表示为特定格式保存的参数编码。

## 滑动条的创建和使用

`创建滑动条：createTrackbar()函数`

createTrackbar()函数用于创建一个可以调整数值的滑动条。

`函数原型`

int createtrackbar(conststring& trackbarname,conststring& winname，int value,int count,TrackbarCallback onChange=0,void* userdata = 0);

+ 第一个参数：conststring&类型的 trackbarname,轨迹条的名字。
+ 第二个参数：conststring&类型的 winname，窗口的名字，表示这个轨迹条会依附到哪个窗口上。
+ 第三个窗口：int* 类型的value,一个指向整型的指针，表示滑块的位置
+ 第四个窗口：int 类型的count,表示滑块可以到达的最大位置的值。
+ 第五个参数：TrackbarCallback类型的onChange,每次滑块位置改变时，这个函数都会进行回调。
+ 第六个参数，void* 类型的userdata,这个参数是用户传给回调函数的数据，用来处理轨迹条事件。
