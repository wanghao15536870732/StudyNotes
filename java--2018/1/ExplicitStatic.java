package Thinking.pravite;

class Cup{
    Cup(int marker){
        System.out.println("Cup("+ marker +")");
    }
    void f(int marker){
        System.out.println("f("+ marker +")");
    }
}
class Cups{
    static Cup cup1;
    static Cup cup2;
    static {
        cup1 = new Cup(1);
        cup2 = new Cup(2);
    }
    Cups(){
        System.out.println("Cups()");
    }
}
public class ExplicitStatic {
    public static void main(String[] args) {
        System.out.println("Inside main()");
        Cups.cup1.f(99);//    .....(1)
    }


//    static Cups cups1 = new Cups();  .....(2)
//    static Cups cups2 = new Cups();  .....(2)
}
//无论是(1)还是(2)Cups的静态初始化动作都会的到执行-