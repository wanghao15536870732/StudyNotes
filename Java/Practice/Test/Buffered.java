package Test;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Buffered {

    public static void main(String[] args) throws IOException {
        //先读取用户的输入
        java.io.BufferedReader br = new java.io.BufferedReader(new InputStreamReader(System.in));
        //再把用户的输入转换成字符类型的数组
        char[] strArr = br.readLine().toCharArray();
        //所有字母一共128个,用于记录英文字母出现的次数
        int[] countArr = new int[128];
        for (int i = 0; i < strArr.length; i++) {
            if (('A' <= strArr[i] && strArr[i] <= 'Z' ) ||  (strArr[i] >= 'a' && strArr[i] <= 'z')){
                //用int类型的数组存放果然字幕出现的次数
                ++ countArr[strArr[i]];
                if (countArr[strArr[i]] == 3){
                    System.out.println(strArr[i]);
                    break;
                }
            }
        }
    }
}
