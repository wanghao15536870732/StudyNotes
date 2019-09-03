#include <stdio.h>
#include <stdlib.h>
typedef char datatype;
typedef struct node /*二叉树结点定义*/
{
    datatype data;
    struct node *lchild, *rchild;
} bintnode;
typedef bintnode *bintree;

typedef struct stack //顺序栈结构定义
{
    bintree data[100];
    int tag[100];
    int top;
} seqstack;
void creat(bintree *t); //创建二叉树结构函数声明

/*函数SeekAncestor的功能是返回二叉树t中结点x与结点y的最近公共祖先结点*/
void SeekAncestor(bintree t, datatype x, datatype y, bintree *antor)
{
    seqstack s;
    bintree data[100] = {0};
    int i = 0, j;
    s.top = -1;
    while (t || s.top > -1)
    {
        while (t)
        {
            s.data[++s.top] = t;
            s.tag[s.top] = 0;
            t = t->lchild;
        }
        while (s.top > -1 && s.tag[s.top])
        {
            t = s.data[s.top];
            if (t->data == x)
                while (i <= s.top) //记录x结点的所有祖先结点
                {
                    data[i] = s.data[i];
                    i++;
                }
            else if (t->data == y)
            {
                while (s.top > -1)
                {
                    j = i - 1;
                    while (j >= 0 && t != data[j]) //查找y与x的最近公共祖先结点
                        j--;
                    if (j >= 0)
                    {
                        *antor = data[j]; //返回公共祖先结点地址
                        return;
                    }
                    t = s.data[--s.top];
                }
            }
            --s.top;
        }
        if (s.top > -1)
        {
            t = s.data[s.top];
            s.tag[s.top] = 1;
            t = t->rchild;
        }
        else
            t = NULL;
    }
}
/*函数creat(根据扩充二叉树的前序序列建立二叉树t的存储结构*/
void creat(bintree *t)
{
    char ch;
    scanf("%c", &ch);
    if (ch == '#')
        *t = NULL;
    else
    {
        *t = (bintnode *)malloc(sizeof(bintnode));
        (*t)->data = ch;
        creat(&(*t)->lchild);
        creat(&(*t)->rchild);
    }
}
int main()
{
    bintree root, p = NULL;
    datatype x = 'B', y = 'C';
    printf("请输入扩充二叉树的前序序列：\n");
    creat(&root);
    printf("请输入树中的两个结点值：\n");
    printf("请输入第一个节点：\n");
    getchar();
    scanf("%c", &x);
    printf("请输入第二个节点：\n");
    getchar();
    scanf("%c",&y);
    printf("%c %c\n", x,y);
    SeekAncestor(root, x, y, &p);
    if (p)
        printf("%c和%c的最近公共祖先是：%c\n", x, y, p->data);
}