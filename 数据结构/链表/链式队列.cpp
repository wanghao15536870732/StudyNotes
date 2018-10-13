/*
链式队列
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

typedef struct{
	node *front,*rear; /*定义队首与队尾指针*/
}queue;



/**********************/
/*建立一个空的链式队列*/
/**********************/
queue *init()
{
	queue *qu;
	qu = (queue *)malloc(sizeof(queue));
	qu->front = NULL;
	qu->rear = NULL;
	return qu;
}


/**********************/
/*判断链式队列是否为空*/
/**********************/
int empty(queue qu)
{
	return (qu.front ? 0 : 1);
}

/****************************/
/*输出链式队列中各个节点的值*/
/****************************/
void display(queue *qu)
{
	node *p = qu->front;
	printf("\n");
	if(!p)
		printf("链式队列是空的!\n");
	while(p)
	{
		printf("%d-->",p->info);
		p = p->next;
	}
	printf("\n");
}

/*************************/
/*取得链式队列的队首结点值*/
/*************************/
int read(queue qu)
{
	if(!qu.front)
	{
		printf("链式队列是空的！");
		exit(1);
	}
	return (qu.front->info);
}


/***********************************/
/*向链式队列当中插入一个值为x的结点*/
/***********************************/
queue *insert(queue *qu,datatype x)
{
	node *p = (node *)malloc(sizeof(node));
	p->info = x;
	p->next = NULL;
	if(qu->front == NULL)
		/*当前队列为空，新插入的结点作为队列中的唯一一个结点*/
		qu->front = qu->rear = p;
	else
	{
		qu->rear->next = p;/*队尾插入*/
		qu->rear = p;
	}
	return qu;
}

/**************************/
/*删除链式队列中的队首结点*/
/*************************/
queue *dele(queue *qu)
{
	node *q;
	if(!qu->front)
	{
		printf("队列为空，无法删除！");
		return qu;
	}
	q = qu->front;/*q指向队首结点*/
	qu->front = q->next;/*对手指针指向下一个结点*/
	free(q);/*释放原队列首结点空间*/
	if(qu->front == NULL)
		qu->rear = NULL;/*队列中的唯一结点被删除后，队列变空*/
	return qu;

}

int main()
{
	int i,j = 0;
	queue *qu = init();
	printf("请输入数据的个数：\n");
	scanf("%d",&j);
	for(i = 0;i < j;i ++)
	{
		int k = 0;
		printf("请输入第%d个数据：\n",i + 1);
		scanf("%d",&k);
		qu = insert(qu,k); 
	}
	printf("队列中的数据为：\n");
	display(qu);
}
