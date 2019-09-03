/*
链式栈
*/
#include "stdio.h"
#include "stdlib.h"

/*
链式栈的头文件，与单链表类似
*/
typedef int datatype;
typedef struct link_node{
	datatype info;
	struct link_node *next;
}node;



/********************/
/*建立一个空的链式栈*/
/********************/
node *init()
{
	return NULL;
}

/********************/
/*判断链式栈是否为空*/
/********************/
int empty(node *top)
{
	return (top ? 0 : 1);
}

/************************/
/*读取链式栈的栈顶结点值*/
/************************/
datatype read(node *top)
{
	if(! top)
	{
		printf("\n链式栈是空的！");
		exit(1);
	}
	return (top->info);
}

/**************************/
/*输出链式栈中各个节点的值*/
/**************************/
void display(node *top)
{
	node *p = top;
	printf("\n");
	if(!p)
		printf("链式栈是空的！");
	while(p)
	{
		printf("%3d-->",p->info);
		p = p->next;
	}
	printf("\n");
}

/*************************/
/*向链式栈插入值为x的结点*/
/*************************/
node *push(node *top,datatype x)
{
	node *p = (node *)malloc(sizeof(node));
	p->info = x;
	p->next = top;
	top = p;
	return top;
}


/**********************/
/*删除链式栈的栈顶结点*/
/**********************/
node *pop(node *top)
{
	node *q;
	if(!top)
	{
		printf("\n链式栈时空的!");
		return NULL;
	}
	q =top;
	top = top->next;
	free(q);
	return top;
}

int main()
{
	int i,j = 0;
	node *head = init();
	printf("请输入学生的个数:\n");
	scanf("%d",&j);
	for(i = 0;i < j;i ++)
	{
		int p = 0;
		printf("请输入第%d个值：\n",i + 1);
		scanf("%d",&p);
		head = push(head,p);
	}
	printf("链式栈的数据为:\n");
	display(head);
}
