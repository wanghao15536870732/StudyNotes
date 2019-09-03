# 第一次Cv

[VS2017 + OpenCv3.4.4 配置教程](https://blog.csdn.net/qq_41175905/article/details/80560429)

## 1.图像显示

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
```

![L3BI$QHNWG58BKCRU374~0X.png](https://upload-images.jianshu.io/upload_images/9140378-6f04f461831183f3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/440)

## 2.图像腐蚀

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
```

![](https://upload-images.jianshu.io/upload_images/9140378-41332ca3ac66c48f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 3.图像模糊

```c++
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
```

![JVX776$@~Z%Q6V1HPLPYA%4.png](https://upload-images.jianshu.io/upload_images/9140378-0a6ff769784c156b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 4.canny边缘检测

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
    //载入图像
    Mat srcImage = imread("D:\\Desktop\\pic.jpg");
    if (srcImage.empty())
    {
        cout << "can not find the img" << endl;
    }
    //显示原始图
    imshow("【原图】Canny边缘检测",srcImage);
    Mat edge, greyImage;  //参数定义

    //【1】将原图像转换为灰度图像
    cvtColor(srcImage, greyImage, CV_BGR2GRAY);

    //【2】先使用3×3内核来降噪
    blur(greyImage, edge, Size(3, 3));

    //【3】运行Canny算子
    Canny(edge, edge, 3, 9, 3);

    //【4】显示效果图
    imshow("均值滤波【效果图】",edge);

    waitKey(0);  //等待任意按键按下
    return 0;
}
```

![Kng](https://upload-images.jianshu.io/upload_images/9140378-206cb5151d4e9c3a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 5.调用摄像头采集图像

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

> 参考自@毛星云的《OpenCV3编程入门》