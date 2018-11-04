#include "stdio.h"
#include "stdlib.h"

//二叉树链式储存的结构体 
typedef struct node{
	int data;
	struct node *lchild,*rchild;
}bintnode;
//全局变量 
bintnode *root;  /*指向二叉树跟结点的指针*/ 

//顺序栈的头文件
typedef struct stack
{
	bintnode *data[100];  
	int tag[100]; /*为栈中的每个元素设置的标记*/
	int top; /*栈顶指针*/ 
} seqstack; 

//二叉树的递归算法

//前序遍历
void preorder(bintnode *t)
{
	if(t)
	{
		printf("%c ",t->data);
		preorder(t->lchild);
		preorder(t->rchild);
	}
 } 
 
//中序遍历
void inorder(bintnode *t)
{
 	if(t)
 	{
 		inorder(t->lchild);
 		printf("%c ",t->data);
 		inorder(t->rchild);
	 }
}

//后序遍历
void postorder(bintnode *t)
{
	if(t)
	{
		postorder(t->lchild);
		postorder(t->rchild);
		printf("%c ",t->data);
	}
}

//二叉树的非递归实现
void push(seqstack *s,bintnode *t)  /*进栈*/
{
	s->data[s->top] = t;
	s->top ++; 
}

bintnode *pop(seqstack *s)
{
	if(s->top != 0)
	{
		s->top --;
		return (s->data[s->top]);
	}
	else
		return NULL;
}

//二叉树前序遍历的非递归实现
void preorder1(bintnode *t)
{
	seqstack s;
	s.top = 0;
	while((t) || (s.top != 0))
	{
		if(t)
		{
			printf("%c ",t->data);
			push(&s,t);
			t = t->lchild;
		}
		else
		{
			t = pop(&s);
			t = t->rchild;
		}
	}
} 

//二叉树中序遍历的非递归实现
void inorder1(bintnode *t)
{
	seqstack s;
	s.top = 0;
	while((t != NULL) || (s.top != 0))
	{
		if(t)
		{
			push(&s,t);
			t = t->lchild; 
		}
		else
		{
			t = pop(&s);
			printf("%c ",t->data);
			t = t->rchild;
		}
	}
}

//二叉树后序遍历的非递归实现
void postorder1(bintnode *t)
{
	seqstack s;
	s.top = 0;
	while((t) || (s.top != 0))
	{
		if(t)
		{
			s.data[s.top] = t;
			s.tag[s.top] = 0;
			s.top ++;
			t = t->lchild;
		}
		else
		{
			if(s.tag[s.top - 1] == 1)
			{
				s.top --;
				t = s.data[s.top];
				printf("%c ",t->data);
				t = NULL;
			}
			else
			{
				t = s.data[s.top - 1];
				s.tag[s.top - 1] = 1;
				t = t->rchild;
				
				
			}
		}
	}
} 

//根据前序遍历创建一棵二叉树 
bintnode *createbintree()
{
	char ch;
	bintnode *t;
	if((ch = getchar())== '#')
		t = NULL;
	else
	{
		t = (bintnode *)malloc(sizeof(bintnode));
		t->data = ch;
		t->lchild = createbintree();
		t->rchild = createbintree();
	}
	return t;
}

//根据中序遍历创建一颗二叉树 
bintnode *createbintree1()
{
	char ch;
	bintnode *t;
	if((ch = getchar()) == '#')
		t = NULL;
	else
	{ 
		t = (bintnode *)malloc(sizeof(bintnode));
		t->lchild = createbintree();
		t->data = ch;
		t->rchild = createbintree(); 
	}
	return t; 
}


int main()
{
	printf("前序遍历方式创建一颗二叉树：\n");
	root = createbintree();
	printf("前序遍历递归输出这颗二叉树：\n");
	preorder(root);
	printf("\n前序遍历非递归输出这颗二叉树：\n");
	preorder1(root);
	printf("\n中序遍历递归输出这颗二叉树：\n");
	inorder(root);
	printf("\n中序遍历非递归输出这颗二叉树：\n");
	inorder1(root); 
	printf("\n后序遍历递归输出这颗二叉树：\n");
	postorder(root);
	printf("\n后序遍历非递归输出这颗二叉树：\n");
	postorder(root); 
	printf("\n");
	system("pause");
	return 0;
}
//cba###de#gf##h###
