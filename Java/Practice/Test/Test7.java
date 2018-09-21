package Test;

import java.util.ArrayList;
import java.util.Stack;
/*
栈的使用
 */
public class Test7 {
    public static class ListNode{
        int val;
        ListNode next = null;
        ListNode(int val){
            this.val = val;
        }
    }

    public static ArrayList<Integer> printListFromTailToHead(ListNode listNode){
        Stack<Integer> stack = new Stack<>();
        while (listNode != null){
            //像里面压栈
            stack.push(listNode.val);
            listNode = listNode.next;
        }

        ArrayList<Integer> list = new ArrayList<>();
        while (!stack.empty()){
            //pop方法返回栈顶的值，会把栈顶的值删除
            // 而peek()方法不改变栈的值，查看栈顶的对象而不移除它
            list.add(stack.pop());
        }
        return list;
    }

    public static void main(String[] args) {
        ListNode listNode_1 = new ListNode(1);
        System.out.println(printListFromTailToHead(listNode_1));
    }
}
