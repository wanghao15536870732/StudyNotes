#include "stdio.h"
#include "stdlib.h"

typedef struct node
{
	int key;					  //二叉树节点定义
	struct node *lchild, *rchild; //左子树，右子树
} bsnode;

bsnode *InsertBstree(bsnode *t, int x)
{
	bsnode *root = t;
	bsnode *f = NULL, *p;
	p = root;
	while (p) //查找插入位置
	{
		if (x == p->key) //如果二叉排序树t中已有key,则无需插入
			return root;
		f = p; //用于保存新结点的最终结点的插入位置
		p = (x < p->key) ? p->lchild : p->rchild;
	}
	p = (bsnode *)malloc(sizeof(bsnode)); //生成待插入节点的新节点
	p->key = x;
	p->lchild = p->rchild = NULL;
	if (root == NULL)
		root = p; //原树为空
	else if (x < f->key)
		f->lchild = p;
	else
		f->rchild = p;
	return root;
}

bsnode *CreateBstree()
{
	bsnode *t = NULL;
	int key;
	printf("\n请输入一个以-1为结束标记的节点数列：\n");
	scanf("%d", &key);
	while (key != -1)
	{
		t = InsertBstree(t, key);
		scanf("%d", &key);
	}
	return t;
}

//中序遍历
void inorder(bsnode *t)
{
	if (t)
	{
		inorder(t->lchild);
		printf("%d ", t->key);
		inorder(t->rchild);
	}
}

//基于二叉排序树的检索算法
void bssearch1(bsnode *t, int c, bsnode *f, bsnode *p)
{
	f = NULL;
	p = t;
	while (p)
	{
		if (c == (p->key))
			return;
		f = p;
		p = c < p->key ? p->lchild : p->rchild;
	}
	return;
}

//删除二叉排序树中的任意节点，删除后仍为二叉排序树
bsnode *DelBstree(bsnode *t, int x)
{
	bsnode *p = NULL, *q = NULL, *child = NULL;
	bssearch1(t, x, p, q); //找到被删结点
	if (q)				   //找到了待删结结点
	{
		if (q->lchild == NULL && q->lchild == NULL) //情况一：被删除节点为叶子节点
		{
			if (p) //待删除结点有双亲
			{
				if (p->lchild == q)
					p->lchild = NULL;
				else
					p->rchild = NULL;
			}
			else
				t = NULL; //被删除结点为树根
			free(q);
		}
	}
	else if (q->rchild == NULL) //情况2：被删除结点的右子树为空，用被删除结点的左子树替代该节点
	{
		if (p)
		{
			if (p->lchild == q)
				p->lchild = q->lchild; //q是双亲结点的左儿子
			else
				p->rchild = q->lchild; //q是双亲结点的右儿子
		}
		else
			t = q->lchild;
		free(q);
	}
	else if (q->lchild == NULL) // 情况3：被删除结点的左子树为空，用被删除结点的右子树代替该节点
	{
		if (p) //被删除结点的双亲结点不为空
		{
			if (p->lchild == q)
				p->lchild = q->rchild; //q是双亲结点的左儿子
			else
				p->rchild = q->rchild; //q是双亲结点的右儿子
		}
		else
			t = q->rchild;
		free(q);
	}
	else //情况4：被删除结点的左右子树均不为空，用右子树代替被删除的结点，同时将被删除结点的左子树收为右子树中序遍历一开始的那个左儿子
	{
		child = q->rchild;
		while (child->lchild) //找被删除结点的右子树中序遍历时的左儿子
			child = child->lchild;
		child->lchild = q->lchild; //将被删除结点的左子树收为child的左孩子
		if (p)
		{
			if (p->lchild == q)
				p->lchild = q->rchild;
			else
				p->rchild = q->rchild;
		}
		else
			t = q->rchild; //被删除节点为树根
		free(q);
	}
	return t;
}

int main()
{
	bsnode *tree;
	tree = CreateBstree();
	inorder(tree);
	system("pause");
	return 0;
}