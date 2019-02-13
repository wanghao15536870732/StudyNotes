# 常见数据结构和函数

## Point类

> 表示二维坐标系下的点

```c++
Point point;
point.x = 10;
point.y = 8;
```

> 并具有如下定义

```c++
typedef Point_<int> Point2i;
typedef Point2i Point;
typedef Point_<float>  
```

## Scalar类

> Scalar()表示具有4个元素的数组，

```c
Scalar(a,b,c); //定义的RGB的颜色值：红色分量为c,绿色分量为b，蓝色分量为a
```
