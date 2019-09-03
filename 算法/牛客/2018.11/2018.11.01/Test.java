package Test;

import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        int [][] a  = {{0,1,2,3,4},{5,6,7,8,9},{9,10,11,12,13}};
        Solution solution = new Solution();
        System.out.println(solution.Find(110,a));  //返回false
        System.out.println(solution.Find(7,a));    //返回true
    }
}

