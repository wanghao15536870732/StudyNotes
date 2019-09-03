

/**
* 本程序利用匿名内部类的概念简化了Message接口子类的定义，在主方法中调用fun()方法时
* 直接实例化了接口对象，但由于接口中包含抽象方法，所以需要同时覆写接口中的抽象方法才嫩否正常完成、
* 此时虽然节省了子类，但是带来的小过确实结构混乱*/
interface Message{
    public void print();
}
class MyInt{
    private int num;
    /*
    * 包装类是为了基本数据类型准备的，所以构造方法只需要接受一个数字
    * @param num*/
    public MyInt(int num){
        this.num = num;
    }
    /**
     * 通过包装类取得所包装的基本数据类型
     * @return 保证的数据
     */
    public int intValue(){   //将包装的内容返回
        return this.num;
    }
}
class MessageImpl implements Message{
    public void print(){
        System.out.println("Hello World!!!");
    }
}
public class TestDemo7 {
    public static void main(String[] args) {
        fun(new MessageImpl());
        fun(new Message(){    //直接实例化接口对象
            public void print(){       //匿名内部类中覆写print()方法

                System.out.println("Hello ZB!!!");
            }
        });   //传递匿名内部类实例化
    }
    public static void fun(Message msg){  //接受接口对象
        msg.print();


        System.out.println("------------");
        MyInt mi = new MyInt(10);
        int temp = mi.intValue();    //将对象中包装的数据取出
        System.out.println(temp * 2);    //输出 20
        Integer ier = new Integer(30);
        int temp1 = ier.intValue();
        System.out.println(temp1 * 2);    //输出 60


        System.out.println("-------------");
        Integer obja1 = 10;           //直接装箱实例化
        Integer obja2 = 10;           //直接装箱实例化
        Integer obja3 = new Integer(10);
        System.out.println(obja1 == obja2);    //输出 true
        System.out.println(obja1 == obja3);    //输出 false
        System.out.println(obja2 == obja3);    //输出 falue
        System.out.println(obja1.equals(obja2));  //输出 ture
        /**如果使用直接装箱实例化的方式，会使用同一块对内存空间
         * 而使用了构造方法的包装类对象，会开辟新的堆内存空间
         *在进行包装类数据相等比较时，最可靠的方法还是equals()
         */

        System.out.println("-----------");
        Object ob = 10; //先自动装箱后再向上转型，此时不能进行数学计算
        //Object不能直接向下转型为int
        //所以要取出基本数据类型必须首先向下转型为指定的包装类
        int temp3 = (Integer) ob;    //向下转型为Integer后自动拆箱
        System.out.println(temp3 * 2);
    }
}
