/************************/
/**** 队列的头文件 ******/
/************************/
# include "stdio.h"
# include "stdlib.h"
# define MAXSIZE 100
typedef int datatype;
typedef struct {
	datatype a[MAXSIZE];
	int front;
	int rear;
}sequence_queue;


//队列的初始化
void init(sequence_queue *sq);
//判断队列是否为空
int empty(sequence_queue sq);
//打印队列的节点值
void display(sequence_queue sq);
//取得队列得队首节点值
int get(sequence_queue sq);
//队列的插入操作
void insert(sequence_queue *sq,int x);
//队列的删除操作
void dele(sequence_queue *sq);
//循环队列的插入操作
void insert_sequence_cqueu(sequence_queue *slt,int x);
//循环队列的删除操作
void dele_quence_cqueu(sequence_queue *slt);

int main()
{
	int i = 0,j = 0,x = 0;
	sequence_queue Stu;
	init(&Stu);
	scanf("%d",&i);
	for(j = 0;j < i;j ++)
	{
		scanf("%d",&x);
		insert(&Stu,x);
	}
	printf("\n");
	printf("普通队列插入\n");
	display(Stu);
	printf("\n");
	printf("循环队列插入\n");
	for(i = 7; i < 10;i ++)
		insert_sequence_cqueu(&Stu,i);
	dele_quence_cqueu(&Stu);
	display(Stu);
	return 0;
}

/***********************/
/*** 队列的初始化 ******/
/***********************/
void init(sequence_queue *sq)
{
	sq->front = sq->rear = 0;
}

/***************************/
/*** 判断队列是否为空 ******/
/***************************/
int empty(sequence_queue sq)
{
	return (sq.front == sq.rear ? 1 : 0);
}

/***************************/
/*** 打印队列的节点值 ******/
/***************************/

void display(sequence_queue sq)
{
	int i;
	if(empty(sq))
		printf("这个队列是空的！");
	else
		for(i = sq.front;i < sq.rear;i ++)
			printf("%5d",sq.a[i]);
}

/*******************************/
/*** 取得队列得队首节点值 ******/
/*******************************/

int get(sequence_queue sq)
{
	if(empty(sq))
	{
		printf("\n顺序表是空的！无法获取队列首节点的值!\n");
		exit(1);
	}
	return sq.a[sq.front];
}

/*******************************/
/******* 队列的插入操作 ********/
/*******************************/

void insert(sequence_queue *sq,int x)
{
	int i;
	if(sq->rear == MAXSIZE)
	{
		printf("队列是满的！");
		exit(1);
	}
	sq->a[sq->rear] = x;
	sq->rear = sq->rear + 1;
}

/*******************************/
/******* 队列的删除操作 ********/
/*******************************/

void dele(sequence_queue *sq)
{
	if(sq->front == sq->rear)
	{
		printf("\n队列时空的！不能进行删除操作！\n");
		exit(1);
	}
	sq->front ++;
}


/***********************************/
/******* 循环队列的插入操作 ********/
/***********************************/

void insert_sequence_cqueu(sequence_queue *slt,int x)
{
	if((slt->rear + 1) % MAXSIZE == slt->front)
	{
		printf("顺序表已满！无法进行插入操作！\n");
		exit(1);
	}
	slt->a[slt->rear] = x;
	slt->rear = (slt->rear + 1) % MAXSIZE;
}


/***********************************/
/******* 循环队列的删除操作 ********/
/***********************************/

void dele_quence_cqueu(sequence_queue *slt)
{
	if(slt->front == slt->rear)
	{
		printf("队列是空的，无法进行删除操作！\n");
		exit(1);
	}
	slt->front = (slt->front + 1) % MAXSIZE;
}
