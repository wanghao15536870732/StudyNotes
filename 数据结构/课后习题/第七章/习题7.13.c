/*分别采用递归和非递归方式编写两个函数，求一棵给定二叉树中叶子结点的个数。
【答】：为方便测试二叉树相关程序，定义二叉树头文件bintree.h如下：*/

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

/*函数creat(根据扩充二叉树的前序序列(字符串a)建立二叉树t的存储结构*/
void creat(bintree *t)
{
    char ch = *a++;
    if (ch == ' ')
        *t = NULL;
    else
    {
        *t = (bintree)malloc(sizeof(binnode));
        (*t)->data = ch;
        creat(&(*t)->lchild);
        creat(&(*t)->rchild);
    }
}

void preorder(bintree t) /*前序递归遍历二叉树*/
{
    if (t)
    {
        printf("%c", t->data);
        preorder(t->lchild);
        preorder(t->rchild);
    }
}

/*顺序栈定义*/
typedef struct
{
    bintree data[N];
    int top;
} seqstack;

void init(seqstack *s) /*初始化空栈*/
{
    s->top = -1;
}
int empty(seqstack *s) /*判断栈是否为空*/
{
    if (s->top > -1)
        return 0;
    else
        return 1;
}
int full(seqstack *s) /*判断栈是否为满*/
{
    if (s->top == N - 1)
        return 1;
    else
        return 0;
}
void push(seqstack *s, bintree x) /*进栈*/
{
    if (!full(s))
        s->data[++s->top] = x;
}
bintree pop(seqstack *s) /*出栈*/
{
    if (!empty(s))
        return s->data[s->top--];
}

/*基于上述结构，递归方法与非递归方法求二叉树中叶子结点的个数的算法分别如leaf1() */

int leaf1(bintree t) /*递归方法求二叉树叶子结点的个数*/
{
    if (t == NULL)
        return 0;
    else if (!t->lchild && !t->rchild)
        return 1;
    else
        return leaf1(t->lchild) + leaf1(t->rchild);
}
int leaf2(bintree t) /*非递归方法求二叉树叶子结点的个数*/
{
    seqstack s;    /*顺序栈*/
    int count = 0; /*叶子结点计数变量*/
    init(&s);      /*初始化空栈*/
    while (t || !empty(&s))
    {
        if (t)
        {
            if (!t->lchild && !t->rchild)
                count++;
            push(&s, t);
            t = t->lchild;
        }
        else
        {
            t = pop(&s);
            t = t->rchild;
        }
    }
    return count;
}
int main()
{
    bintree t;
    creat(&t); /*建立二叉树t的存储结构*/
    printf("\n该二叉树一共有%d个叶子结点！\n", leaf1(t));
    printf("\n该二叉树一共有%d个叶子结点！\n", leaf2(t));
}