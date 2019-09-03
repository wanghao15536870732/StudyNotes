package Test;
/*
线程
 */
public class Test9 extends Thread{

    private int i;

    public void run(){
        for (; i < 100; i++) {
            //当线程继承Thread时，直接使用This就可获得当前线程
            //Thread对象的getName()方法返回当前线程的的名字
            //
            System.out.println(getName() + " " + i);
        }
    }

    public static void main(String[] args) {
        for (int i = 0; i < 100; i++) {

            //调用Thread的currentThread()方法获取当前线程
            System.out.println(Thread.currentThread().getName() + " " + i);

            if (i == 20){
                //创建并启动第一个线程
                new Test9().start();
                new Test9().start();
            }
        }
    }

}
