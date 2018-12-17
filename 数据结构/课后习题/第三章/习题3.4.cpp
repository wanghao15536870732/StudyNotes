/*
习题 3. 4 在一个单链表当中值为y的结点前面插入一个值为x的结点，
即使值为 x 的新结点成为值为 y 的结点的前驱结点
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
//在值为y的结点前插入一个值为x的结点
node *front_insert(node *head,int y,int x);
//在链表当中查找值为x的前驱结点
node *find(node *head,int x);
int main()
{
	int x = 0,y =0;
	node *head,*p;
	head = init();
	head = my_scanf(head);
	printf("\n单链表各个结点的值为：\n");
	display(head);
	printf("输入想要前插的结点跟数据：\n");
	scanf("%d%d",&y,&x);
	head = front_insert(head,y,x);
	printf("插入后的数据：\n");
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

/****************************************/
/****在链表当中查找值为x的前驱结点******/
/***************************************/
node *find(node *head,int x)
{
	node *p = head,*pre = head;
	while(p && p->info != x)
		p = p->next;
	//寻找q的前驱结点
	while(pre->next != p && p->info != x)
		pre = pre->next;
	return pre;
}

/********************************************/
/****在值为y的结点前插入一个值为x的结点******/
/********************************************/
node *front_insert(node *head,int y,int x)
{
	node *p = NULL,*q = NULL;
	q = find(head,y);
	if(!q)
		printf("\n找不到值为%d的结点，不能前插%d!",y,x);
	else
	{
		p = (node *)malloc(sizeof(node));
		p->info = x;
		//如果是第一个结点，插入到第一个结点前面
		if(head->info == y)
		{
			p->next = head;
			head = p;
		}
		else
		{
			p->next = q->next;
			q->next = p;
		}
	}
	return head;
}


