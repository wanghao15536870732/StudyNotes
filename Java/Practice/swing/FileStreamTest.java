package swing;

import java.io.*;
public class FileStreamTest {
    public static void main(String[] args) throws IOException{
        File f = new File("a.txt");
//       创建输出流
        FileOutputStream fop = new FileOutputStream(f);
        //构建FileOutputStream对象，文件不存在就自动新建，即创建写入流
        OutputStreamWriter writer = new OutputStreamWriter(fop,"UTF-8");
        //构建OutputStreamWriter对象,参数可以指定编码，默认为操作系统默认码,windows上是gbk
        writer.append("中文输入");
        //写入到缓存区
        writer.append("\r\n");
        //换行
        writer.append("English");
        //刷新缓存区，写入到文件。如果下面已经没有写入的内容了，直接cloe也会写入
        writer.close();
        //关闭写入流，同时会把缓冲区内容写入文件，所以上面的注释掉
        fop.close();
        //关闭输出流，释放系统资源
        FileInputStream fip = new FileInputStream(f);
        //构建FileInputStream对象
        InputStreamReader reader = new InputStreamReader(fip,"UTF-8");
        //构建InputStreamReader对象，编码与写入相同
        StringBuffer sb = new StringBuffer();
        while (reader.ready()){
            sb.append((char) reader.read());
            //转成char加入到StringBuffer对象当中
        }
        System.out.println(sb.toString());
        reader.close();
        //关闭读取流
        fip.close();
        //关闭输入流，释放系统资源
    }
}
