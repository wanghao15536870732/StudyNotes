# Java基础语法

+ [`Java 的注释`](#Java的注释)
  + [`单行注释`](#单行注释)
  + [`多行注释`](#多行注释)
  + [`使用文档注释`](#使用文档注释)
  + [`利用中文定义标识符`](#利用中文定义标识符)
+ [`数据类型划分`](#数据类型划分)
  + [`定义 int 型变量`](#定义int型变量)
  + [`观察变量与常量的区别`](#观察变量与常量的区别)
  + [`如果超过了int 的最大值或最小值的结果`](#如果超过了int的最大值或最小值的结果)
  + [`扩大数据类型`](#扩大数据类型)
  + [`将范围大的数据类型变为范围小的数据类型`](#将范围大的数据类型变为范围小的数据类型)
  + [`发生溢出的转换问题`](#观察发生溢出的转换问题)
  + [`byte 的转换`](#观察byte转换)
+ [`运算符`](#运算符)
  + [`不建议使用的代码`](#不建议使用的代码)
  + [`使用关系运算符`](#使用关系运算符)
  + [`观察自增`](#观察自增)
  + [`利用判断语句实现三目运算的功能`](#利用判断语句实现三目运算的功能)
+ [`方法的定义及使用`](#方法的定义及使用)
  + [`定义一个没有参数没有返回值的方法`](#定义一个没有参数没有返回值的方法)
  + [`定义一个有参数无返回值的方法`](#定义一个有参数无返回值的方法)
  + [`定义有返回值有参数的方法`](#定义有返回值有参数的方法)
  + [`方法重载`](#方法重载)
  + [`递归调用`](#递归调用)


## Java的注释

### 单行注释

```java
public class TestDemo { 
    public static void main(String[] args) {
        // 此处为注释，编译代码时不编译
        System.out.println("Hello World!");
    }
}
```

### 多行注释

```java
public class TestDemo {
    public static void main(String[] args) {
        /*
         *  此处为多行注释，编译代码时不编译
         *  如果要学习Java高端课程，可以登录：www.mldnjava.cn
         */
        System.out.println("Hello World!");
    }
}
```

### 使用文档注释

```java
/**
 * 此处为文档注释
 *@author wanghao
 */
public class TestDemo {
    public static void main(String[] args) {
        System.out.println("Hello MLDN .");
    }
}
```

### 利用中文定义标识符

```java
public class 你好 { // 类名称
    public static void main(String args[]) {
        int 年龄 = 20 ;	 			// 变量名称
        System.out.println(年龄) ; // 输出内容
    }
}
/*
20
*/
```

## 数据类型划分

### 定义int型变量

```java
public class TestDemo {
    public static void main(String args[]) {
        // 为变量设置内容使用如下格式：数据类型 变量名称 = 常量 ;
        int num = 10 ; // 10是常量，常量的默认类型是int
        int result = num * 2 ; // 利用num变量的内容乘以2，并且将其赋值给result
        System.out.println(result) ; // 输出result变量
    }
}
/*
20
*/
```

### 观察变量与常量的区别

```java
public class TestDemo {
    public static void main(String args[]) {
        // 所有的变量名称在同一块代码中只允许声明一次
        int num = 10 ; // 10是常量，常量的默认类型是int
        // 取出num变量的内容乘以2，并且将其设置给num变量
        num = num * 2 ;
        System.out.println(num) ;
    }
}
/*
20
*/
```

### 如果超过了int的最大值或最小值的结果

```java
public class TestDemo {
    public static void main(String args[]) {
        int max = Integer.MAX_VALUE ; // 取出最大值
        int min = Integer.MIN_VALUE ; // 取出最小值
        System.out.println(max) ; // 2147483647
        System.out.println(min) ; // -2147483648
        // int变量 ± int型常量 = int型数据
        System.out.println(max + 1) ; // 最大值加1：-2147483648
        System.out.println(min - 1) ; // 最小值减1：2147483647
        System.out.println(min - 2) ; // 最小值减2：2147483646
    }
}
```

### 扩大数据类型

```java
public class TestDemo {
    public static void main(String args[]) {
        int max = Integer.MAX_VALUE; // 取出最大值
        int min = Integer.MIN_VALUE; // 取出最小值
        // int变量 ± long型常量 = long型数据
        System.out.println(max + 1L); // 最大值加1：2147483648
        System.out.println(min - (long) 1); // 最小值减1：-2147483649
        // long变量 ± int型常量 = long型数据
        System.out.println((long) min - 2); // 最小值减2：-2147483650
    }
}
```

### 将范围大的数据类型变为范围小的数据类型

```java
public class TestDemo {
    public static void main(String args[]) {
        long num = 1000 ; // 1000常量是int型，使用long接受，发生了向大范围转型
        int x = (int) num ; // 把long变为int
        System.out.println(x) ; //
    }
}
/*
1000
*/
```

### 观察发生溢出的转换问题

```java
public class TestDemo {
    public static void main(String args[]) {
        long num = 2147483650L ; // 该数据已经超过了int数据范围
        int x = (int) num ; // 把long变为int
        System.out.println(x) ;
    }
}
/*
-2147483646
*/
```

### 观察byte转换

```java
public class TestDemo {
    public static void main(String args[]) {
        int num = 130 ; // 此范围超过了byte定义
        byte x = (byte) num ; // 由int变为byte
        System.out.println(x) ;
    }
}
/*
-126
*/
```

## 运算符

### 不建议使用的代码

```java
public class TestDemo {
    public static void main(String args[]) {
        int numA = 10 ;
        int numB = 20 ;
        // 如此复杂的代码，一定会大量损害你的脑细胞
        int result = numA * 2 - --numB * numA ++ + numB - numA -- + numB ;
        System.out.println(result) ;
    }
}
/*
-143 这咋算出来的  哈哈
*/
```

### 使用关系运算符

```java
public class TestDemo {
    public static void main(String args[]) {
        System.out.println("3 > 1 = " + (3 > 1));  // 使用大于号
        System.out.println("3 < 1 = " + (3 < 1)); // 使用小于号
        System.out.println("3 >= 1 = " + (3 >= 1)); // 使用大于等于号
        System.out.println("3 <= 1 = " + (3 <= 1)); // 使用小于等于号
        System.out.println("3 == 1 = " + (3 == 1)); // 使用等于号
        System.out.println("3 != 1 = " + (3 != 1)); // 使用不等于号
    }
}
```

### 观察自增

```java
public class TestDemo {
    public static void main(String args[]) {
        int numA = 10; // 定义整型变量
        int numB = 20; // 定义整型变量
        // “++”写在变量前面，表示先对numA的变量内容加1
        // 使用处理后的numA变量的内容 + numB变量的内容
        int result = ++numA + numB;
        System.out.println("numA = " + numA);
        System.out.println("result = " + result);
    }
}
/*
numA = 11
result = 31
*/
```

### 利用判断语句实现三目运算的功能

```java
public class TestDemo {
    public static void main(String args[]) {
        int numA = 10; // 定义int型变量
        int numB = 20; // 定义int型变量
        int max = 0 ;
        // 用if语句替代：int max = numA > numB ? numA : numB;
        if (numA > numB) { // 如果numA的内容大于numB
           max = numA ; // max变量的内容为numA的内容
        } else { // 如果numA的内容小于numB
           max = numB ; // max变量的内容为numB的内容
        }
        System.out.println(max);
    }
}
/*
20
*/
```

## 方法的定义及使用

### 定义一个没有参数没有返回值的方法

```java
public class TestDemo {
    public static void main(String args[]) {
        printInfo(); // 直接调用方法
        printInfo(); // 直接调用方法
    }
    /**
     * 信息输出操作
     */
    public static void printInfo() { // 定义没有参数，没有返回值的方法
        System.out.println("*********************");
        System.out.println("*   www.baidu.com   *");
        System.out.println("*********************");
    }
}
/*
*********************
*   www.baidu.com   *
*********************
*/
```

### 定义一个有参数无返回值的方法

```java
public class TestDemo {
    public static void main(String args[]) {
        pay(10.0); // 调用方法
        pay(-10.0); // 调用方法
    }
    /**
     * 定义一个支付的操作方法，如果支付金额大于0则正常支付，否则会输出错误提示信息
     * @param money 要支付的金额
     */
    public static void pay(double money) { // 购买支付操作
        if (money > 0.0) { // 现在已经给钱
           System.out.println("可以进行支付！");
        } else { // 不能够支付
           System.out.println("你穷疯了，没钱还买东西！");
        }
    }
}
/*
可以进行支付！
你穷疯了，没钱还买东西！
*/
```

### 定义有返回值有参数的方法

```java
public class TestDemo {
    public static void main(String args[]) {
        int result = add(10, 20); // 方法的返回值可以进行接收
        System.out.println("计算结果：" + result);
        System.out.println("计算结果：" + add(50, 60)); // 也可以直接将方法返回值进行输出
    }
    /**
     * 实现数据的加法操作
     * @param x 操作数字一
     * @param y 操作数字二
     * @return 返回两个数字的加法计算结果
     */
    public static int add(int x, int y) { // 有参数有返回值的方法
        return x + y; // 返回加法计算结果
    }
}
/*
计算结果：30
计算结果：110
*/
```

### 方法重载

```java
public class TestDemo {
    public static void main(String args[]) {
        // 方法重载之后执行语句时会根据传入参数的类型或个数的不同调用不同的方法体
        System.out.println("两个整型参数：" + add(10, 20)); 
        System.out.println("三个整型参数：" + add(10, 20, 30)); 
        System.out.println("两个浮点型参数：" + add(10.2, 20.3)); 
    }
    /**
     * 实现两个整型数字的加法计算操作
     * @param x 操作数字一
     * @param y 操作数字二
     * @return 两个整型数据的加法计算结果
     */
    public static int add(int x, int y) { // add()方法一共被重载三次
        return x + y;
    }
    /**
     * 实现三个整型数字的加法计算操作
     * @param x 操作数字一
     * @param y 操作数字二
     * @param z 操作数字三
     * @return 三个整型数据的加法计算结果
     */
    public static int add(int x, int y, int z) { // 与之前的add()方法的参数个数不一样
        return x + y + z;
    }
    /**
     * 实现两个小数的加法计算操作
     * @param x 操作数字一
     * @param y 操作数字二
     * @return 两个小数的加法计算结果
     */
    public static double add(double x, double y) { // 与之前的add()方法的参数类型不一样
        return x + y;
    }
}
/*
两个整型参数：30
三个整型参数：60
两个浮点型参数：30.5
*/
```

### 递归调用

```java
public class TestDemo {
    public static void main(String args[]) {
        System.out.println(sum(100)); // 1 - 100累加
    }
    /**
     * 数据的累加操作，传入一个数据累加操作的最大值，而后每次进行数据的递减，一直累加到计算数据为1
     * @param num 要进行累加的操作
     * @return 数据的累加结果
     */
    public static int sum(int num) { // 最大的内容
        if (num == 1) { // 递归的结束调用
           return 1; // 最终的结果返回了1
        }
        return num + sum(num - 1); // 递归调用
    }
}
/*
5050
*/
```