class Outer1{
    private String msg = "Hello World";
    class Inner1{
        public void print1(){
            System.out.println(Outer1.this.msg);
        }
    }
    public void fun3(int num){  //外部类普通方法
        class Inner2{    //方法中定义内部类
            public void print2(){
                System.out.println(Outer1.this.msg);
                System.out.println("方法参数：" + num);
            }
        }
        new Inner2().print2();  //内部类实例化对象调用print输出
    }
}
public class TestDemo3 {
    public static void main(String[] args) {
    Outer1.Inner1 in = new Outer1().new Inner1();
        in.print1();
    new Outer1().fun3(100);
    }
}
//外部类.内部类 对象 = new 外部类().new 内部类();
//外部类.this = 外部类当前对象
