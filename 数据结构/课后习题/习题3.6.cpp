/*
习题 3. 6 利用单链表原来的结点空间逆转一个单链表
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
//利用单链表原来的节点空间空间逆转一个单链表
node *reverse(node *head);
int main()
{
	node *head,*p;
	head = init();
	head = my_scanf(head);
	printf("\n单链表各个节点的值为：\n");
	display(head);
	printf("\n数值逆转后的单链表：\n");
	head = reverse(head);
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

/****************************************************/
/****利用单链表原来的节点空间空间逆转一个单链表******/
/****************************************************/
node *reverse(node *head)
{
	node *p = head,*q;
	head = NULL;
	while(p)
	{
		q = p;
		p = p->next;
		q->next = head;
		head = q;
	}
	return head;
}

