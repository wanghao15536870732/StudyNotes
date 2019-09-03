package Thinking.pravite;

class Window{
    Window(int maker){
        System.out.println("Window("+ maker +")");
    }
}
class House{
    //在构造器之前声明对象
    Window w1 = new Window(1);
    House(){
        //表示我们在构造器中
        System.out.println("House()");
        w3 = new Window(33);
    }
    Window w2 = new Window(2);
    void f(){
        System.out.println("f()");
    }
    Window w3 = new Window(3);
}
public class OrderOfInitialization {
    public static void main(String[] args) {
        House h = new House();
        h.f();
    }
}
