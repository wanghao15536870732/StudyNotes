/*
习题 3. 8 对一个有序的单链表，删除所有值大于 x 而不大于 y 的结点
*/ 

#include "stdio.h"
#include "stdlib.h"

/**************************/
/*****链表表现头文件*******/
/**************************/
typedef int datatype;
typedef struct link_node{
	datatype info;
	struct link_node *next;
}node;

//建立一个空的单链表
node *init();
//输出单链表中各个节点的值
void display(node *head);
//在链表当中查找第i个节点的存放地址
//自定义输入数据函数 
node *my_scanf(node *head);
//单链表中删除一个值为x的结点
node *dele(node *head,datatype x);
//单链表中删除所有值大于x而不大于y的结点
node *dele_more(node *head,int x,int y);
node *find(node *head,int i);

int main()
{
	int x = 0,y =0;
	node *head,*p;
	head = init();
	head = my_scanf(head);
	printf("\n单链表各个结点的值为：\n");
	display(head);
	printf("输入想要删除的值的范围：\n");
	scanf("%d%d",&x,&y);
	head = dele_more(head,x,y);
	printf("删除之后的链表：\n");
	display(head);
	return 0;
}

//自定义输入数据函数 
node *my_scanf(node *head)
{
	node *p = NULL,*q = NULL;
	int n,a;
	printf("请输入数据的个数：\n");
	scanf("%d",&n);
	for(int a = 1;a <= n;a ++)
	{
		int data = 0; 
		scanf("%d",&data);
		p = (node *)malloc(sizeof(node));
		p->info = data;
		p->next = NULL;
		if(a == 1)
		{
			head = p;
			q = p;
		}
		else
		{
			q->next = p;
			q = p;
		}
	}
	return head;
}

/****************************/
/****建立一个空的单链表******/
/****************************/
node *init()
{
	return NULL;
}

/**********************************/
/****输出单链表中各个节点的值******/
/**********************************/
void display(node *head)
{
	node *p;
	p = head;
	if(!p)
		printf("\n链表是空的！");
	else
	{
		while(p)
		{
			printf("%5d",p->info);
			p = p->next;
		}
	}
	printf("\n");
}

node *find(node *head,int i)
{
	node *p = head;
	while(p && p->info != i)
		p = p->next;
	return p;
}

/************************************************/
/****单链表中删除所有值大于x而不大于y的结点******/
/************************************************/
node *dele_more(node *head,int x,int y)
{
	int i = 0;
	node *p1 = NULL,*p2 = NULL;
	p1 = find(head,x);
	p2 = find(head,y);
	p1->next = p2->next;
	return head;
}


