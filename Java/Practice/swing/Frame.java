package swing;

import java.awt.*;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.stream.IntStream;

public class Frame {
    public static void main(String[] args) {
        Collection c  = new ArrayList();
        //添加元素
        c.add("孙悟空");
        //虽然集合里面不能放基本类型的值，但java支持自动装箱
        c.add(6);
        Collection book = new HashSet();
        book.add("疯狂java讲义");
        book.add("轻量级javaEE企业应用实战");
        book.forEach(o -> System.out.println("迭代集合元素 ：" + o));
        Iterator it = book.iterator();
        IntStream is  = IntStream.builder()
                .add(20)
                .add(14)
                .add(-2)
                .add(18)
                .add(78)
                .build();
        System.out.println("is中所有元素最大的值为：" + is.max().getAsInt());
        Collection book2 = new HashSet();
        book2.add("轻量级javaEE企业应用实战");
        book2.add("疯狂java讲义");
        book2.add("疯狂iOS讲义");
        book2.add("疯狂Ajax讲义");
        book2.add("疯狂Android讲义");
        System.out.println(book2.stream().filter(ele -> ((String) ele).contains("疯狂")).count());
        System.out.println(book2.stream().filter(ele -> ((String) ele).contains("java")).count());
        System.out.println(book2.stream().filter(ele -> ((String) ele).length() > 10).count());
        book2.stream().mapToInt(value -> ((String) value).length())
                .forEach(System.out::println);
        java.awt.Frame f = new java.awt.Frame("测试窗口");
        //创建一个Panel容器
        Panel p = new Panel();
        //向Panel容器添加两个组件
        p.add(new TextField(20));
        p.add(new Button("登陆"));
        //将Panel容器添加到Frame窗口中
        f.add(p);
        //设置窗口的位置和大小
        f.setBounds(30,30,1250,1120);
        //将窗口显示出来(Frame对象默认处于隐藏状态)
        f.setVisible(true);
    }
}
