package Sort;

import java.util.Scanner;
import edu.princeton.cs.algs4.In;

import java.util.ArrayList;
import java.util.List;

/*
基数排序
将所有待比较数值（正整数）统一为同样的数位长度，数位较短的数前面补零。
然后，从最低位开始，依次进行一次排序。这样从最低位排序一直到最高位排序完成以后,数列就变成一个有序序列。
 */
public class RadixSort {
    public void radixSort(int[] str){
        //首先确定排序的趟数
        int max = str[0];
        for (int i = 0; i < str.length; i++) {
            if(str[i] > max){
                max = str[i];
            }
        }
        //自定义次数
        int time = 0;
        //确定max的位数
        while(max > 0){
            max /= 10;
            time ++;
        }

        //建立十个队列
        List<ArrayList> queue = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            ArrayList<Integer> queue1 = new ArrayList<>();
            queue.add(queue1);
        }
        //进行time次分配和收集
        for (int i = 0; i < time; i++) {
            //分配数组元素
            for (int j = 0; j < str.length; j++) {
                //得到数字第time + 1位数
                int x = str[j] % (int) Math.pow(10,i + 1) / (int) Math.pow(10,i);
                ArrayList<Integer> queue2 = queue.get(x);
                queue2.add(str[j]);
                queue.set(x,queue2);
            }
            //元素计数器
            int count = 0;
            //收集队列元素
            for (int k = 0; k < 10; k++) {
                while(queue.get(k).size() > 0){
                    ArrayList<Integer> queue3 = queue.get(k);
                    str[count] = queue3.get(0);
                    queue3.remove(0);
                    count ++;
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
        RadixSort rst = new RadixSort();
        rst.radixSort(str);
        System.out.println("排序后：");
        for (int i = 0; i < str.length; i++) {
            System.out.print(str[i] + " ");
        }
    }
}
//49 38 65 97 76 13 27 49 78 34 12 64 5 4 62 99 98 54 56 17 18 23 34 15 35 25 53 51