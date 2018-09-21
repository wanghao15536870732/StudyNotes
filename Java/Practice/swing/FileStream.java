package swing;

import java.io.*;

public class FileStream {
    public static void main(String[] args) throws IOException{
        File f = new File("D.txt");

        FileOutputStream fop = new FileOutputStream(f);

        OutputStreamWriter writer = new OutputStreamWriter(fop,"UTF-8");

        writer.append("王浩");

        writer.append("\r\n");

        writer.append("侯越");

        writer.append("\r\n");

        writer.append("杨雨润");

        writer.close();

        fop.close();

        FileInputStream fip = new FileInputStream(f);

        InputStreamReader reader = new InputStreamReader(fip,"UTF-8");

        StringBuffer b = new StringBuffer();

        while (reader.ready()){
            b.append((char)reader.read());
        }
        System.out.println(b.toString());

        reader.close();

        fip.close();

    }



}
