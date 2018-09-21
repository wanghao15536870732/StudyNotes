package Thinking.pravite;

class Soup1 {
    private Soup1() {
        System.out.println("哈哈");
    }

    public static Soup1 makeSoup() {
        return new Soup1();
    }
}

class Soup2 {
    private Soup2() {
    }

    private static Soup2 ps1 = new Soup2();

    public static Soup2 access() {
        return ps1;
    }

    public void f() {
        System.out.println("王浩");
    }
}

public class Test {
    void testStatic() {
        Soup1 soup = Soup1.makeSoup();
    }

    void testSingleton() {
        Soup2.access().f();
    }

    public static void main(String[] args) {
        Test test = new Test();
        test.testSingleton();
        test.testStatic();

    }
}
