import org.omg.CORBA.PUBLIC_MEMBER;

class Book{
    private String title;
    private double price;
    public Book(String title,double price){
        this.title = title;
        this.price = price;
    }
    //对象比较实现
    public boolean compare(Book book) {
        if (book == null) {
            return false;
        }
        //执行b4.compare(b5)代码时会有两个对象
        // 当前对象this(调用方法对象，就是b4引用)
        //传递的对象book(引用传递，就是b5引用)
        if (this == book){  //内存地址比较
            return true;
        }
        if (this.title.equals(book.title)
                && this.price == price){   //属性判断
            return true;
        }else {
            return false;
        }
    }
    public void setTitle(String title) {
        this.title = title;
    }
    public String getTitle() {
        return title;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public double getPrice() {
        return price;
    }
}
class Info{
    private String msg = "Hello!";
    public void print(){
        System.out.println("msg = " + msg);
    }
    public void fun(Info temp){  //本类接受本类对象
        temp.msg = "wnaghao";    //在累的内部直接利用对象访问私有属性
    }
}
class Book2{
    private String title;
    private double price;
    static String pub = "清华大学出版社";
    public Book2(String title,double price){
        this.title = title;
        this.price = price;
    }
    public static void setPub(String p){    //定义static方法可以用类名称直接调用
        pub = p;
    }
    public String getInfo(){
        return "图书名称：" + this.title + ",图书价格：" + this.price + ",出版社：" + this.pub;
    }
}
class MyMath{   //数学操作类，类中没有属性
    public static int add(int x,int y){   //只是一个加法操作
        return x + y;
    }
}
public class TestDemo {
    public static void main(String args[]) {
        for (int i = 0; i < args.length; i++) {
            System.out.println(args[i]);
        }
        Book b1 = new Book("java开发",79.8);
        Book b2 = new Book("Android开发",99.9);
        if (b1.getTitle().equals(b2.getTitle())
                && b1.getPrice() == b2.getPrice()){  //属性比较不知道为啥不能两个都是equals
            System.out.println("是同一个对象!");
        }else{
            System.out.println("不是同一个对象！");
        }
        Info In = new Info();
        In.fun(In);  //没有意义，只是一个语法验证
        In.print();
        Book b4 = new Book("java开发",78.9);
        Book b5 = new Book("java开发",78.9);
        if (b4.compare(b5)) {
            System.out.println("是同一个对象！");
        }else {
            System.out.println("不是同一个对象！");
        }
    Book2 ba = new Book2("明明白白学通C语言",44.4);
    Book2 bb = new Book2("数据结构",55.6);
    Book2 bc = new Book2("算法导论",77.8);
    ba.pub = "中北大学出版社";          //修改static属性的内容
        System.out.println(ba.getInfo());
        System.out.println(bb.getInfo());
        Book2.setPub("青界中学");    ///定义static方法可以用类名称直接调用
        System.out.println(bc.getInfo());
        System.out.println(Book2.pub);    //static属性不受实例化对象的控制
        Book2.pub = "沙河一中出版社";     //在没有实例化对象的情况下，依然可以修改static属性的内容
        Book2 bd = new Book2("Unity",55);
        System.out.println(bd.getInfo());
        fun();   //static方法调用static方法
        new TestDemo().fun2();      //对象调用方法
    }
    public static void fun(){   //static定义的方法
        System.out.println("Hello World!");
    }
    public void fun2(){
        System.out.println("bububu");
        System.out.println(MyMath.add(10,20));  //直接调用
        }
}
//严格意义上来讲，String是一个类。
//所以equals()完成的就是对象比较操作，
// 具备null的验证,为null时直接返回false

