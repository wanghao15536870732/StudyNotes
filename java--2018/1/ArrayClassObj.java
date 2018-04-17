package Thinking.pravite;

import java.util.Arrays;

public class ArrayClassObj {
    public static void main(String[] args) {

        Integer[] a = {
                new Integer(1),
                new Integer(2),
                3,  //最后的逗号时可选的
        };
        Integer [] b= {
                new Integer(1),
                new Integer(2),
                3,
        };

        System.out.println(Arrays.toString(a));
        System.out.println(Arrays.toString(b));
    }
}
