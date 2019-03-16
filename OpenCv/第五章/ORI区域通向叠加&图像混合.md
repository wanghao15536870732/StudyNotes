# ORI区域通向叠加&图像混合

## 定义ROI区域

### 方法一 使用表示矩形区域的Rect

它指定矩形的左上角坐标和矩形的长宽以定义一个矩形区域

```c
//其中，image为已经载入好的图片
Mat imageROI;

//方法一
imageROI = image(Rect(500,250,logo.cols,logo.rows));
```

### 方法二 指定感兴趣行或列的范围

Range是指从起始索引到终止索引的一连段连续序列

```c
imageROI = image(Range(250,250 + logoImage.rows),Range(200,200 + logoImage.cols));
```

### 利用ROI将一幅图加到另一幅图的指定位置

+ 通过一个图像掩模(mask),直接将插入处的像素设置为logo图像的像素值

```c
bool ROI_AddImage()
{
    //【1】读入图像
    Mat srcImage1 = imread("D:\\Desktop\\lena.jpg");
    Mat logoImage = imread("D:\\Desktop\\cat.png");
    if (!srcImage1.data)
    {
        cout << "读取srcImage1错误" << endl;
        return false;
    }
    if (!logoImage.data)
    {
        cout << "读取logoImage出错" << endl;
        return false;
    }
    //【2】定义一个Mat类型并给其设定ROI区域
    Mat imageROI = srcImage1(Rect(20, 25, logoImage.cols, logoImage.rows));

    //【3】加载掩模
    Mat mask = imread("D:\\Desktop\\cat.png", 0);

    //【4】将掩模复制到ROI
    logoImage.copyTo(imageROI, mask);

    //显示结果
    namedWindow("<1>利用ROI实现图像叠加示例窗口");
    imshow("<1>利用ROI实现图像叠加示例窗口", srcImage1);
    return true;
}
```

### 运行结果

![34](https://upload-images.jianshu.io/upload_images/9140378-b856baba11cf1422.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/240)

## 线性混合操作

> 线性混合操作是一种典型的二元的像素操作，理论公式为：

<div align="center"> <font size = 6>
g(x) = (1 - a)Fa(x) + aF3(x); </font></div>

`意思就是通过在范围0到1之间改变alpha值，来对两幅图像（f0(x)） 和（f1(x)）产生时间上的画面叠化效果`

### 计算数组加权和 addWeighted()函数

`这个函数的作用就是计算两个数组的加权和`

```c
//函数原型
void addWeight(
    InputArray src1,  //表示需要加权的第一个数组
    double alpha,   //表示第一个数组的权重
    InputArray src2,  //表示第二个数组，必须和第一个数组拥有相同的尺寸和通道数
    double beta,   //表示第二个数组的权重
    double gamma,  //一个加到权重总和上的标量值
    OutputArray dst, //输出的数组
    int type == - 1  //输出阵列的可选深度
);
```

> 用addWeight函数计算以下两个数组的加权和，得到结果输出给第四个参数。

```c
dst = src1[I]*alpha + src2[I]*beat + gamma;
```

### 示例

```c
bool LinearBlending()
{
    //【0】定义一些局部变量
    double alphavalue = 0.5;  //
    double betaValue;
    Mat srcImage2, srcImage3, dstImage;

    //【1】读取图像
    srcImage2 = imread("D:\\Desktop\\img_nice.png");
    srcImage3 = imread("D:\\Desktop\\img_nice1.jpg");
    if (!srcImage2.data)
    {
        cout << "读取srcImage2错误" << endl;
        return false;
    }
    if (!srcImage3.data)
    {
        cout << "读取srcImage3出错" << endl;
        return false;
    }

    //【2】作图像混合加权操作
    betaValue = (1.0 - alphavalue);
    addWeighted(srcImage2, alphavalue, srcImage3, betaValue, 0.0, dstImage);

    //【3】创建并显示原图窗口
    namedWindow("<2>线性混合示例窗口【原图】", 1);
    imshow("<2>线性混合示例窗口【原图】", srcImage2);

    namedWindow("<3>线性混合示例窗口【效果图】", 1);
    imshow("<3>线性混合示例窗口【效果图】", dstImage);

    return true;
}
```

### 效果

![show](https://upload-images.jianshu.io/upload_images/9140378-d51182d06e50968d.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/240)
