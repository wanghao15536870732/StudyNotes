package Test;

import java.util.Scanner;
/*
字母大小写转换
 */
public class Test13 {
    public static int getCount(String str,char c){
        int count = 0;
        if (str != null && str.length() > 0){
            for (int i = 0; i < str.length(); i++) {
                char at = str.charAt(i);
                if (c == at){
                    count ++;
                }else if ((at >= 'A') && (at <= 'Z') && (c == at + 32)){
                    count ++;
                }else if ((at >= 'a') && (at <= 'z') && (c == at - 32)){
                    count ++;
                }
            }
        }else {
            count =  0;
        }
        return count;
    }

    public static void main(String[] args) {
        Scanner scr = new Scanner(System.in);
        String str = scr.next();
        char c = scr.next().charAt(0);
        System.out.println(getCount(str,c));
    }
}
