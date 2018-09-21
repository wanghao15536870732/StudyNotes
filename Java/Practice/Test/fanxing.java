package Test;

import java.util.Scanner;
import java.util.TreeSet;
/*
泛型
 */
public class fanxing {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int num = 0;
        while(scanner.hasNext() && num < 10) {

            //记录下输入的数字的数量
            int sum = scanner.nextInt();

            //建立Integer的TreeSet泛型,用它的强大的功能进行排序
            TreeSet<Integer> tree = new TreeSet<>();

            for (int i = 0; i < sum; i++) {
                int number = scanner.nextInt();
                tree.add(number);
            }
            //再进行循环打印
            for (Integer set : tree) {
                System.out.println(set);
            }

            num ++;
        }
    }
}
