# 初探core组件

## Mat结构的使用

> OpenCV函数中输出图像的内存分配是自动完成的(如果不特别指定的话)。

> 使用OpenCv的C++接口时不需要考虑内存释放的问题。

> 赋值运算和拷贝构造函数只复制信息头。

```c++
Mat A,C; //仅创建信息头部分
A = imread("1.jpg",CV_LOAD_IMAGE_COLOR);  //这里为矩阵开辟空间
Mat B(A);  //使用拷贝构造函数
C = A;  //赋值运算符
```

> 使用函数clone()或则cypyTo()来复制一幅图像的矩阵。

```c++
Mat F = A.clone();
Mat G;
A.copyTo(G);
```