package Sort;

import java.util.Scanner;

/*
* 希尔排序
* 算法先将要排序的一组数按某个增量d（n/2,n为要排序数的个数）分成若干组，每组中记录的下标相差d.
* 对每组中全部元素进行直接插入排序，然后再用一个较小的增量（d/2）对它进行分组，在每组中再进行直接插入排序。
* 当增量减到1时，进行直接插入排序后，排序完成
 */
public class ShellSort {

    public void shellSort(int[] str){
        double length = str.length;
        int temp = 0;
        while(true){
            //向上取整
            length = Math.ceil(length / 2);
            int length2 = (int) length;
            for (int i = 0; i < length2; i++) {
                for (int j = i + length2; j < str.length; j += length2) {
                    int k = j - length2;
                    temp = str[j];
                    for (;k >= 0 && temp < str[k];k -= length2){
                        str[k + length2] = str[k];
                    }
                    str[k + length2] = temp;
                }
            }
            if (length2 == 1)
                break;
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
        ShellSort sst = new ShellSort();
        sst.shellSort(str);
        System.out.println("排序后:");
        for (int i = 0; i < str.length; i++) {
            System.out.print(str[i] + " ");
        }
    }
}
