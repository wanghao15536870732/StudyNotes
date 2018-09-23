import edu.princeton.cs.algs4.In;

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
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入一个数组：");
        String s1 = scanner.nextLine();
        String[] s2 = s1.split(" ");
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
