---
title: Java第一行代码 学习笔记(二) Java 异常处理机制
tags:
  - Java
  - Java第一行代码
categories: Java
top: 101
---

![12.jpg](https://upload-images.jianshu.io/upload_images/9140378-1ab9bf303a5ac8e8.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
***
<!--more-->

***
### 首先观察下面两个异常类的继承关系：

> # ArithmeticException：
>> ## java.lang.Exception：
>>> ### java.lang.RuntimeException：
>>>> #### java.lang.ArithmeticException

> # NumberFormatExcpetion:
>> ## java.lang.Throwable:
>>> ### java.lang.Expcetion:
>>>> #### java.lang.RuntimeException:
>>>>> ##### java.lang.IllegalArgumentException:
>>>>>> ###### java.lang.NumberFormatExcpetion

###  通过两个异常类可以发现所有的异常类型最高的继承类时是Throwable,并且在Throwable下有两个子类：
* ##### Error :指的是JVM错误，这使得程序并没有执行，无法处理
  + 是程序无法处理的错误，表示运行应用程序中较严重问题。大多数错误与代码编写者执行的操作无关，而表示代码运行时 JVM（Java 虚拟机）出现的问题
  + 例如，Java虚拟机运行错误（Virtual MachineError），当 JVM 不再有继续执行操作所需的内存资源时，将出现 OutOfMemoryError。这些异常发生时，Java虚拟机（JVM）一般会选择线程终止
  + 这些错误表示故障发生于虚拟机自身、或者发生在虚拟机试图执行应用时，如Java虚拟机运行错误（Virtual MachineError）、类定义错误（NoClassDefFoundError）等。这些错误是不可查的，因为它们在应用程序的控制和处理能力之 外，而且绝大多数是程序运行时不允许出现的状况
  + 对于设计合理的应用程序来说，即使确实发生了错误，本质上也不应该试图去处理它所引起的异常状况。在 Java中，错误通过Error的子类描述

* ##### Exception :值得是程序运行过程中产生的异常，用户可以使用异常处理格式进行处理
  + 是程序本身可以处理的异常。主要包含RuntimeException等运行时异常和IOException，SQLException等非运行时异常
  + 运行时异常包括：都是RuntimeException类及其子类异常，如NullPointerException(空指针异常)、IndexOutOfBoundsException(下标越界异常)等，这些异常是不检查异常，程序中可以选择捕获处理，也可以不处理
  + 这些异常一般是由程序逻辑错误引起的，程序应该从逻辑角度尽可能避免这类异常的发生。
  + 运行时异常的特点是Java编译器不会检查它
  + 当程序中可能出现这类异常， 没有用try-catch语句捕获它，也没有用throws子句声明抛出它，也会编译通过
  + 非运行时异常（编译异常）包括：RuntimeException以外的异常，类型上都于Exception类及其子类。从程序语法角度讲是必须进行处理的异常，如果不处理，程序就不能编译通过
  + 如IOException、SQLException等以及用户自定义的Exception异常，一般情况下不自定义检查异常

<br>

![20170510095156954.png](https://upload-images.jianshu.io/upload_images/9140378-6194f94665a25017.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 在 Java 应用程序中，异常处理机制为：抛出异常，捕捉异常
+ ##### 抛出异常
  + 当一个方法出现错误引发异常时，方法创建异常对象并交付运行时系统，异常对象中包含了异常类型和异常出现时的程序状态等异常信息。运行时系统负责寻找处置异常的代码并执行
  + 注意：对于运行时异常、错误或可查异常，Java技术所要求的异常处理方式有所不同
  + 由于运行时异常的不可查性，为了更合理、更容易地实现应用程序，Java规定，运行时异常将由Java运行时系统自动抛出，允许应用程序忽略运行时异常对于方法运行中可能出现的Error，当运行方法不欲捕捉时，Java允许该方法不做任何抛出声明。因为，大多数Error异常属于永远不能被允许发生的状况，也属于合理的应用程序不该捕捉的异常。
  + 对于所有的可查异常，Java规定：一个方法必须捕捉，或者声明抛出方法之外。也就是说，当一个方法选择不捕捉可查异常时，它必须声明将抛出异常
+ ##### 捕获异常
  +  在方法抛出异常之后，运行时系统将转为寻找合适的异常处理器（exception handler）。潜在的异常处理器是异常发生时依次存留在调用栈中的方法的集合。、
  + 当异常处理器所能处理的异常类型与方法抛出的异常类型相符时，即为合适 的异常处理器。运行时系统从发生异常的方法开始，依次回查调用栈中的方法，直至找到含有合适异常处理器的方法并执行。
  + 当运行时系统遍历调用栈而未找到合适 的异常处理器，则运行时系统终止。同时，意味着Java程序的终止

+ ##### 代码演示：
```java
public class Test {
    public static void main(String[] args) {
        System.out.println("1.除法计算开始");
        try {
            System.out.println("2.除法计算：" + (10 / 0));    //此处产生异常
            // 异常产生之后的语句将不再执行，此处在try中产生异常。所以下面的语句不会再执行
            System.out.println("王浩");
        }catch (ArithmeticException e){
            System.out.println("*******出现异常了*********");
        }finally {
            System.out.println("3.除法计算结束。");
        }
    }
}
```
+ ##### 代码注释：
+ 结构解释：
  + try 块：用于捕获异常。其后可接零个或多个catch块，如果没有catch块，则必须跟一个finally块
  + catch 块：用于处理try捕获到的异常
  + finally 块：无论是否捕获或处理异常，finally块里的语句都会被执行。当在try块或catch块中遇到return语句时，finally语句块将在方法返回之前被执行
+ 在以下4种特殊情况下，finally块不会被执行：
  + 在finally语句块中发生了异常
  + 在前面的代码中用了System.exit()退出程序
  + 程序所在的线程死亡
  + 关闭CPU
+ try、catch、finally语句块的执行顺序
  + 当try没有捕获到异常时：try语句块中的语句逐一被执行，程序将跳过catch语句块，执行finally语句块和其后的语句
  + try捕获到异常，catch语句块里没有处理此异常的情况：当try语句块里的某条语句出现异常时，而没有处理此异常的catch语句块时，此异常将会抛给JVM处理，finally语句块里的语句还是会被执行，但finally语句块后的语句不会被执行
  + try捕获到异常，catch语句块里有处理此异常的情况：在try语句块中是按照顺序来执行的，当执行到某一条语句出现异常时，程序将跳到catch语句块，并与catch语句块逐一匹配，找到与之对应的处理程序，其他的catch语句块将不会被执行，而try语句块中，出现异常之后的语句也不会被执行，catch语句块执行完后，执行finally语句块里的语句，最后执行finally语句块后的语句


+ ##### 输出结果：
```java
    1.除法计算开始
    *******出现异常了*********
    3.除法计算结束。
```
### 关键词 throws
+ 虽然在"MyMath.div(10,2)"计算时一定不会出现任何的异常，但是必须得写异常处理机制
因为这是设计的需要
+ 现在编写的计算操作可能没有问题，但是另一个人就有可能把被除数写成0
并且主方法上也可以使用theows抛出
```java

class MyMath{
    public static int div(int x,int y)throws Exception{  // 此方法不处理异常
        return x / y;
    }
}
public class TestDemo {
    public static void main(String[] args) {
    try {   //div 方法抛出异常，必须明确的进行异常的处理
            System.out.println(MyMath.div(10,5));
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
```
+ 输出结果为：2
***

参考文章 [Java异常处理机制总结](https://www.jianshu.com/p/872844d995c4)  <br>   Github Pages [hyyyrwang.github.io](https://github.com/wanghao15536870732/LearnNotes/blob/master/java--%E5%BC%82%E5%B8%B8%E5%A4%84%E7%90%86%E6%9C%BA%E5%88%B6#L79)
