import java.io.File;

interface USB{
    public void start();
    public void stop();
}
class Computer{
    public void plugin(USB usb){
        usb.start();
        usb.stop();
    }
}
class Flash implements USB{
    public void start(){
        System.out.println("U盘开始使用");
    }
    public void stop(){
        System.out.println("U盘停止使用");
    }
}
class Print implements USB{
    public void start(){
        System.out.println("打印机开始工作");
    }
    public void stop() {
        System.out.println("打印机停止使用");
    }
}
interface Fruit{  //定义接口
    public void eat();
}
class Apple implements Fruit{   //定义接口子类
    public void eat(){
        System.out.println("*** 吃苹果。");
    }
}
class Orange implements Fruit{
    public void eat(){
        System.out.println("*** 吃橘子。");
    }
}
//工厂设计模式
class Factory{    //定义工厂类，此类不属于属性
    /*
    * 取得指定类型的接口对象
    * @param className 要取得的类实例化对象标记
    * @return 如果指定标记存在，则Fruite接口实例化对象，否则返回 null
    */
    public static Fruit getInstance(String className){
        if("apple".equals(className)){   //判断是否是苹果类
            return new Apple();
        }else if("orange".equals(className)){
            return new Orange();
        }else{
            return null;
        }
    }
}
public class TestDemo5{
    public static void main(String[] args) {
        Computer com = new Computer();
        com.plugin(new Flash());
        com.plugin(new Print());
        Fruit f = new Apple();  //子类实例化父类对象
        f.eat();               //调用被覆写的方法
        System.out.println("-----------------------");
        Fruit f1 = Factory.getInstance("orange");   //通过工厂类取得指定标记的对象
        f1.eat();                           //调用接口方法
        Fruit f2 = Factory.getInstance("apple");
        f2.eat();
    }
}

