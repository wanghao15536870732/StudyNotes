package Sort;

import java.util.Scanner;

/*
 * 插入排序
 * 原理：在要排序的一组数中，假设前面(n-1) [n>=2] 个数已经是排好顺序的，现在要把第n个数插到前面的有序数中，
 * 使得这n个数也是排好顺序的。如此反复循环，直到全部排好顺序。
 * */
public class InsertSort {
    public void insertSort(int[] str){
        int temp = 0;
        for (int i = 1; i < str.length; i++) {
            int j = i - 1;
            temp = str[i]; //保存数据
            for (;j >= 0 && temp < str[j]; j --){
                str[j + 1] = str[j];  //将大于temp的值整体后移一个单位
            }
            str[j + 1] = temp;
        }
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
        InsertSort ist = new InsertSort();
        ist.insertSort(str);
        System.out.println("排序后：");
        for (int i = 0; i < str.length; i++) {
            System.out.print(str[i] + " ");
        }
    }
}


