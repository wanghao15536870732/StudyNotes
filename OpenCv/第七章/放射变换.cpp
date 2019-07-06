#include<iostream>
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main()
{
	//【0】改变console字体颜色
	system("color 1A");
	//【1】参数准备
	//定义两组点，代表两个三角形
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];

	//定义一些Mat变量
	Mat rotMat(2, 3, CV_32FC1);
	Mat wrapMat(2, 3, CV_32FC1);
	Mat srcImage,dstImage_wrap,dstImage_wrap_rotate;

	//【2】加载图像并做一些初始化
	srcImage = imread("D:\\Desktop\\lena.jpg");
	if (!srcImage.data) {
		cout << "图片加载失败，请检查文件是否存在!" << endl;
		return false;
	}
	//设置目标图像的大小与类型与源图像一致
	dstImage_wrap = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());

	srcTriangle[0] = Point2f(0,0);
	srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
	srcTriangle[2] = Point2f(0,static_cast<float>(srcImage.rows - 1));
	
	dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols * 0.0), static_cast<float>(srcImage.rows * 0.33));
	dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols * 0.65), static_cast<float>(srcImage.rows * 0.35));
	dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols * 0.15), static_cast<float>(srcImage.rows * 0.6));

	//【4】求得放射变换
	wrapMat = getAffineTransform(srcTriangle, dstTriangle);

	//【5】对原图像应用刚刚求得的仿射变换
	warpAffine(srcImage, dstImage_wrap, wrapMat, dstImage_wrap.size());

	//对图像缩放后再旋转
	Point center = Point(dstImage_wrap.cols / 2, dstImage_wrap.rows / 2);
	double angle = -30.0;
	double scale = 0.8;
	rotMat = getRotationMatrix2D(center, angle, scale);

	warpAffine(srcImage, dstImage_wrap_rotate, rotMat, dstImage_wrap.size());


	//显示效果
	imshow("【原始图】",srcImage);
	imshow("【经过Wrap后的图像】",dstImage_wrap);
	imshow("【经过Wrap跟Rotate后的图像】",dstImage_wrap_rotate);
	
	waitKey(0);
	system("pause");
	return 0;
}
