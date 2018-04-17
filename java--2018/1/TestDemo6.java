
/*
* Object 类中默认的equals()方法实现比较的是两个对象的内存地址数值
* 但这并不符合真正的对象比较(还需要比较对象的内容)
**/

class Books extends Object{   //此类为object的子类
    private String title;
    private double price;
    public Books(String title,double price){
        this.price = price;
        this.title = title;
    }
    public boolean equals(Object obj){
        if(this == obj){    //如果地址是相同的
            return true;
        }
        if(obj == null){   //如果对象内容为null
            return false;
        }
        if(!(obj instanceof Books)){  //不是本类的实例
            return false;
        }
        Books book = (Books)obj;  //向下转型
        if(this.title.equals(book.title) && this.price == book.price){
            return true;
        }
        return false;
    }
    public String toString(){
        return "书名：" + this.title + ",价格：" + this.price;
    }
}


class Link2 {
    private class Node{
        private Object data;
        private Node next;
        public Node(Object data){
            this.data = data;
        }
        /*
        * 设置新结点的保存，所有新结点保存在最后一个结点之后
        * @param newNode 新结点对象
        * */
        public void addNode(Node newNode){
            if (this.next == null) {
                this.next = newNode;
            }else{
                this.next.addNode(newNode);
            }
    }

    /*
    * 数据检索操作,判断制定数据是否存在*/

    public boolean containsNode(Object data){
            if(data.equals(this.data)){
                return true;
            }else{
                if(this.next != null){    //如果有后续结点
                    return this.next.containsNode(data);    //递归调用继续查询
                }else{           //没有后续结点
                    return false;
                }
            }
        }

        /*
        * 根据索引取出数据
        * @param index 要取得数据的索引编号*/

        public Object getNode(int index){
            if(Link2.this.foot++ == index){
                return this.data;
            }else{
                return this.next.getNode(index);
            }
        }

        /*
        * 修改指定索引结点包含的数据*/

        public void setNode(int index,Object data){
            if (Link2.this.foot ++ == index){
                this.data = data;
            }else {
               this.next.setNode(index,data);
            }
        }
        /*
        * 结点删除操作
        * @param previous 当前结点的上一个结点
        * @param data 想要删除的数据*/
        public void removeNode(Node previous,Object data){
            if(data.equals(this.data)){
                previous.next = this.next;  //空出当前结点
            }else {
                this.next.removeNode(this,data);
            }
        }

        /*
        * 将节点中保存的数据转化为对象数组*/

        public void toArrayNode(){
            Link2.this.retArray[Link2.this.foot ++] = this.data;   //取出元素并保存到数组中
            if(this.next != null){         //有后续元素
                this.next.toArrayNode();   //继续下一个数据的取得
            }
        }
    }

    //------------------------------以上为内部类-------------------------------------
    private Node root;   //根节点定义
    private int count = 0;  //保存元素的个数
    private int foot = 0;   //结点索引
    private Object[] retArray;  //返回的数组

    /*
    * 用户向链表增加新的数据，在增加要将数据封装为Node类，这样才能匹配节点数据
    * */

    public void add(Object data){
        if(data == null){
            return;
        }
        Node newNode = new Node(data);  //要保存的数据
        if(this.root == null){      //当前没有根结点
            this.root = newNode;   //保存根节点
        }else {
            this.root.addNode(newNode);    //交给Node类来查询
        }
        this.count ++;
    }

    /*
    * 获取链表中保存的数据个数*/

    public int size(){
        return count;
    }
    /*
    *判断是否为空链表*/
    public boolean isEmpty(){
        return this.count == 0;
    }

    /*
    * 数据查询操作*/

    public boolean contains(Object data){
        if(data == null || this.root == null){
            return false;
        }
        return this.root.containsNode(data);  //交给Node类来查询
    }
    /*
    * 根据索引取得你保存的节点数据*/
    public Object get(int index){
        if(index > this.count){
            return null;
        }
        this.foot = 0;
        return this.root.getNode(index);
    }

    /*
    * 根据索引修改数据*/
    public void set(int index,Object data){
        if(index > this.count){  //判断是否超过了保存的范围
            return;
        }
        this.foot = 0;
        this.root.setNode(index,data);
    }

    /*
    * 链表数据的删除操作,再删除前先使用contains判断链表中是否存在指定数据
    * 如果要删除的数据存在，则首先判断根节点的数据是否为要删除的结点
    * 如果是，则将根节点的下一个数据作为子新的结点*/

    public void remove(Object data){
        if(this.contains(data)){    //判断数据是否存在
            if(data.equals(this.root.data)) {
                this.root = this.root.next;   //空出当前结点
            }else{                           //根节点不是想要删除的数据
                //此时根元素已经判断过了，从第二个元素开始判断，即第二个元素的上一个元素作为根节点
                this.root.next.removeNode(this.root,data);
            }
            this.count --;   //删除成功后个数要减少
        }
    }
    /*
    * 将链表中的数据转换为对象数组进行输出
    * */
    public Object[] toArray(){
        if(this.root == null){
            return null;
        }
        this.foot = 0;
        this.retArray = new Object[this.count];
        this.root.toArrayNode();  //交给Node类进行处理
        return this.retArray;//返回数组对象
    }
    /*
    * 清空链表数据
    * */
    public void clear(){
        this.root = null;
        this.count = 0;
    }
}

public class TestDemo6 {
        public static void main(String[] args){
            Object objb = "hello";     //向上转型，接受String子类对象
            Object obja = new Books("java第一行代码",89.00);   //向上转型,接受Book子类对象
            Object objc = new Books("疯狂java讲义",199.00);
            Object objd = new Books("java第一行代码",89.00);
            //Books b = (Books) obja;    //测试向下转型
            //String s = (String) objb;  //测试向下转型
            System.out.println(obja);
            System.out.println(obja.toString());
            System.out.println(objb);
            System.out.println("----------------------------");
            System.out.println(obja.equals(objb));
            System.out.println(obja.equals(objc));
            System.out.println(obja.equals(objd));
            System.out.println("------------------------------");
            Object obj = new int[]{1,2,3};   //向上转型
            System.out.println(obj);
            //数组编码 [I@4554617c  //数组直接输出的对象信息，都会增加一个[,而第二个则表示的是数组的类型
            if (obj instanceof int[]){
                int date[] = (int []) obj;
                for (int i = 0; i < date.length; i++) {
                    System.out.print(date[i] + "、");
                }
            }
            System.out.println("接下来是链表操作");
            System.out.println("------------------------------------");
            Link2 all = new Link2();
            all.add("A");
            all.add("E");
            all.add("D");
            all.add("V");
            all.add("C");
            Object data[] = all.toArray();   //将链表转化为对象数组
            for (int i = 0; i < data.length; i++) {
                String str = (String) data[i];   //Object变成String
                System.out.print(data[i] + "、");
            }
        }
}
/*
*中北大学--大数据学院--计算机类--1707004716王浩
* 辽宁大学--闫靓璐
* 冀州一中--侯越
* */