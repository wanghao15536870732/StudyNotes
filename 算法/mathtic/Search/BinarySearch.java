package Search;

import java.util.Scanner;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import java.util.Arrays;
/*
二分查找
 */
public class BinarySearch {
    public static int rank(int key,int[] str){
        //录入的数组必须时有序的
        int front = 0;
        int rear = str.length - 1;
        while (front <= rear){
            //被查找的键要么不存在，要么必然在str[front ... rear]之中
            int middle = front + (rear - front) / 2;
            if(key < str[middle])
                rear = middle - 1;
            else if(key > str[middle])
                front = middle + 1;
            else
                return middle;
        }
        return -1;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入一个数组：");
        String s1 = scanner.nextLine();
        String s2[] = s1.split(" ");
        int[] str = new int[s2.length];
        for (int i = 0; i < str.length; i++) {
            str[i] = Integer.valueOf(s2[i]);
        }
        Arrays.sort(str);
        Scanner scanner1 = new Scanner(System.in);
        String s3 = scanner1.next();
        int key = Integer.valueOf(s3);
        if(rank(key,str) < 0)
            System.out.println("该数组当中没有"+ key + "这个数值！");
        else
            System.out.println("查找成功！");
    }
}
