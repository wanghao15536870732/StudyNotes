---
title: 总结的一些 [牛客] 上的算法题
tags:
  - c
categories: c-c++
top: 70
dedescription:
---

***

<!--more-->
![timg.jpg](https://upload-images.jianshu.io/upload_images/9140378-eefb30e5e7ac737f.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

# [牛客官网](https://www.nowcoder.com)：

+ 反序输出  ~ 替换空格 ~ 句子反转
+ 数字颠倒 ~ 字符串分离 ~ 明明的随机数
+ 计算字符个数 ~ 字符串最后一个单词的长度
+ 从尾到头打印链表 ~ 跳台阶
+ 斐波那契数列 ~ 10000的阶乘

## 1. 反序输出

### 输入任意4个字符(如：abcd)， 并按反序输出(如：dcba)

```java
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNext()){
            StringBuilder str = new StringBuilder(scanner.next());
            str.reverse();
            System.out.println(str.toString());
        }
    }
}
```

## 2. 替换空格

### 请实现一个函数，将一个字符串中的空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy

```Java
import java.util.Scanner;
public class Solution {
  public String replaceSpace(StringBuffer str) {
        if (str == null){
            return null;
        }
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) == ' '){
                sb.append('%');
                sb.append('2');
                sb.append('0');
            }else {
                sb.append(str.charAt(i));
            }
        }
        return sb.toString();
    }
}
```

## 3. 句子反转

### 给定一个句子 (只包含字母和空格) 将句子中的单词位置反转，单词用空格分割, 单词之间只有一个空格，前后没有空格比如: （1） “hello xiao mi”-> “mi xiao hello”

```Java
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String str = scanner.nextLine();
        String string = reverse(str);
        System.out.println(string);
    }

    public static String reverse(String str){

        String[] s = str.split(" ");
        StringBuilder sb = new StringBuilder();
        for (int i = s.length - 1; i > 0 ; i --) {
            sb.append(s[i]);
            sb.append(" ");
        }
        sb.append(s[0]);
        return sb.toString();
    }
}
```

## 4. 数字颠倒

### 描述：输入一个整数，将这个整数以字符串的形式逆序输出程序不考虑负数的情况，若数字含有0，则逆序形式也含有0，如输入为100，输出为001

```c
#include <stdio.h>
int main()
{
    int k,i;
    scanf("%d",&k);
    if(k == 0)
    {
        printf("%d",k);
    }
    while(k != 0)
    {
        i = k % 10;
        printf("%d",i);
        k = k / 10;
    }
    return 0;
}
```

## 5. 字符串分离

### 连续输入字符串，请按长度为8拆分每个字符串后输出到新的字符串数组长度不是8整数倍的字符串请在后面补数字0，空字符串不处理

```Java
import java.util.Scanner;
public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String str = scanner.nextLine();
            cutout(str);
        }
    }

    public static void cutout(String str){

        if (str.length() >= 8){
            //输出截取后的数字串
            System.out.println(str.substring(0,8));
            //将原来的数字串，从第八位截取，为下一行做准备
            str = str.substring(8);
            cutout(str);
        }else if ((str.length() > 0)){
            str += "00000000";
            System.out.println(str.substring(0,8));
        }
    }
}
```

## 6. 明明的随机数

+ ### 明明想在学校中请一些同学一起做一项问卷调查，为了实验的客观性，他先用计算机生成了N个1到1000之间的随机整数（N≤1000），对于其中重复的数字，只保留一个，把其余相同的数去掉，不同的数对应着不同的学生的学号。然后再把这些数从小到大排序，按照排好的顺序去找同学做调查。
+ ### 请你协助明明完成“去重”与“排序”的工作。
+ ### n输入随机数的个数inputArray n 个随机整数组成的数组 Return Value OutputArray 输出处理后的随机整数

```Java
import java.util.Scanner;
import java.util.TreeSet;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int num = 0;
        while(scanner.hasNext() && num < 10) {

            //记录下输入的数字的数量
            int sum = scanner.nextInt();

            //建立Integer的TreeSet泛型,用它的强大的功能进行排序
            TreeSet<Integer> tree = new TreeSet<>();

            for (int i = 0; i < sum; i++) {
                int number = scanner.nextInt();
                tree.add(number);
            }
            //再进行循环打印
            for (Integer set : tree) {
                System.out.println(set);
            }

            num ++;
        }
    }
}
```

## 7. 计算字符个数

### 写出一个程序，接受一个有字母和数字以及空格组成的字符串，和一个字符，然后输出输入字符串中含有该字符的个数。不区分大小写

```Java
import java.util.Scanner;

public class Main {
    public static int getCount(String str,char c){
        int count = 0;
        if (str != null && str.length() > 0){
            for (int i = 0; i < str.length(); i++) {
                char at = str.charAt(i);
                if (c == at){
                    count ++;
                }else if ((at >= 'A') && (at <= 'Z') && (c == at + 32)){
                    count ++;
                }else if ((at >= 'a') && (at <= 'z') && (c == at - 32)){
                    count ++;
                }
            }
        }else {
            count =  0;
        }
        return count;
    }

    public static void main(String[] args) {
        Scanner scr = new Scanner(System.in);
        String str = scr.next();
        char c = scr.next().charAt(0);
        System.out.println(getCount(str,c));
    }
}
```

## 8. 字符串最后一个单词的长度

### 计算字符串最后一个单词的长度，单词以空格隔开

```Java
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String s = "";
        while (input.hasNextLine()){
            s = input.nextLine();
            System.out.println(s.length() - 1 - s.lastIndexOf(" "));
        }
    }

}
```

## 9. 从尾到头打印链表

### 输入一个链表，从尾到头打印链表每个节点的值

+ #### 方法一：链表从尾到头输出，利用递归实现，不使用库函数直接printf输出的时候用递归比较好

```Java
/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> printListFromTailToHead(struct ListNode* head) {
        vector<int> value;
        if(head != NULL)
        {
            value.insert(value.begin(),head->val);
            if(head->next != NULL)
            {
                vector<int> tempVec = printListFromTailToHead(head->next);
                if(tempVec.size()>0)
                value.insert(value.begin(),tempVec.begin(),tempVec.end());
            }

        }
        return value;
    }
};
```

+ #### 方法二：用库函数，每次扫描一个节点，将该结点数据存入vector中，如果该节点有下一节点，将下一节点数据直接插入vector最前面，直至遍历完，或者直接加在最后，最后调用reverse

```Java
/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> printListFromTailToHead(struct ListNode* head) {
        vector<int> value;
        if(head != NULL)
        {
            value.insert(value.begin(),head->val);
            while(head->next != NULL)
            {
                value.insert(value.begin(),head->next->val);
                head = head->next;
            }

        }
        return value;
    }
};
```

+ #### 方法三：java递归 简洁版本

```java
public class Solution {
    ArrayList<Integer> arrayList=new ArrayList<Integer>();
    public ArrayList<Integer> printListFromTailToHead(ListNode listNode) {
        if(listNode!=null){
            this.printListFromTailToHead(listNode.next);
            arrayList.add(listNode.val);
        }
        return arrayList;
    }
}
```

## 10. 跳台阶

### 一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法

```java
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println(JumpFloor(scanner.nextByte()));
    }

    public static int JumpFloor(int target){
        if (target == 1) return 1;
        if (target == 2) return 2;
        if (target == 3) return 3;
        int one = 1;
        int two = 2;
        int result = 0;
        for (int i = 2; i < target; i++) {
            result = one + two;
            one = two;
            two = result;
        }
        return result;
    }
}
```

## 11. 斐波那契数列

### 大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项。 n <= 39

```java
import java.util.Scanner;
import com.sun.java_cup.internal.runtime.Symbol;

public class Main12 {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println(fibinalie(scanner.nextInt()));
    }

    public static int fibinalie(int n){
        int a = 1,b = 1,c = 0;
        if (n < 0){
            return 0;
        }else if(n == 1 || n == 2){
            return 1;
        }else {
            for (int i = 3; i <= n ; i++) {
                c = a + b;
                b = a;
                a = c;
            }
            return c;
        }
    }

}
```

## 12. 10000 的阶乘

+ ### 还记得这是大一学C语言时候，井超老师给我们出的题，当时C语言学的还不咋扎实，所以想了有一段时间，就被搁置了
+ ### 直到看到[Black Bao](http://barackbao.com/)的一篇博客：[求10000的阶乘](http://barackbao.com/2018/03/11/%E6%B1%8210000%E7%9A%84%E9%98%B6%E4%B9%98/) 我才想起来,今天仔细琢磨了琢磨，知道了是咋个一回事
+ ### 利用进位，将阶乘的数据倒着存放于数组当中，涉及到进位的一些让人‘头大’的事情

```c
#include <iostream>
using namespace std;

int main()
{
  int result[40000]; //保存结算结果的数组
  int height = 1;  //结果的最高位
  int num;  //计算阶乘的数字
  cout << "请输入阶乘数：" << endl;
  cin >> num;
  result[0] = 1;
  for (int i = 1;i <= num;i ++)
  {
    int res = 0; //进位
    for (int j = 0;j < height;j ++)
    {
      int buf = result[j] * i + res; //计算结果
      result[j] = buf % 10;  //取当前位
      res = buf / 10;   //计算进位
    }
    //判断是否进位
    while (res)
    {
      result[height ++] = res % 10; //取当前位
      res /= 10;   //计算进位
    }
  }

  for (int k = height - 1;k >= 0;k --)
  {
     cout << result[k];  //数组你想输出
  }
  cout << endl;
  cout << "length = " << height << endl;

}
```

## 13. 数字转化二进制比较有所不同

### 正好在这里复习一下& 、^ 跟 |

```c
  101010        101010        101010
& 011100      | 011100      ^ 011100
----------  -------------  ------------
  001000        111110        110110        ;
```

```c
#include<stdio.h>
#include<stdlib.h>

int main(){
    int num1,num2 = 0;
    scanf("num1 = %d\nnum2 = %d",&num1,&num2);
    char str1[30],str2[30];
    itoa(num1,str1,2);
    itoa(num2,str2,2);
    int ans = num1 ^ num2;
    int count = 0;
    while(ans != 0)
    {
        ans &= (ans - 1);
        count ++;
    }
    printf("%d",count);
    return 0;
}
```