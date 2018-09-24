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

//建立一个空的循环单链表
node *init();
//输出循环单链表中各个节点的值
void display(node *head);
//在循环单链表当中查找第i个节点的存放地址
node *find(node *head,int i);
//带循环单链表第i个结点后插入值为x的新结点
node *insert(node *head,datatype x,int i);
//带循环单链表中删除一个值为x的结点
node *dele(node *head,datatype x);
//获得循环单链表的最后一个结点的储存地址
node *rear(node *head);
//自定义输入数据函数 
node *my_scanf(node *head);

int main()
{
	node *head;
	head = init();
	head = my_scanf(head); 
	display(head);
	head = dele(head,4);
	display(head);
	return 0;
}



/*******************************/
/****建立一个空的循环单链表*****/
/*******************************/
node *init()
{
	return NULL;
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


/***********************************************/
/****获得循环单链表的最后一个结点的储存地址******/
/***********************************************/
node *rear(node *head)
{
	node *p;
	//循环单链表为空
	if(!head)
		p = NULL;
	else
	{
		//从第一个结点开始
		p = head;
		//没有到达最后一个结点
		while(p->next != head)
			p = p->next; //继续向后
	}
	return p;
}

/*************************************/
/****输出循环单链表中各个节点的值******/
/*************************************/
void display(node *head)
{
	node *p;
	if(!head)
		printf("\n循环单链表是空的");
	else
	{
		printf("\n循环单链表各个结点的值分别为：\n");
		//输出链表的第一个数据
		printf("%5d",head->info);
		p = head->next;//指向下一个结点
		while(p != head) //没有回到第一个结点
		{
			printf("%5d",p->info);
			p = p->next;
		}
	}
}

/**********************************************/
/***在循环单链表当中查找值为x的节点的存放地址****/
/*********************************************/
node *find(node *head,int x)
{
	//查找一个值为x的结点
	node *q;
	//循环单链表是空的
	if(!head)
	{
		printf("\n循环单链表是空的！无法找到指定的结点！");
		return NULL;
	}
	q = head;
	//将q指向循环单链表的第一个结点，准备开始查询
	while(q->next != head && q->info != x)
		q = q->next;
	if(q->info == x)
		return q;
	else
		return NULL;
}



/**********************************************************/
/****在循环单链表第i个结点后插入值为x的新结点******/
/**********************************************************/
node *insert(node *head,datatype x,int i)
{
	//i = 0时，表示将值为x的系欸但插入到循环单链表的第一个结点
	node *p,*q,*myrear;
	int j;
	p = (node *)malloc(sizeof(node));
	//设置新结点的值
	p->info = x;
	if(i < 0)
	{
		printf("\n无法查找指定的插入位置！");
		free(p);
		return head;
	}
	//如果这个循环单链表是空的，则让它指向它自己
	if(i == 0 && !head)
	{
		p->next = p;
		head = p;
		return head;
	}
	//在循环单链表的第一个位置插入
	if(i == 0 && head)
	{
		//找到循环单链表的最后一个结点
		myrear = rear(head);
		p->next = head;
		myrear->next = p;
		return head;
	}
	if(i > 0 && !head)
	{
		printf("\n无法找到指定的插入位置！");
		free(p);
		return head;
	}
	//插入的位置不是第一个
	if(i > 0 && head)
	{
		//从循环单链表表头开始查找
		q = head;
		//计数开始
		j = 1;
		//没有找到对应的数据并且没有找到最后一个
		while(i != j && q->next != head)
		{
			q = q->next;
			j ++;
		}
		//找不到指定插入的位置
		if(i != j) 
		{
			printf("\n表中不存在第%d个结点，无法进行插入操作！\n");
			free(p);
			return head;
		}
		else
		{
			p->next = q->next;
			q->next = p;
			return head;
		}
	}
}


/***************************************************/
/****在循环单链表中删除一个值为x的结点******/
/***************************************************/

node *dele(node *head,datatype x)
{
	//q用于查找值为x的结点，pre指向 q 的前驱结点
	node *pre = NULL,*q;
	if(!head)
	{
		printf("\n循环单链表为空，无法进行删除操作！");
		return head;
	}
	//从第一个结点开始查找
	q = head;
	//没有找遍且没有找到
	while(q->next != head && q->info != x)
	{
		pre = q;
		q = q->next;
	}
	//遍历了整个没有找到
	if(q->info != x)
		printf("没有找到值为%d的结点！",x);
	else 
	{
		if(q != head)
		{
			pre->next = q->next;
			free(q);
		}
		else
		{
			if(head->next == head)
			{
				free(q);
				head = NULL;
			}
			else
			{
				pre = head->next;
				//查找 q 的前驱节点位置
				while(pre->next != q)
					pre = pre->next;
				head = head->next;
				pre->next = head;
				free(q);
			}
		}
	}
	return head;
}


