# C Train For 18

## 大一C语言培训

## 数组

+ ### 

## 指针

+ ### 指针及其使用

+ ### 指向数组的指针

+ ### 保存指针的数组

+ ### 指针在函数中的应用

+ ### 二级指针

## 结构体

### 1. 为什么要有结构体？

在程序中，经常会遇到特定类型的实物需要使用过很多不同类型的数据来表述，如果全部都用单独的变量来指代每一个数据，就要定义很多非常繁琐的变量

```c
#include "stdio.h"
int main()
{
    char name[20] = "baoqianyue";
    int height = 175;
    int weight = 70;
    char sex = 'm';
    short age = 19;
    long  wealth  = 300000;
    printf("鲍骞月的个人信息：\n");
    printf("姓名：%s,身高：%d,性别：%c,年龄：%d,财产：%d\n",name,height,sex,age,wealth);
    return 0;
}
```

数组允许定义可存储相同类型数据项的变量，结构是 C 编程中另一种用户自定义的可用的数据类型，它允许您存储不同类型的数据项,而结构体的出现就很好的解决了这个问题

+ 结构体的构造

```c
struct 结构类型名
{
    数据类型1 成员变量1;
    数据类型2 成员变量2;
    数据类型3 成员变量3;
    ....
}; //<- 需要注意的地方
```

+ 定义结构体变量

```c
struct Stu{
    int height;//身高
    int weight;//体重
    char sex;//性别
    int age; //年龄
    long wealth;
};
```

这个结构体名是Stut，它内部有五个成员，分别为身高，体重，性别，年龄。定义形式与普通变量定义的方式一样，只不过不能立即初始化。

+ 结构体变量的初始化


结构体也是一种数据类型，在某种意义上与int，char这些基本数据类型是同级的，所以定义变量的方式是一样的。

```c
struct student stu1,stu2;
```

对于结构体，初始化并赋值的一般形式为

```c
strcut 结构类型名 结构变量 = {数据1，数据2,...};
```

+ 结构体成员的读取和赋值

结构体成员的获取形式为：

```c
结构体变量名.成员名;
```

为单个结构体变量赋值,定义结构体变量并赋值，在这里我们定义了一个名stu1的结构体变量，并且为这个结构体

```c
    Stu stu1;
    stu1.age = 19;
    stu1.height = 175;
    stu1.sex = 'm';
    stu1.wealth = 30000;
    stu1.weight = 70;
    printf("身高：%d,性别：%c,年龄：%d,财产：%d\n",stu1.height,stu1.sex,stu1.age,stu1.wealth);
```

+ 使用typedef简化变量名

```c
typedef StudentInfo Stu;
typedef int integer;
```

### 2. 结构体的使用
  
#### 结构体与数组
  
+ 数组作为结构体的变量

举个例子：一家店雇佣了三个兼职人员，只需要他们在一个星期内来4天就可以，此时如何定义结构体？

```c
struct schedule{
    char name;
    char sex;
    int week1;
    int week2;
    int week3;
    int week4;
};
```

使用数组节省没必要的变量

```c
struct schedule{
    char name;
    char sex;
    int week[4];
};
//简化结构体的名字
typedef schedule S;
```

```c
int main()
{
    S sd1 = {'A','m',1,2,4,6};
    S sd2 = {'A','m',3,5,6,7};
    S sd3 = {'A','m',2,3,5,7};
    printf("姓名：%c,性别：%c,工作日：%d %d %d %d",
        sd1.name,sd1.sex,sd1.week[0],sd1.week[1],sd1.week[2],sd1.week[3]);
    return 0;
}
```

+ 保存结构的数组

```c
int main()
{
    S st[3] = { {'A','m',1,2,4,6 } , {'A','m',3,5,6,7} , {'A','m',2,3,5,7} };
    for(int i = 0;i < 3;i ++)
    printf("姓名：%c,性别：%c,工作日：%d %d %d %d\n",
        st[i].name,st[i].sex,st[i].week[i],st[i].week[1],st[i].week[2],st[i].week[3]);
    return 0;
}
```

#### 结构体与指针
  
+ 结构体与函数

结构体作为函数参数，传入函数进行赋值，并将赋值完的结构体返回给主函数
传参方式与其他类型的变量或指针类似

```c
#include "stdio.h"
struct complex_num{
    int real;
    int image;
};
typedef complex_num comp;

comp assign(comp num)
{
    puts("输入复数的实部：");
    scanf("%d",&(num.real));
    puts("输入复数的实部：");
    scanf("%d",&(num.image));
    return num;
}

int main()
{
    comp com1;
    com1 = assign(com1);
    printf("%d + %di",com1.real,com1.image);
    return 0;
}
```

#### 结构体的应用 -- 链表

+ 结构体变量指针

![train.png](https://upload-images.jianshu.io/upload_images/9140378-105df5dddce29c6a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/640)

结构体变量成员指向自身

即将定义的结构体变量的地址赋予给所定义的结构体，这样定义的该结构体的指针域就只想了结构体本身

```c
struct table{
    int i;
    char c;
    struct table *st;
};
int main()
{
    table st1 = {1,'a'};
    st1.st = &st1;
    //使用结构体变量输出自身的2个成员的值
    printf("%d %c\n",st1.i,st1.c);
    //使用结构体指针域所指向的结构体输出数值
    printf("%d %c\n",st1.st->i,st1.st->c);
    return 0;
}
/*
1 a
1 a
*/
```

结构体变量成员指向其他结构变量

即将定义的两个结构体变量，比方说定义了 st1 和 st2两个结构体变量，只需要将st2 的地址 赋给 st1 的指针域，这样 st1 的指针就指向了 st2

![train1.png](https://upload-images.jianshu.io/upload_images/9140378-b8b80be836c3d74a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/440)

```c
int main()
{
    table st1 = {1,'a'};
    table st2 = {2,'b'};
    st1.st = &st2;

    //使用结构体变量输出st1自身的2个成员的值
    printf("%d %c\n",st1.i,st1.c);

    //使用结构体指针域所指向的结构体输出数值,即 st2 中的数值
    printf("%d %c\n",st1.st->i,st1.st->c);

    //使用结构体变量输出st2自身的2个成员的值
    printf("%d %c\n",st2.i,st2.c);

    return 0;
}
/*
1 a
2 b
2 b
*/
```

+ 数组与链表

数组是由同类型的多个数据组成的，链表是由是由多个相同结构连接而成
但是数组中就可以存放结构体，为啥还要单独专门独立出来一个链表呢？这是因为数组的长度总是固定的，没办法动态的储存数据

```c
#include "stdio.h"
struct table{
    int i;
    char c;
    struct table *st;
};
int main()
{
    table tal[3] = {
        {1,'a'},
        {2,'b'},
        {3,'c'}
    };
    return 0;
}
```

上面的代码也能做到和链表一样的效果，甚至比链表还要简洁，但是如果程序中的结构数目是用户自己决定的话，或者说结构体的数目是位未知的，那怎么办?数组的长度可以在程序运行时不能被更改，所以说，数组跟结构体搭配的前提时数组的长度固定并且已知

+ 链表概述

![timg.jpg](https://upload-images.jianshu.io/upload_images/9140378-c16769111551b03e.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/840)

1. 链表的最小单元 -- 结点

2. 链表的组成部分

一个连边通常由3部分组成：投机欸但、数据结点和尾结点

+ 头节点：

+ 数据结点：

+ 尾结点：


#### 链表操作

+ 插入结点到链表
+ 删除链表中的结点

## 字符串

+ ### 什么是字符串？

+ ### 字符串的输入与输出

+ ### 指向字符串的指针

+ ### 常见的字符串操作
  + 赋值
  + 加法
  + 修改
  + 比较

## 文件

+ ### 为什么要有文件操作
+ ### 文件的打开和关闭
+ ### 文件的读写操作
  + 写入数据
  + 读取数据

