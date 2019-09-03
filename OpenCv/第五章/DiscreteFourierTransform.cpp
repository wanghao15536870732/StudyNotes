#include "opencv2/core/core.hpp"
         "
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    //【1】ui灰度模式读取原始图像并显示
    Mat srcImage = imread("D:\\Desktop\\lena.jpg", 0);
    if (!srcImage.data)
    {
        cout << "lena图片读取错误" << endl;
        return false;
    }
    imshow("原始图像", srcImage);

    //将图像扩大到合适的尺寸
    int m = getOptimalDFTSize(srcImage.rows);
    int n = getOptimalDFTSize(srcImage.cols);

    //将添加的像素初始化为0
    Mat padded;
    copyMakeBorder(srcImage, padded,
                   0, m - srcImage.rows, 0, n - srcImage.cols,
                   BORDER_CONSTANT, Scalar::all(0));

    //将planes数组组合合并成一个多通道的数组complexI
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);

    //进行离散傅里叶变换
    dft(complexI, complexI);

    //将多通道complexI分离成几个单通道数组
    split(complexI, planes);

    /*
	planes[0] = Re(DFT(complexI));
	planes[1] = Im(DFT(complexI));
	*/
    magnitude(planes[0], planes[1], planes[0]);
    Mat magnitudeImage = planes[0];

    //进行对数尺度缩放
    magnitudeImage += Scalar::all(1);
    log(magnitudeImage, magnitudeImage); //求自然对数

    //若有奇数行或技术列，进行谱写裁剪
    magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));

    //重新排列傅里叶图像中的象限，使得原点位于图像中心
    int cx = magnitudeImage.cols / 2;
    int cy = magnitudeImage.rows / 2;
    Mat q0(magnitudeImage, Rect(0, 0, cx, cy));   //ROI区域的左上
    Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));  //ROI区域的右上
    Mat q2(magnitudeImage, Rect(0, cy, cx, cy));  //ROI区域的左下
    Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); //ROI区域的右下

    //交换象限(左上与右下)
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    //交换象限(右上与左下)
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    //归一化
    normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

    //显示
    imshow("频谱幅值", magnitudeImage);
    waitKey();
    //按任意键结束
    waitKey(0);
    return 0;
}