
/*
* 本程序利用匿名内部类的概念简化了Message接口子类的定义，在主方法中调用fun()方法时
* 直接实例化了接口对象，但由于接口中包含抽象方法，所以需要同时覆写接口中的抽象方法才嫩否正常完成、
* 此时虽然节省了子类，但是带来的小过确实结构混乱*/
interface Message {
    public void print();
}

class MessageImpl implements Message {
    public void print() {
        System.out.println("Hello World!!!");
    }
}

public class TestDemo7 {
    public static void main(String[] args) {
        fun(new MessageImpl());
        fun(new Message() { // 直接实例化接口对象
            public void print() { // 匿名内部类中覆写print()方法
                System.out.println("Hello ZB!!!");
            }
        }); // 传递匿名内部类实例化
    }

    public static void fun(Message msg) { // 接受接口对象
        msg.print();
    }
}
