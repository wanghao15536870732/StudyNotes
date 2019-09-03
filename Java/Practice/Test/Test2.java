package Test;

import java.util.Scanner;
import com.sun.java_cup.internal.runtime.Symbol;
/*
斐波那契数列
* */
public class Test2 {

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
