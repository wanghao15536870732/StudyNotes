# Java IO编程

+ [`文件操作类 File`](#文件操作类：File)
  + [`文件基本操作`](#文件基本操作)
  + [`创建带路径的文件`](#创建带路径的文件)
  + [`取得文件或目录的信息`](#取得文件或目录的信息)
  + [`列出文件目录信息`](#列出目录信息)
+ [`字节流与字符流`](#字节流与字符流)
  + [`自动执行 close() 操作`](#自动执行close()操作)
  + [`文件内容的输出`](#文件内容的输出)
  + [`采用单个字节的方式输出`](#采用单个字节的方式输出)
  + [`输出部分字节数组内容`](#输出部分字节数组内容)
  + [`数据读取操作`](#数据读取操作)
  + [`使用 Writer 类实现内容输出`](#使用Writer类实现内容输出)
  + [`强制清空字符流缓冲区`](#强制清空字符流缓冲区)
+ [`转换流`](#转换流)
  + [`实现输出流转换`](#实现输出流转换)
+ [`System 类对 IO 的支持`](#System类对IO的支持)
  + [`错误输出`](#错误输出)
  + [`利用 OutputStream 实现屏幕输出`](#利用OutputStream实现屏幕输出)
  + [`实现键盘的数据输入`](#实现键盘的数据输入)
+ [`字符缓冲流 BufferedReader`](#字符缓冲流：BufferedReader)
  + [`键盘数据输入的标准格式`](#键盘数据输入的标准格式)
  + [`读取文件`](#读取文件)
+ [`扫描流：Scanner`](#扫描流：Scanner)
  + [`利用 Scanner 实现键盘数据输入`](#利用Scanner实现键盘数据输入)
+ [`对象序列化`](#对象序列化)
  + [`定义一个可以被序列化对象的类`](#定义一个可以被序列化对象的类)
  + [`实现序列化对象操作 —— ObjectOutputStream`](#实现序列化对象操作——ObjectOutputStream)
  + [`实现反序列化操作 —— ObjectInputStream`](#实现反序列化操作——ObjectInputStream)

## 文件操作类：File

### 文件基本操作

+ 任意给定一个文件路径，如果文件不存在则创建一个新的文件，如果文件存在则将文件删除

```java
import java.io.File;
public class TestDemo {
    public static void main(String[] args) throws Exception { 	// 此处直接抛出
        File file = new File("d:\\test.txt"); // 设置文件的路径
        if (file.exists()) { // 判断文件是否存在
           file.delete(); // 删除文件
        } else { // 文件不存在
           System.out.println(file.createNewFile()); // 创建新文件
        }
    }
}
```

### 创建带路径的文件

+ 如果给定的路径为根路径，则文件可以直接利用createNewFile()方法进行创建；
+ 如果要创建的文件存在目录，那么将无法进行创建。所以合理的做法应该是在创建文件前判断父路径（getParent()取得父路径）是否存在
+ 如果不存在则应该先创建目录（mkdirs()创建多级目录），再创建文件

```java
import java.io.File;
public class TestDemo {
    public static void main(String[] args) throws Exception { 	// 此处直接抛出
        File file = new File("d:" + File.separator + "demo" + File.separator
              + "hello" + File.separator + "yootk" + File.separator
              + "test.txt"); // 设置文件的路径
        if (!file.getParentFile().exists()) { // 现在父路径不存在
           file.getParentFile().mkdirs(); // 创建父路径
        }
        System.out.println(file.createNewFile()); // 创建新文件
    }
}
```

### 取得文件或目录的信息

```java
mport java.io.File;
import java.math.BigDecimal;
import java.text.SimpleDateFormat;
import java.util.Date;
public class TestDemo {
    public static void main(String[] args) throws Exception {  // 此处直接抛出
        File file = new File("d:" + File.separator + "my.jpg"); // 设置文件的路径
        if (file.exists()) {
           System.out.println("是否是文件：" + (file.isFile()));
           System.out.println("是否是目录：" + (file.isDirectory()));
           // 文件大小是按照字节单位返回的数字，所以需要将字节单元转换为兆（M）的单元
           // 但是考虑到小数点问题，所以使用BigDecimal处理
           System.out.println("文件大小："
                    + (new BigDecimal((double) file.length() / 1024 / 1024)
                            .divide(new BigDecimal(1), 2,
                                   BigDecimal.ROUND_HALF_UP)) + "M");
           // 返回的日期是以long的形式返回，可以利用SimpleDateFormat进行格式化操作
           System.out.println("上次修改时间："
                    + new SimpleDateFormat("yyyy-MM-dd HH:mm:ss")
                             .format(new Date(file.lastModified())));
        }
    }
}
```

### 列出目录信息

```java
mport java.io.File;
public class TestDemo {
    public static void main(String[] args) throws Exception { // 此处直接抛出
        File file = new File("c:" + File.separator);
        if (file.isDirectory()) { // 判断当前路径是否为目录
           File result [] = file.listFiles() ;
           for (int x = 0; x < result.length; x++) {
               System.out.println(result[x]); // 调用toString()
           }
        }
    }
}
```

## 字节流与字符流

### 自动执行close()操作

```java
class Net implements AutoCloseable {
    @Override
    public void close() throws Exception {
        System.out.println("*** 网络资源自动关闭，释放资源。");
    }
    public void info() throws Exception { // 假设有异常抛出
        System.out.println("*** 欢迎访问：www.baidu.com");
    }
}
public class TestDemo {
    public static void main(String[] args) {
        try (Net n = new Net()){
            n.info();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### 文件内容的输出

```java
import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;
public class TestDemo {
    public static void main(String[] args) throws Exception { 	// 直接抛出
        // 1．定义要输出文件的路径
        File file = new File("d:" + File.separator + "demo" + File.separator
              + "mldn.txt");
        // 此时由于目录不存在，所以文件不能输出，应该首先创建目录
        if (!file.getParentFile().exists()) { // 文件目录不存在
           file.getParentFile().mkdirs(); // 创建目录
        }
        // 2．应该使用OutputStream和其子类进行对象的实例化，此时目录存在，文件还不存在
        OutputStream output = new FileOutputStream(file);
        // 字节输出流需要使用byte类型，需要将String类对象变为字节数组
        String str = "wanghao15536870732";
        byte data[] = str.getBytes(); // 将字符串变为字节数组
        output.write(data); // 3．输出内容
        output.close(); // 4．资源操作的最后一定要进行关闭
    }
}
```

### 采用单个字节的方式输出

+ 此处可以利用循环操作输出全部字节数组中的数据

```java
  for (int x= 0 ; x < data.length ; x ++) {
        output.write(data[x]); // 内容输出
    }
```

### 输出部分字节数组内容

```java
 output.write(data, 6, 6); // 内容输出
```

### 数据读取操作

```java
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
public class TestDemo {
    public static void main(String[] args) throws Exception { // 直接抛出
        File file = new File("d:" + File.separator + "demo" + File.separator
              + "mldn.txt"); // 1．定义要输出文件的路径
        if (file.exists()) { // 需要判断文件是否存在后才可以进行读取
           // 2．使用InputStream进行读取
           InputStream input = new FileInputStream(file) ;
           byte data [] = new byte [1024] ; // 准备出一个1024的数组
           int len = input.read(data) ; // 3．进行数据读取，将内容保存到字节数组中
           input.close(); // 4．关闭输入流
           // 将读取出来的字节数组数据变为字符串进行输出
           System.out.println("【" + new String(data,0,len) + "】");
        }
    }
}
```

### 使用Writer类实现内容输出

```java
import java.io.File;
import java.io.FileWriter;
import java.io.Writer;
public class TestDemo {
    public static void main(String[] args) throws Exception { // 此处直接抛出
        File file = new File("d:" + File.separator + "demo" + File.separator
              + "mldn.txt"); // 1．定义要输出文件的路径
        if (!file.getParentFile().exists()) { // 判断目录是否存在
           file.getParentFile().mkdirs(); // 创建文件目录
        }
        Writer out = new FileWriter(file); // 2．实例化了Writer类的对象
        String str = "I like you";	// 定义输出内容
        out.write(str); // 3．输出字符串数据
        out.close(); // 4．关闭输出流
    }
}
```

### 强制清空字符流缓冲区

```java
import java.io.File;
import java.io.FileWriter;
import java.io.Writer;
public class TestDemo {
    public static void main(String[] args) throws Exception { // 此处直接抛出
        File file = new File("d:" + File.separator + "demo" + File.separator
              + "mldn.txt"); // 1．定义要输出文件的路径
        if (!file.getParentFile().exists()) { // 判断目录是否存在
           file.getParentFile().mkdirs(); // 创建文件目录
        }
        Writer out = new FileWriter(file); // 2．实例化了Writer类的对象
        String str = "I like you"; // 定义输出内容
        out.write(str); // 3．输出字符串数据
        out.flush(); // 强制刷新缓冲区
    }
}
```

## 转换流

### 实现输出流转换

```java
import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.Writer;
public class TestDemo {
    public static void main(String[] args) throws Exception { // 此处直接抛出
        File file = new File("d:" + File.separator + "demo" + File.separator
              + "mldn.txt"); // 1．定义要输出文件的路径
        if (!file.getParentFile().exists()) { // 判断父路径是否存在
           file.getParentFile().mkdirs() ; // 创建父路径
        }
        OutputStream output = new FileOutputStream(file) ;// 字节流
        // 将OutputStream类对象传递给OutputStreamWriter类的构造方法，而后向上转型为Writer
        Writer out = new OutputStreamWriter(output) ;
        out.write("Hello World!"); // Writer类的方法
        out.flush();
        out.close();
    }
}
```

## System类对IO的支持

### 错误输出

```java
public class TestDemo {
    public static void main(String[] args) throws Exception {
        try {
            Integer.parseInt("abc"); // 此处一定会发生异常
        } catch (Exception e) {
            System.err.println(e); // 错误输出
        }
    }
}
```

### 利用OutputStream实现屏幕输出

```java
public class TestDemo {
    public static void main(String[] args) throws Exception { // 此处直接抛出异常
        OutputStream out = System.out; // OutputStream就为屏幕输出
        out.write("Hello World!".getBytes()); // 屏幕输出
    }
}
```

### 实现键盘的数据输入

```java
import java.io.InputStream;
public class TestDemo {
    public static void main(String[] args) throws Exception { 	// 此处直接抛出
        // 为了方便读者理解，本处将System.in使用InputStream接收，但实际上不需要此操作
        InputStream input = System.in; // System.in为InputStream类实例
        byte data[] = new byte[1024]; // 开辟空间接收数据
        System.out.print("请输入数据："); // 信息提示，此处没有换行
        int len = input.read(data); // 读取数据并返回长度
        System.out.println("输入数据为：" + new String(data, 0, len));
    }
}
```

## 字符缓冲流：BufferedReader

### 键盘数据输入的标准格式

```java
import java.io.BufferedReader;
import java.io.InputStreamReader;
public class TestDemo {
    public static void main(String[] args) throws Exception { // 此处直接抛出
        // System.in是InputStream类对象，BufferedReader的构造方法里面需要接收Reader类对象
        // 利用InputStreamReader将字节流对象变为字符流对象
        BufferedReader buf = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("请输入数据：");
        String str = buf.readLine(); // 以回车作为换行
        System.out.println("输入的内容：" + str);
    }
}
```

### 读取文件

```java
mport java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
public class TestDemo {
    public static void main(String[] args) throws Exception { // 此处直接抛出
        File file = new File("D:" + File.separator + "hello.txt");
        // 使用文件输入流实例化BufferedReader类对象
        BufferedReader buf = new BufferedReader(new FileReader(file));
        String str = null; // 接收输入数据
        while ((str = buf.readLine()) != null) { // 读取数据并判断是否存在
            System.out.println(str); // 输出读取内容
        }
        buf.close();
    }
}
```

## 扫描流：Scanner

### 利用Scanner实现键盘数据输入

```java
import java.util.Scanner;
public class TestDemo {
    public static void main(String[] args) throws Exception { 	// 此处直接抛出
        Scanner scan = new Scanner(System.in); // 准备接收键盘输入数据
        System.out.print("请输入内容："); // 提示信息
        if (scan.hasNext()) { // 是否有输入数据
           System.out.println("输入内容：" + scan.next()); // 存在内容则输出
        }
        scan.close();
    }
}
```

## 对象序列化

### 定义一个可以被序列化对象的类

```java
import java.io.Serializable;
@SuppressWarnings("serial") // 压制序列化版本号警告信息
class Book implements Serializable { // 此类对象可以被序列化
    private String title;
    private double price;
    public Book(String title, double price) {
        this.title = title;
        this.price = price;
    }
    @Override
    public String toString() {
        return "书名：" + this.title + "，价格：" + this.price;
    }
}

```

### 实现序列化对象操作——ObjectOutputStream

```java
import java.io.File;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
public class TestDemo {
    public static void main(String[] args) throws Exception {
        ser();
    }
    public static void ser() throws Exception {
        ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(
                new File("D:" + File.separator + "book.ser")));
        oos.writeObject(new Book("Java开发实战经典", 79.8)); // 序列化对象
        oos.close();
    }
}
```

### 实现反序列化操作——ObjectInputStream

```java
import java.io.File;
import java.io.FileInputStream;
import java.io.ObjectInputStream;
public class TestDemo {
    public static void main(String[] args) throws Exception {
        dser();
    }
    public static void dser() throws Exception {
        ObjectInputStream ois = new ObjectInputStream(
                new FileInputStream(new File("D:" + File.separator + "book.ser")));
        Object obj = ois.readObject() ; // 反序列化对象
        Book book = (Book) obj ; // 转型
        System.out.println(book);
        ois.close();
    }
}
```