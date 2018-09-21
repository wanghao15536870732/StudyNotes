package Test;


import java.util.Scanner;

public class Test11 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String str = scanner.nextLine();
        String string = reverse(str);
        System.out.println(string);
    }

    public static String reverse(String str){

        String[] s = str.split(" ");
        StringBuilder sb = new StringBuilder();
        for (int i = s.length - 1; i > 0 ; i --) {
            sb.append(s[i]);
            sb.append(" ");
        }
        sb.append(s[0]);
        return sb.toString();
    }
}

