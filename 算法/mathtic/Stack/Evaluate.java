package Stack;

import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

import java.awt.geom.Arc2D;
import java.util.Stack;

public class Evaluate {
    public static void main(String[] args) {
        Stack<String> ops = new Stack<String>();
        Stack<Double> vals = new Stack<>();
        while (!StdIn.isEmpty()){
            //读取字符，如果是运算符，则压入栈
            String s = StdIn.readString();
            if (s.equals("("));
            else if (s.equals("+"))
                ops.push(s);
            else if (s.equals("-"))
                ops.push(s);
            else if (s.equals("*"))
                ops.push(s);
            else if (s.equals("/"))
                ops.push(s);
            else if (s.equals("sqrt"))
                ops.push(s);
            else if (s.equals(")")) {
                //如果字符串为")",弹出运算符跟操作符，计算结果并压入栈内
                String op = ops.pop();
                double v = vals.pop();
                if(op.equals("+"))
                    v = vals.pop() + v;
                else if (op.equals("-"))
                    v = vals.pop() - v;
                else if (op.equals("*"))
                    v = vals.pop() * v;
                else if (op.equals("/"))
                    v = vals.pop() / v;
                else if (op.equals("sqrt"))
                    v = Math.sqrt(v);
                vals.push(v);
            }  //如果字符串既不是运算符又不是括号，将它作为double值压入栈
            else{
                vals.push(Double.parseDouble(s));
            }
        }
        StdOut.println(vals.pop());
    }
}
