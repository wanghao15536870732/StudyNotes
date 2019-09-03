public class Wolf extends Animal{
    public Wolf(){
        super("莉莉安",18);
        System.out.println("WOlf的无参函数构造器");
    }

    public static void main(String[] args) {
        new Wolf();
    }
}