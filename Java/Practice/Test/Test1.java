package Test;

import java.util.Scanner;

/*
一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法
* */
public class Test1 {
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
