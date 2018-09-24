package Sort;

import java.util.Scanner;
/*
选择排序
原理: 在要排序的一组数中，选出最小的一个数与第一个位置的数交换;
然后在剩下的数当中再找最小的与第二个位置的数交换，如此循环到倒数第二个数和最后一个数比较为止
 */
public class SelectSort {
    public void selectSort(int[] str){
        int temp = 0;// 用于数据交换时的中间常量
        for (int i = 1; i <= str.length - 1; i++) {
            int position = 0; //定义常量用于保存最大数的下标
            for (int j = 1; j <= str.length - i; j++) {
                if(str[position] < str[j]){
                    position = j; //将大于str[position]的数的下标赋给position
                }
            }
            //如果对应的下标不符合，就开始交换
            if (position != str.length - i){
                temp = str[str.length - i];
                str[str.length - i] = str[position];
                str[position] = temp;
            }
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入一个数组：");
        String s1 = scanner.nextLine();
        String[] s2 = s1.split(" ");
        int[]str = new int[s2.length];
        for (int i = 0; i < str.length; i++) {
            str[i] = Integer.valueOf(s2[i]);
        }
        SelectSort sst = new SelectSort();
        sst.selectSort(str);
        System.out.println("排序后：");
        for (int i = 0; i < str.length; i++) {
            System.out.print(str[i] + " ");
        }
        scanner.close();
    }
}
