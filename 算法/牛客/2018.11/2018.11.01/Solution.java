package Test;
import java.util.Scanner;
public class Solution {
    public boolean Find(int target, int [][] array) {
        int len = array.length - 1;   //数组长度
        int i = 0;
        while ((len >= 0) && (i < array[0].length)){
            if (array[len][i] > target) {  //列查找，从上到下
                len --;
            }else if (array[len][i] < target){
                i ++;  //行查找，从左到右
            }else {
                return true;   //查找到了该数据，返回true
            }
        }
        return false;   //没有查找到，返回false
    }
}
