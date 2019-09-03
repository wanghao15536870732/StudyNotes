/*
习题 3. 5 判断单链表是否有序
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
int order_down(node *head);
int order_up(node *head);

int main()
{
	int x = 0,y =0;
	node *head,*p;
	head = init();
	head = my_scanf(head);
	printf("\n单链表各个结点的值为：\n");
	display(head);
	if(order_down(head) || order_up(head))
		printf("该单链表是有序的!\n");
	else
		printf("该单链表是无序的!\n");
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

/***************************/
/****判断链表是否有序******/
/**************************/
int order_up(node *head)
{
	node *pre = head,*p = head ->next;
	if(p == NULL) 
		return 1; //空表是有序的
	while(p != NULL)
	{
		if(p->info > pre->info)
			break;
		pre = p;
		p = p->next;
	}
	return (p == NULL);
}
int order_down(node *head)
{
	node *pre = head,*p = head ->next;
	if(p == NULL) 
		return 1; //空表是有序的
	while(p != NULL)
	{
		if(p->info < pre->info)
			break;
		pre = p;
		p = p->next;
	}
	return (p == NULL);
}
