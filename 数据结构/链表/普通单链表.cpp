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
node *find(node *head,int i);
//在链表当中查找值为i的节点的存放地址
node *findi(node *head,int i);
//链表第i个结点后插入值为x的新结点
node *insert(node *head,datatype x,int i);
//单链表中删除一个值为x的结点
node *dele(node *head,datatype x);
//自定义输入数据函数 
node *my_scanf(node *head);

int main()
{
	int i = 0,j = 0;
	node *head,*p;
	head = init();
	head = my_scanf(head);
	printf("\n单链表各个节点的值为：\n");
	display(head);
	printf("\n输入想要删除的节点数值:\n");
	scanf("%d",&i);
	head = dele(head,i);
	printf("\n删除结点数值为%d的结点后的链表：\n",i); 
	display(head);
	printf("\n输入想要插入的结点位置以及数值：\n");
	scanf("%d%d",&i,&j);
	insert(head,j,i); 
	printf("\n将数值%d插入到链表第%d位后的链表：\n",j,i);
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

/*********************************************/
/****在链表当中查找第i个节点的存放地址******/
/*********************************************/
node *find(node *head,int i)
{
	int j = 1;
	node *p = head;
	if(i < 1)
		return NULL;
	while(p && i != j)
	{
		p = p->next;
		j ++;
	}
	return p;
}


/*********************************************/
/****在链表当中查找值为i的节点的存放地址******/
/*********************************************/
node *findi(node *head,int i)
{
	node *p = head;
	while(p && p->info != i)
		p = p->next;
	return p;
}

/********************************************/
/****单链表第i个结点后插入值为x的新结点******/
/********************************************/
node *insert(node *head,datatype x,int i)
{
	node *p,*q;
	//查找第i个结点
	q = find(head,i);
	if(!q && i != 0)
		printf("\n找不到第%d个结点，不能插入%d!",i,x);
	else
	{
		//为p开辟一个空间
		p = (node *)malloc(sizeof(node));
		//设置新节点的数据
		p->info = x;
		//如果插入的结点是单链表的第一个结点
		if(i == 0)
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


/**************************************/
/****单链表中删除一个值为x的结点******/
/*************************************/

node *dele(node *head,datatype x)
{
	node *pre = NULL,*p;
	if(!head)
	{
		printf("单链表是空的！");
		return head;
	}
	p = head;
	//指针指向数据存在并且没有找到符合的数据
	while(p && p->info != x)
	{
		pre = p;
		p = p->next;
	}
	if(p)
	{
		//前驱结点不存在，即想要删除第一个数据
		if(!pre)
			head = head->next;
		else
			pre->next = p->next;
		free(p);
	}
	return head;
}
