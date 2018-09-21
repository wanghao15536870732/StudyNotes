package Test;

import java.util.Scanner;
import java.math.*;
/*
水仙花数
 */
public class Test8 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNext()){
            int num = scanner.nextInt();
            int i = num / 100;
            int j = ( num - i * 100 ) / 10;
            int k = num % 10;
            if (Math.pow(i,3) + Math.pow(j,3) + Math.pow(k,3) == num)
                System.out.println("1");
            else
                System.out.println("0");
        }
    }
}
