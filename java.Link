
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
# java--
