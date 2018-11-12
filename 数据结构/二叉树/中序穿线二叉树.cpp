#include "stdio.h"
#include "stdlib.h"

typedef struct node
{
	char data;
	int ltag,rtag;
	struct node *lchild,*rchild;
}bintnode;
bintnode *pre = NULL;

bintnode *createbintree()
{
	char ch;
	bintnode *t;
	if((ch = getchar()) == '#')
		t = NULL;+
	else
	{
		t = (bintnode *)malloc(sizeof(bintnode));
		t->data = ch;
		t->lchild = createbintree();
		t->rchild = createbintree();
	}
	return t;
}

void inthreading(bintnode *p)
{
	if(p)
	{
		inthreading(p->rchild);
		p->ltag = (p->lchild) ? 0 : 1;
		p->rtag = (p->rchild) ? 0 : 1;
		if(pre)
		{
			if(pre->rtag == 1)
				pre->rchild = p;
			if(p->ltag == 1)
				p->lchild = pre;
		}
		pre = p;
		inthreading(p->rchild);
	}
}

//创建中序穿线二叉树
void createthrtree(bintnode *p)
{
	p = createbintree();
	inthreading(p);
}

int main()
{
	bintnode *root;
	createthrtree(root);
	return 0;
}
