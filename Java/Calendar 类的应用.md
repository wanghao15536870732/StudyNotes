# Date 类最主要的作用就是获得当前时间，同时这个类里面也具有设置时间以及一些其他的功能

+ ## 但是由于本身设计的问题，这些方法却遭到众多批评，不建议使用，更推荐使用 Calendar 类进行时间和日期的处理。

+ ## java.util.Calendar 类是一个抽象类，可以通过调用 getInstance() 静态方法获取一个 Calendar 对象，此对象已由当前日期时间初始化，即默认代表当前时间,如

```jaVa
Calendar c = Calendar.getInstance();
```

+ ## 那么如何使用 Calendar 获取年、月、日、时间等信息呢？我们来看下面的代码：

```java
        Calendar c1 = Calendar.getInstance();  //创建Calendar对象
        int year = c1.get(Calendar.YEAR);
        int month = c1.get(Calendar.MONTH) + 1;  //获取月份，0表示1月份
        int day = c1.get(Calendar.DAY_OF_MONTH);
        int hour = c1.get(Calendar.HOUR_OF_DAY);
        int minute = c1.get(Calendar.MINUTE);
        int second = c1.get(Calendar.MINUTE);
        System.out.println("当前时间：" + year + "-" + month + "-" + day + "-"
             + hour + ":" + minute + ":" + second);
```

+ ## 其中，调用 Calendar 类的 getInstance() 方法获取一个实例，然后通过调用 get() 方法获取日期时间信息，参数为需要获得的字段的值，Calendar.Year 等为 Calendar 类中定义的静态常量。
 
 ### 运行结果 ：

```java
 当前时间：2018-2-4-22:24:24
```

+ ## Calendar 类提供了 getTime() 方法，用来获取 Date 对象， 

+ 完成 Calendar 和 Date 的转换，还可通过 getTimeInMillis() 方法，获取此 Calendar 的时间值，以毫秒为单位。如下所示：

```java
        Date date = c.getTime();

        Long time = c.getTimeInMillis();
        System.out.println("******************");

        System.out.println("当前时间：" + date);
        System.out.println("当前毫秒数：" + time);

        System.out.println("*****************");
```

### 运行结果:

```java
******************
当前时间：Sun Feb 04 22:32:21 CST 2018
当前毫秒数：1517754741009
*****************
```
