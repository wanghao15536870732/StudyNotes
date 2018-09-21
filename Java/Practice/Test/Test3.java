package Test;
/*
Test3
 */
public class Test3 {

    public static void main(String[] args) {
        int num[][] = new  int[3][3];
        int k = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                num[i][j] = k;
                k ++;
            }
        }
        if (Find(num,1)){
            System.out.println("perfect!");
        }else {
            System.out.println("Failed");
        }
    }


    private static boolean Find(int[][] array, int target){
        int len = array.length - 1;
        int i = 0;
        while ((len >= 0) && (i < array[0].length)){
            if (array[len][i] > target) {
                len--;
            }else if (array[len][i] < target){
                i ++;
            }else {
                return true;
            }
        }
        return false;
    }
}
