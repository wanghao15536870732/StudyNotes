package Test;

import java.util.Scanner;
/*
Test5
 */
public class Test5 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNext()){
            StringBuilder str = new StringBuilder(scanner.next());
            str.reverse();
            System.out.println(str.toString());
        }
    }
}
