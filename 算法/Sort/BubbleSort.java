package Sort;

import edu.princeton.cs.algs4.StdDraw;

import java.awt.*;
import java.util.Scanner;

public class BubbleSort {
    public void bubbleSort(int[] str){
        int temp = 0; //用于排序是交换
        for (int i = 0; i < str.length - 1; i++) {
            for (int j = 0; j < str.length - 1 - i; j++) {
                if(str[j] > str[j + 1]){
                    temp = str[j];
                    str[j] = str[j + 1];
                    str[j + 1] = temp;
                }
            }
        }
        for (int k = 0; k < str.length; k++) {
            double x = 1.0 * k / str.length;
            double y = str[k] / 2.0;
            double rw = 0.5 / str.length;
            double rh = str[k] / 2.0;
            StdDraw.setPenColor(Color.black);
            StdDraw.filledRectangle(x,y,rw,rh);
        }
        StdDraw.show();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入一个数组：");
        String s1 = scanner.nextLine();
        String[] s2 = s1.split(",");
        int[] str = new int[s2.length];
        for (int i = 0; i < str.length; i++) {
            str[i] = Integer.valueOf(s2[i]);
        }
        BubbleSort bst = new BubbleSort();
        bst.bubbleSort(str);
        System.out.println("排序后：");
        for (int i = 0; i < str.length; i++) {
            System.out.print(str[i] + " ");
        }
        scanner.close();
    }
}
//49,38,65,97,76,13,27,49,78,34,12,64,5,4,62,99,98,54,56,17,18,23,34,15,35,25,53,51
