package Test;

import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        Scanner scanner = new Scanner(System.in);
        String count = solution.replaceSpace(scanner.nextLine());
        System.out.println(count.toString());
    }
}

