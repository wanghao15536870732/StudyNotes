#include"stdio.h"
#include"stdlib.h"
typedef struct node
{
	int data;
	struct node* next;
}S;
int main()
{
	S *h = NULL, *q = NULL, *p = NULL;
	int a, n, i, sum, count;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &a);
		p = (struct node *)malloc(sizeof(S));
		p->data = a; p->next = NULL;
		if (i == 1)
		{
			h = p; q = p;
		}
		else
		{
			q->next = p; q = p;
		}
	}
	count = 0;
	scanf("%d", &a);
	p = h;
	while (p)
	{
		if (p->data == a)
			count++;
		p = p->next;
	}
	p = h;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
	printf("%d\n", count);
	return 0;
}

