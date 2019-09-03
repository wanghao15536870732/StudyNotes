/*编写两个函数分别计算AOE网中所有活动的最早开始时间与最晚允许开始时间。
【答】：为了记录AOE网中所有活动的最早开始时间与最晚允许开始时间，定义边结点结构
edge如下，其中vi, vj存放边的起点与终点，e存放该边表示的活动的最早开始时间，l存放该
边表示的活动的最晚允许开始时间。*/
typedef struct
{
	int vi, vj;
	int e, l;
} edge;    /*定义边结构类型，存放每个活动的最早开始时间与最晚允许开始时间*/

#include"stdio.h"
#include"stdlib.h"
#define M 20  /*预定义图的最大顶点数*/
#include"string.h"

typedef struct node {  //边表结点 
	int adjvex;        //邻接点 
	int len;
	struct node *next;
}edgenode;

typedef struct vnode {   //头节点类型 
	char vertex;        //顶点信息 
	edgenode *firstedge;  //邻接表表头指针
	int id;
}vertexnode;

typedef struct {         //邻接表类型 
	vertexnode adjlist[M];  //存放头节点的顺序表 
	int n, e;     //图的顶点数与边数 
}aoegraph;

int visited[M];


/*若活动ak的尾事件是vi，头事件是vj，则e(k)就是vi的最早发生时间，l(k)是vj所允许的
最晚开始时间减去活动ak的持续的时间。求解AOE网络事件的最早发生时间与最晚允许发生
时间的算法参见教材算法8.10。
/*求AOE网中各活动的最早开始时间*/
void e(aoegraph *gout, int ve[], edge active[])
{
	int i, k = 0;
	edgenode* p;
	for (i = 0; i < gout->n; i++)  /*对出边表中的每一条边进行求解*/
	{
		p = gout->adjlist[i].firstedge;
		while (p)
		{
			active[k].vi = i;   /*边的起点*/
			active[k].vj = p->adjvex; /*边的终点*/
			active[k].e = ve[i];
			k++;
			p = p->next;
		}
	}
}

/*求AOE网中各活动的最晚允许开始时间*/
void l(aoegraph *gout, int vl[], edge active[])
{
	int i, k = 0;
	edgenode *p;
	for (i = 0; i < gout->n; i++)
	{
		p = gout->adjlist[i].firstedge;
		while (p)
		{
			active[k].l = vl[p->adjvex] - p->len;
			p = p->next;
			k++;
		}
	}
}
