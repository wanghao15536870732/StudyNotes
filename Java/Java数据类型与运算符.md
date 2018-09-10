
# Java数据类型与运算符

+ ## 一个数 异或同一个数两次，结果还是那个数>
+ ## << : 其实就是乘以2的移动的次数次幂
+ ## >> : 就是除以2移动的位数次幂
+ ## >> : 最高位补什么有原有数据的最高位置决定，
+ ## 如果最高位0，右移后，用0补空位。 
+ ## 如果最高位1，右移后，用1补空位。
+ ## << : 无论最高位是什么，右移后，都用0补。

```java
public class ShiftTest {
    public static void main(String[] args){
        int a = 0b1001_1101;    //十进制157
        int b = 0b0001_1101;    //十进制57
        System.out.println(a);
        // !!!!!!!!!!!!!!(红色的感叹号)
        System.out.println(a << 3);  //左移三位（带符号)
        // 157
        System.out.println(a >> 3); //右移三位 (带符号)
         // 1256
        System.out.println(a >>> 3);  //右移三位(不带符号)
        // 19
        System.out.println(~a);  //按位取反
        // 158
        System.out.println(a & b);  //按位或
        // - 29
        System.out.println(a | b);  //按位与
        //  157
        System.out.println(a ^ b);  //按位异或
        //  128
        System.out.println(Integer.toBinaryString(-13));
        //  11111111111111111111111111110011
        System.out.println(6 ^ 5);
        // 3
        int grade;
        grade = 10;
        if (grade >= 60)    //条件表达式的值应为布尔类型
            System.out.println("passed");
        else
            System.out.println("failed");
        // failed
        String []sa = {"何以" + "解忧","唯有Java!"};
        for (int i = 0; i < sa.length; i++) {
            System.out.println(sa[i]);
        }
        // 何以解忧 
        // 唯有Java!
        System.err.println("!!!!!!!!!!!!!!"); //输出的信息为红色
       System.out.printf("n1 = %.2f\tn2 = %6.2f\n",100,200);
       System.out.printf("E = % 2$ .2f\tPI = % 1$ 6.4f\n", Math.PI, Math.E);
       System.out.printf(" % 2$ d\t% 1$ d\n",100,200);
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= i; j++) {
                System.out.print(i + "*" + j + "=" + i * j + "\t");
            }
            System.out.println();
        }
    }
}

```