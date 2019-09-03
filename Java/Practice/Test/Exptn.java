package Test;
import com.sun.xml.internal.ws.policy.privateutil.PolicyUtils;

import java.io.*;


public class Exptn {
    public static void main(String[] args) throws IOException{
//        char c;
//        //使用System.in创建BufferedReader
//        Buffered br = new Buffered(new InputStreamReader(System.in));
//        System.out.println("Enter characters.'q'to quit.");
//        //读取字符
//        do{
//            c = (char) br.read();
//            System.out.println(c);
//        }while (c != 'q');
//
//        /**
//         * 输人1234abcq
//         * 输出 1
//                2
//                3
//                4
//                 a
//                 b
//                 c
//                 q
//         */
//
//        //使用System.in创建BufferReader
//        Buffered brr = new Buffered(new InputStreamReader(System.in));
//        String str;
//        System.out.println("Enter lines of text.");
//        System.out.println("Enter 'end' to quit.");
//        do{
//            str = brr.readLine();
//            System.out.println(str);
//        }while (!str.equals("end"));
//
//        /**
//         * 输入：This is line one
//         * 输出：this is line one
//         * 输入：this is line two
//         * 输出：this is line two
//         * 输入：end
//         * 输出：end
//         */
        try{
            byte bWrite [] = {11,12,12,12,121};
            OutputStream os = new FileOutputStream("Exptn.txt");
            for (int i = 0; i < bWrite.length; i++) {
                os.write(bWrite[i]);//writes the bytes
            }
            os.close();
            InputStream is = new FileInputStream("Exptn.txt");
            int size = is.available();
            for (int i = 0; i < size; i++) {
                System.out.println((char)is.read() + "、");
            }
            is.close();
        }catch (IOException e){
            System.out.println("IOException");
        }
    }
}
