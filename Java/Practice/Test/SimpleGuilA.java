package Test;

//首先导入swing的这个包
import javax.swing.*;

//import进ActionListener和ActionEvent所在的包
import java.awt.event.*;
/*
java窗口 swing 的使用
 */
public class SimpleGuilA {
    public static void main(String[] args) {
        //创建frame和button
        JFrame frame = new JFrame();
        JButton button = new JButton("click me");

        //在windows关闭程序
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //将button加到frame的pane上
        frame.getContentPane().add(button);

        //设定frame的大小
        frame.setSize(300,300);

        //让fame显示出来
        frame.setVisible(true);


    }
}
