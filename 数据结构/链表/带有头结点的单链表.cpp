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

//建立一个空的带有头节点的单链表
node *init();
//输出带有头节点的单链表中各个节点的值
void display(node *head);
//在带有头节点的单链表当中查找第i个节点的存放地址
node *find(node *head,int i);
//带有头节点的单链表第i个结点后插入值为x的新结点
node *insert(node *head,datatype x,int i);
//带有头节点的单链表中删除一个值为x的结点
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
		p->next = NULL;
		if(a == 1)
		{
			head = p;
			q = p;
		}
		else
		{
			p->info = data;
			q->next = p;
			q = p;
		}
	}
	return head;
}

/**************************************/
/****建立一个空的带头节点的单链表******/
/*************************************/
node *init()
{
	node *head;
	head = (node *) malloc (sizeof(node));
	head->next = NULL;
	return head;
}

/**********************************************/
/****输出带有头节点的单链表中各个节点的值******/
/**********************************************/
void display(node *head)
{
	node *p;
	//从第一个实际的结点开始
	p = head->next;
	if(!p)
		printf("\n带头节点的单链表是空的！");
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

/*********************************************************/
/****在带有头结点的单链表当中查找第i个节点的存放地址******/
/*********************************************************/
node *find(node *head,int i)
{
	int j = 0;
	node *p = head;
	if(i < 0)
	{
		printf("\n带有头结点的单链表中不存在第%d个结点！",i);
		return NULL;
	}
	else if(i == 0)  /*此时p指向的是头结点*/
		return p;
	//没有查找完并且没有找到
	while(p && i != j)
	{
		p = p->next;
		j ++;
	}
	return p;
}



/**********************************************************/
/****在带有头节点的单链表第i个结点后插入值为x的新结点******/
/**********************************************************/
node *insert(node *head,datatype x,int i)
{
	node *p,*q;
	//查找带有头节点的单链表中的第i个结点
	q = find(head,i); /*如果i = 0，表示新结点插入在头节点之后*/
	//没有找到
	if(!q)
	{
		printf("\n带有头结点的单链表中不存在的第%d个结点！不能插入%d!",i,x);
		return head;
	}
	p = (node *)malloc(sizeof(node));
	p->info = x;
	p->next = q->next;
	//当 i = 0时，由于q指向的是头结点，本语句等价于head->next = p;
	q->next = p;
	return head;
}


/***************************************************/
/****在带有头结点的单链表中删除一个值为x的结点******/
/***************************************************/

node *dele(node *head,datatype x)
{
	//将pre指向头结点
	node *pre = head,*q;
	//q从带有头结点的第一个实际的结点开始找值为 x 的结点
	q = head->next; 
	while(q && q->info != x)
	{
		pre = q;
		q = q->next;
	}
	if(q)
	{
		//删除结点
		pre->next = q->next;
		free(q);//释放空间
	}
	return head;
}

