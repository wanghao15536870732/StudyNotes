package Sort;

import java.util.Scanner;

/*
归并排序
归并（Merge）排序法是将两个（或两个以上）有序表合并成一个新的有序表，
即把待排序序列分为若干个子序列，每个子序列是有序的。然后再把有序子序列合并为整体有序序列。
 */
public class MergingSort {
    public void sort(int[] str,int left,int right){
        if(left < right){
            //找出中间索引
            int center = (left + right) / 2;
            //对左边的数据进行递归
            sort(str,left,center);
            //对右边的数据进行递归
            sort(str,center + 1,right);
            //合并
            merge(str,left,center,right);
        }
    }

    public void merge(int[] str,int left,int center,int right){
        int[] str1 = new int[str.length];
        int mid = center + 1;
        //用 temp1、temp2 记录中间数组的索引值
        int temp1 = left;
        int temp2 = left;
        while (left <= center && mid <= right){
            //从两个数组当中取出最小值放入中间数组
            if (str[left] < str[mid]){
                str1[temp1 ++] = str[left ++];
            }else {
                str1[temp1 ++] = str[mid ++];
            }
        }
        //剩余部分依次放入中间数组
        while (mid <= right){
            str1[temp1 ++] = str[mid ++];
        }
        while (left <= center){
            str1[temp1 ++] = str[left ++];
        }

        //将中间数组当中内容复制会原数组
        while (temp2 <= right){
            str[temp2] = str1[temp2 ++];
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
        MergingSort mst = new MergingSort();
        mst.sort(str,0,str.length - 1);
        System.out.println("排序后：");
        for (int i = 0; i < str.length; i++) {
            System.out.print(str[i] + " ");
        }
        scanner.close();
    }

}
