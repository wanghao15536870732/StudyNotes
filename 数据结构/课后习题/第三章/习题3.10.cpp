#include <stdlib.h>
#include <stdio.h>
    typedef struct node
{
    int data;
    struct node *next;
} linknode;
typedef linknode *linklist;
/*尾插法创建带头结点的单链表*/
linklist creatlinklist()
{
    linklist head, r, s;
    int x;
    head = r = (linklist)malloc(sizeof(linknode));
    printf("\n请输入一组以0结束的整数序列：\n");
    scanf("%d", &x);
    while (x)
    {
        s = (linklist)malloc(sizeof(linknode));
        s->data = x;
        r->next = s;
        r = s;
        scanf("%d", &x);
    }
    r->next = NULL;
    return head;
}
/*输出带头结点的单链表*/
void print(linklist head)
{
    linklist p;
    p = head->next;
    printf("List is:\n");
    while (p)
    {
        printf("%5d", p->data);
        p = p->next;
    }
    printf("\n");
}


int count(linklist head)
{
    int c = 0;
    linklist p = head;
    while (p)

        15
        {
            c++;
            p = p->next;
        }
    return c;
}
//3.3设计一个算法，求一个带头结点单链表中的结点个数。 
//【答】：带头结点的单链表的存储结构定义同题3 .2，实现本题功能的算法程序如下（3_3.c）
int count(linklist head)
{
    int c = 0;
    linklist p = head->next;
    while (p)
    {
        c++;
        p = p->next;
    }
    return c;
}

int main() /*测试函数*/
{
    linklist head;
    head = creatlinklist();
    print(head);
    printf("\nLength of head is:%d", count(head));
    getch();
}

//当输入5个数据时，产生的输出结果如下图所示：

//3.4设计一个算法，在一个单链表中值为y的结点前面插入一个值为x的结点。即使值为x的新结点成为值为y的结点的前驱结点。 
//【答】：
void insert(linklist head, int y, int x)
{ /*在值为y的结点前插入一个值为x的结点*/
    linklist pre, p, s;
    pre = head;

    16 p = head->next;
    while (p && p->data != y)
    {
        pre = p;
        p = p->next;
    }
    if (p) /*找到了值为y的结点*/
    {
        s = (linklist)malloc(sizeof(linknode));
        s->data = x;
        s->next = p;
        pre->next = s;
    }
}

int main() /*测试程序*/
{
    linklist head;
    int y, x;
    head = creatlinklist(); /*创建单链表*/
    print(head);            /*输出单链表*/
    printf("\n请输入y与x的值:\n");
    scanf("%d %d", &y, &x);
    insert(head, y, x);
    print(head);
}


//3.5设计一个算法，判断一个单链表中各个结点值是否有序。

int issorted(linklist head, char c)
/*当参数c=’a’时判断链表是否为升序，当参数c=’d’是判断链表是否为降序*/
{
    int flag = 1;
    linklist p = head->next;
    switch (c)

        17
        {
        case 'a': /*判断带头结点的单链表head是否为升序*/
            while (p && p->next && flag)
            {
                if (p->data <= p->next->data)
                    p = p->next;
                else
                    flag = 0;
            }
            break;
        case 'd': /*判断带头结点的单链表head是否为降序*/
            while (p && p->next && flag)
            {
                if (p->data >= p->next->data)
                    p = p->next;
                else
                    flag = 0;
            }
            break;
        }
    return flag;
}
int main() /*测试程序*/
{
    linklist head;
    head = creatlinklist();
    print(head);
    if (issorted(head, 'a'))
        printf("单链表head是升序排列的！\n");
    else if (issorted(head, 'd'))
        printf("单链表head是降序排列的！\n");
    else
        printf("单链表head是无序的！\n");
}


//3.6设计一个算法，利用单链表原来的结点空间将一个单链表就地转置。

void verge(linklist head)
{ /*本函数的功能是就地倒置带头结点的单链表*/
    linklist p, q;
    p = head->next;
    head->next = NULL;
    while (p) /*每次从原表取一个结点插入到新表的最前面*/
    {
        q = p;
        p = p->next;
        q->next = head->next;
        head->next = q;
    }
}
int main() /*测试函数*/
{
    linklist head;
    head = creatlinklist(); /*创建单链表*/
    print(head);            /*输出原单链表*/
    verge(head);            /*就地倒置单链表*/
    print(head);            /*输出倒置后的单链表*/
}

//3.7设计一个算法，将一个结点值自然数的单链表拆分为两个单链表，原表中保留值为偶数的 结点，而值为奇数的结点按它们在原表中的相对次序组成一个新的单链表。 

linklist sprit(linklist head)
{ /*将带头结点的单链表head中的奇数值结点删除生成新的单链表并返回*/
    linklist L, pre, p, r;
    L = r = (linklist)malloc(sizeof(linknode));
    r->next = NULL;
    pre = head;
    p = head->next;
    while (p)
    {
        if (p->data % 2 == 1) /*删除奇数值结点*/
        {
            pre->next = p->next;
            r->next = p;
            r = p;
            p = pre->next;
        }
        else /*保留偶数值结点*/
        {
            pre = p;
            p = p->next;

            19
        }
    }
    r->next = NULL; /*置链表结束标记*/
    return L;
}
int main() /*测试函数*/
{
    linklist head, L;
    head = creatlinklist(); /*创建单链表*/
    print(head);            /*输出原单链表*/
    L = sprit(head);        /*分裂单链表head*/
    printf("\n原单链表为:\n");
    print(head); /*输出倒置后的单链表*/
    printf("\n分裂所得奇数单链表为:\n");
    print(L);
}