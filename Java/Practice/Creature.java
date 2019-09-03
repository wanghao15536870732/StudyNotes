class Creature{
    public Creature(){
        System.out.println("Creature的无参构造器");
    }
}
class Animal extends Creature{
    public Animal(String name){
        System.out.println("Animal带有一个参数的构造器" + "我的名字" + name);
    }
    public Animal(String name,int age){
        this(name);
        System.out.println("Animal带有两个参数的构造器" + "我的年龄" + age);
    }
}
class Parent {
    public String tag = "疯狂的丁逸群";
}
class Derived extends Parent{
    private String tag = "轻量级的杨旭";
}
class BaseClass{
    public int a = 5;
}
