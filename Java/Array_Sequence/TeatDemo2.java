class Outer{
    private String msg = "Hello World";


    //通过内部类进行调用
//    class Inner{
//        public void print(){
//            System.out.println(msg);
//        }
//    }
//    public void fun(){
//        new Inner().print();  //实例化内部类对象，并且调用print()方法
//    }

  //将内部类放到外部并且实现同样的功能

    public void fun(){
        //this表示当前调用fun()方法的对象，
        // 在本程序主方法中由out对象调用，所以this就是out
        new Inner(this).print();
        //实例化内部类对象，并且调用print方法
    }
    //内部类需要访问msg属性，但由于此属性属于Outer类，
    // 而在Outer类中此属性使用pravate进行封装
    //所以此时要得到这个属性的内容,需要定义一个getter方法
    public String getMsg() {
        return this.msg;
    }
}
class Inner{  //定义一个内部类
    private Outer out;  //必须需要对象才可以调用getMsg()方法
    public Inner(Outer out){    //在构造方法中接受外部对象
        this.out = out;
    }
    public void print(){  //利用Outer类对象调用方法
        System.out.println(this.out.getMsg());
    }
}
public class TeatDemo2 {
    public static void main(String[] args) {
        Outer out = new Outer();   //实例化外部对象
        out.fun();                  //调用外部类方法
    }
}
