package Test;

public class Array {
    //泛型方法printArray
    public static <E> void printArray(E[] inputArray){
        for (E element : inputArray){
            System.out.printf("%s",element);
        }
        System.out.println();
    }

    public static void main(String[] args) {

        //创建不同类型的数组;Integer,Double和Character
        Integer[] intArray = {1,2,3,4,5};
        Double[] doubleArray = {1.1,2.2,3.3,4.4};
        Character[] charArray = {'H','E','L','L','O'};
        System.out.println("Array integerArray contains:");
        printArray(intArray);
        //传递一个整形数组
        System.out.println("\nArray doubleArray contains:");
        printArray(doubleArray);
        //传递一个双精度型数组
        System.out.println("\nArray characterArray contains:");
        printArray(charArray);
        //传递一个字符型数组
    }
}
