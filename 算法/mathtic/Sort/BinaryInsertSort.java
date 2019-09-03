package Sort;

import java.util.Scanner;

/*
二分插入排序
原理：将数组分为两部分开始进行插入排序
 */
public class BinaryInsertSort {

    public void binaryInsertSort(int[] str) {
        for (int i = 1; i < str.length; i++) {
            if (str[i] < str[i - 1]) {
                // 定义temp储存将要插入的数
                int temp = str[i];
                int left = 0; // 定义左边的数，从str[0]开始
                int right = i - 1; // 定义最右边的
                while (left <= right) {
                    int mid = (left + right) / 2; // 定义mid中间位
                    if (str[mid] < temp) { // 中间位与str[i]比较
                        left = left + 1;
                    } else { // 通过if语句找到应该插入的位置str[left]
                        right = right - 1;
                    }
                }
                for (int j = i; j > left; j--) { // 将 str[left]->str[i - 1] 的数都向后挪一位
                    str[j] = str[j - 1];
                }
                str[left] = temp; // 最后将str[i] 插入 str[left]
            }
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
        BinaryInsertSort bis = new BinaryInsertSort();
        bis.binaryInsertSort(str);
        System.out.println("排序后：");
        for (int i = 0; i < str.length; i++) {
            System.out.print(str[i] + " ");
        }
        scanner.close();
    }
}
