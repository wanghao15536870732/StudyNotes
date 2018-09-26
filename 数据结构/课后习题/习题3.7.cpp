/*
习题 3. 7 将一个结点值为自然数得单链表拆分为两个单链表，
原表当中保留值为偶数的结点，而值为奇数的结点按他们在元表中的
相对次序组成一个新的链表
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
//提取奇数
node *separate(node *head1,node *head2);
//剩余偶数的旧连表
node *surplus(node *head,node *head2);

int main()
{
	int x = 0,y =0;
	node *head,*p;
	node *head1;
	head = init();
	head1 = init();
	head = my_scanf(head);
	printf("\n单链表各个结点的值为：\n");
	display(head);
	head1 = separate(head,head1);
	printf("\n提取奇数节点的新链表：\n");
	display(head1);
	head1 = surplus(head,head1);
	printf("\n剩余偶结点的旧链表：\n");
	display(head1);
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

/*******************/
/****提取奇数******/
/******************/
node *separate(node *head1,node *head2)
{
	node *p = head1,*q = NULL,*m = NULL;
	if(p->next == NULL)
		printf("链表是空的!\n");
	int a = 0;
	while(p)
	{
		if(p->info % 2 != 0)
		{
			q = (node *)malloc(sizeof(node));
			q->info = p->info;
			q->next = NULL;
			if(a == 0)
			{
				head2 = q;
				m = q;
				a = 1;
			}
			else
			{
				m->next = q;
				m = q;
			}
		}
		p = p->next;
	}
	return head2;
}

/**************************/
/****剩余偶数的旧连表******/
/**************************/
node *surplus(node *head,node *head2)
{
	node *p = head,*q = NULL,*m = NULL;
	if(p->next == NULL)
		printf("链表是空的!\n");
	int a = 0;
	while(p)
	{
		if(p->info % 2 == 0)
		{
			q = (node *)malloc(sizeof(node));
			q->info = p->info;
			q->next = NULL;
			if(a == 0)
			{
				head2 = q;
				m = q;
				a = 1;
			}
			else
			{
				m->next = q;
				m = q;
			}
		}
		p = p->next;
	}
	return head2;
}
