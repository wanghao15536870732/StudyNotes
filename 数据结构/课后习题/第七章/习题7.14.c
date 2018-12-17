/*试编写一个函数，返回一棵给定二叉树在中序遍历下的最后一个结点。 
【答】：*/

#include <stdio.h>
#include <stdlib.h>
#define N 100
extern char *a;     /*存放扩充二叉树的前序序列*/
typedef struct node /*二叉树结构定义*/
{
    char data;
    struct node *lchild, *rchild;
} binnode;
typedef binnode *bintree;

char *a = "ABC  D  EF G   "; /*扩充二叉树序树t的前序序列*/
bintree inlast(bintree t)
{
    bintree p = t;
    while (p && p->rchild)
        p = p->rchild;
    return p;
}
int main()
{
    bintree t;
    creat(&t); /*建立二叉树t的存储结构*/
    printf("二叉树中序遍历最后一个结点是%c\n", inlast(t)->data);
}