package Test;

import java.util.Scanner;

public class Test10 {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String str = scanner.nextLine();
            cutout(str);
        }
    }

    public static void cutout(String str){

        if (str.length() >= 8){
            //输出截取后的数字串
            System.out.println(str.substring(0,8));
            //将原来的数字串，从第八位截取，为下一行做准备
            str = str.substring(8);
            cutout(str);
        }else if ((str.length() > 0)){
            str += "00000000";
            System.out.println(str.substring(0,8));
        }
    }
}

