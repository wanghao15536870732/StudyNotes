public class HideTest{
    public static void main(String[] args) {
        Derived d = new Derived();
        //程序不可访问d的私有变量tag,所以下面的语句将引起编译错误
//      System.out.println(d.tag);
        System.out.println(((Parent)d).tag);
        //直接调用Parent的tag成员变量
    }
}
