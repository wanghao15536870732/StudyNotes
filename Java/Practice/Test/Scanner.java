package Test;

public class Scanner {
    public static void main(String[] args) {
        //从键盘接收数据
        java.util.Scanner scan = new java.util.Scanner(System.in);
        //next的方式接受字符串
        System.out.println("next的方式接受：");
        //判断是否还有输入
        if (scan.hasNext()){
            String str1 = scan.next();
            System.out.println("输出的数据为：" + str1);
        }
        java.util.Scanner scan1 = new java.util.Scanner(System.in);
        //nextLine的方式接受字符串
        System.out.println("nextLine方式接受：");
        if (scan1.hasNextLine()){
            String str2 = scan1.nextLine();
            System.out.println("输出的数据为：" + str2);
        }
    }
}
