package Test;
import java.util.Scanner;
public class Solution {
    public String replaceSpace(String str) {
        if (str == null) {
            return null;
        }
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) == ' ') {  //如果得到的是个空格
                //添加字符
                sb.append('%');
                sb.append('2');
                sb.append('0');
            } else {
                sb.append(str.charAt(i));  //没有空格的话继续添加
            }
        }
        return sb.toString();
    }
}
