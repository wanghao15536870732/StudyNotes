import java.util.Scanner;

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


