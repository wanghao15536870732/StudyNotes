package Test;

public class Sort {
    public static void main(String[] args) {
        int[] a = {2, 4, 6, 8, 3, 6, 9, 12};
        doSomething(a, 0, a.length - 1);
        for (int i = 0; i <= a.length - 1; i++)
            System.out.print(a[i] + " ");
    }

    private static void doSomething(int[] a, int start, int end) {
        if (start < end) {
            int p = core(a, start, end);
            doSomething(a, start, p - 1);
            doSomething(a, p + 1, end);
        }
    }

    private static int core(int[] a, int start, int end) {
        int x = a[end];
        int i = start;
        for (int j = start; j <= end - 1; j++) {
            if (a[j] >= x) {
                swap(a, i, j);
                i++;//交换了几次
            }
        }//把最大的放到最后
        swap(a, i, end);//把最大的放到i的位置
        return i;
    }

    private static void swap(int[] a, int i, int j) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}
