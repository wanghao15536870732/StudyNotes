class A{
    public void print(){
        System.out.println("A---public void print(){}");
    }
}
class B extends A{
    public void print(){
        System.out.println("B---public void print(){}");
    }
    /*
    * 在子类中扩充一个新的方法，但是此方法只能由子类对象调用
    * 父类对象不能调用*/
    public void funB(){
        System.out.println("B---扩充的funB()方法");
    }
}
abstract class As{
    public void fun1(){
        System.out.println("有方法体的方法");
    }
    public abstract void print1();
}
class Bs extends As{
    public void print1(){
        System.out.println("Hello World");
    }
}

/*
* 1.抽象类继承子类里面会有明确的方法覆写要求,而普通类没有
*
* 2.抽象类只是比普通类多了一些抽象方法的定义
*
* 3.普通类对象可以直接实例化,但是抽象类的对象必须经过向上转型后才能得到实例化对象
*
* 4.抽象类必须由有子类,因此抽象类不能用final定义
*
* 5.抽象类没有任何抽象方法,不能直接使用new来实例化对象
*
* 6.在抽象类中,如果定义了static属性或方法时,就可以在没有对象的时候直接调用
*
* 7.static定义的内部类属于外部类
*
* 8.一个抽象类只能继承一个抽象类的父类，而接口没有这个限制，一个接口可以继承多个父接口
*
* 9.一个子类只能集成一个抽象类，却可以实现多个接口。多用于解决单继承局限的问题*/
abstract class E{
    public static void print(){    //static方法不受实例化对象的限制
        System.out.println("王浩");
    }
}
public class TestDemocrats {
    public static void main(String[] args) {
        A a = new B();
        a.print();         //在此处无法调用b类中扩充的那个方法
        System.out.println();
        System.out.println("------------------------------------");
        fun(new B());       //向上转型,只能调用父类中定义的方法
        System.out.println();
        System.out.println("------------------------------------");
        As a1 = new Bs();    //向上转型
        a1.print1();          //被子类覆写过的方法
        System.out.println("-------------------------------------");
        E.print();
    }
    public static void fun(A a){
        a.print();
        if(a instanceof B) {    //判断a对象是否是B类的实例
            B b = (B) a;     //要调用子类的特殊操作,需要向下转型
            b.funB();       //调用子类的扩充的方法
        }
    }
}
