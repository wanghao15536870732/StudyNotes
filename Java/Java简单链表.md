# Java简单链表

```java
class Node{
    private String data;
    private Node next;
    public Node(String data){   //必须有数据才有Node
        this.data = data;
    }
    public void setNext(Node next) {
        this.next = next;
    }
    public Node getNext() {
        return next;
    }
    public void setData(String data) {
        this.data = data;
    }
    public String getData() {
        return data;
    }
}
class Node2{
    private String data;
    private Node2 next;
    public Node2(String data){
        this.data = data;
    }
    public String getData() {
        return this.data;
    }
    public Node2 getNext() {
        return this.next;
    }
    /*
    * 实现节点的增加(递归调用，目的是将新结点保存到最后一个结点之后)
    * 第一次调用(Link):this = Link.root
    * 第二次调用(Link):this = Link.root.next
    * 第三次调用(Link):this = Link.root.next.next
    * @param newNode2 新结点，结点抽象由Link类创建
    * */
    public void addNode(Node2 newNode2){
        if(this.next == null){   //当前结点的下一个为null
            this.next = newNode2;  //保存新结点
        }else {                     //当前结点之后还存在结点
            this.next.addNode(newNode2);  //当前结点的下一个节点继续保存
        }
    }/*
    * 递归的方式输出每个结点保存的数据
    * 第一次调用(Link):this = Link.root
    * 第二次调用(Link):this = Link.root.next
    * 第三次调用(Link):this = Link.root.next.next
    * @param newNode2 新结点，结点抽象由Link类创建
    * */
    public void printNode2(){
        System.out.println(this.data);    //输出当前结点数据
        if(this.next != null){            //判断下一个节点
            this.next.printNode2();      //找到下一个节点递归输出
        }
    }
}

class Link{    //负责数据的设置和输出
    private Node2 root;            //根节点
    /*
    * 向链表中增加新的数据,如果当前链表没有结点则将下一个数据作为结点
    * 如果有节点则使用Node类将新结点保存到最后一个结点之后
    * @param data 要保存的数据*/
    public void add(String data){
        Node2 newNode2 = new Node2(data); //设置数据的先后关系所以将data包装在一个Node类对象中
        if (this.root == null){             //一个链表只有一个根节点
           this.root = newNode2;            //将新的结点设置为根节点
        }else {                             //根节点已将存在
            this.root.addNode(newNode2);   // 交由Node类来进行结点保存
        }
    }
    public void print(){   //输出数据
        if (this.root != null){    //存在根节点
            this.root.printNode2();   //交给Node类进行输出
        }
    }
}
public class TestDemo4 {
    public static void main(String[] args) {
        Node root = new Node("火车头");
        Node n1 = new Node("车厢A");
        Node n2 = new Node("车厢B");
        Node n3 = new Node("车厢C");
        root.setNext(n1);
        n1.setNext(n2);
        n2.setNext(n3);
        Node p = root;
        while(p != null)
        {
            System.out.println(p.getData());
             p = p.getNext();
        }
        System.out.println("-----------------");
        print(root);
        System.out.println("-----------------------");
        Link link = new Link();
        link.add("中北大学");
        link.add("大数据需学院");
        link.add("七班");
        link.add("1707004716王浩");
        link.print();
    }
    public static void print(Node p){
        if(p == null){
            return;
        }
        System.out.println(p.getData());
        print(p.getNext());   //递归操作
    }
}
```

```java
结果 :

火车头
车厢A
车厢B
车厢C
-----------------
火车头
车厢A
车厢B
车厢C
-----------------------
中北大学
大数据需学院
七班
1707004716王浩
```