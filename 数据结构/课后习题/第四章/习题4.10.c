/*(试编写一个函数，实现在链式存储方式下字符串的strcompare（S1，S2）运算。*/

/*建立字符串链式存储结构文件linkstring.h*/
#include <stdio.h> 
#include <stdlib.h> 
typedef struct node
{
	char data;
	struct node *next;
} linkstrnode;

typedef linkstrnode *linkstring;
/*---------------------------------------*/
/*     尾插法建立单链表     */
/*---------------------------------------*/
void strcreate(linkstring *S)
{
	char ch;
	linkstrnode *p, *r;
	*S = NULL; r = NULL;
	while ((ch = getchar()) != '\n')
	{
		p = (linkstrnode *)malloc(sizeof(linkstrnode));
		p->data = ch;      /*产生新结点*/
		if (*S == NULL)  /*新结点插入空表*/
		{
			*S = p;   r = p;
		}
		else {
			r->next = p;
			r = p;
		}
	}
	if (r != NULL)  r->next = NULL;  /*处理表尾结点指针域*/
}
/*---------------------------------------------*/
/*       输出单链表的内容       */
/*---------------------------------------------*/
void print(linkstring head)
{
	linkstrnode *p;
	p = head;
	while (p)
	{
		printf("%c-->", p->data);
		p = p->next;
	}
	printf("\n");
}
int strcompare(linkstrnode*S1, linkstrnode*S2)
{
	while (S1&&S2)
	{
		if (S1->data > S2->data)
			return 1;
		else if (S1->data < S2->data)
			return -1;
		S1 = S1->next;
		S2 = S2->next;
	}
	if (S1)   return 1;
	else if (S2) return -1;
	return 0;
}
int main()
{
	linkstring s1, s2;
	int k;
	printf("\nPlease input s1:");
	strcreate(&s1); /*建立字符串s1*/
	print(s1);
	printf("\nPlease input s2:");
	strcreate(&s2);  /*建立字符串s2*/
	print(s2);
	k = strcompare(s1, s2);
	if (k == 1) 
		printf("s1>s2");
	else {
		if (k == -1)
			printf("s1<s2");
		else
			printf("s1==s2");
	}
}