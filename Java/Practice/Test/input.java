package Test;

import java.util.Scanner;

public class input {
    public static int sertch(String s,char c){
        int count = 0;
        if (s != null && s.length() > 0){
            for (int i = 0; i < s.length(); i++) {
                if (c == s.charAt(i)){
                    count ++;
                }
            }
        }else {
            count = 0;
        }
        return count;
    }
    public static void main(String[] args) {
        Scanner sca = new Scanner(System.in);
        String str = sca.next();
        System.out.println(str);
        char c = sca.next().charAt(0);
        System.out.println(c);
        System.out.println(sertch(str,c));
    }
}
