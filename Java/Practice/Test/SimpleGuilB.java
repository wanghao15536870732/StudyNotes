package Test;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleGuilB implements ActionListener {
    JButton button;

    public static void main(String[] args) {

        SimpleGuilB gui = new SimpleGuilB();
        gui.go();
    }

    public void go(){
        JFrame frame = new JFrame();
        button = new JButton("click me");


        //向按钮注册
        button.addActionListener(this);

        frame.getContentPane().add(button);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300,300);
        frame.setVisible(true);
    }

    //实现interface 上的方法
    //这是真正处理事件的方法
    @Override
    public void actionPerformed(ActionEvent e) {

        //按钮会一ActionEvent对象作为参数来调用此方法
        button.setText("T've been clicked!");
    }
}