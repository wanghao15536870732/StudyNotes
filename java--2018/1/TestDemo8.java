class Singleton{
    private static Singleton inst = new Singleton();
    private Singleton(){  //构造方法私有化
    }
    public void print(){
        System.out.println("Hello World.");
    }
    public static Singleton getInst(){  //取得本类对象
        return inst;
    }
}
public class TestDemo8 {
    public static void main(String[] args) {
        Singleton inst = Singleton.getInst();   //利用 "类.static方法()" 取得实例化对象
        inst.print();               //调用方法
    }
}
