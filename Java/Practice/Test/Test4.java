package Test;


import java.util.Scanner;
/*
Test4
 */
public class Test4 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String str  = scanner.nextLine();
        String string = change(str);
        System.out.println(string);
    }

    public static String change(String str){
        if (str == null){
            return null;
        }
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) == ' '){
                sb.append('%');
                sb.append('2');
                sb.append('0');
            }else {
                sb.append(str.charAt(i));
            }
        }
        return sb.toString();
    }
}
