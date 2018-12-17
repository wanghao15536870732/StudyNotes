#include "stdio.h"
#include "stdlib.h"
#define M 20 /*预定义图的最大顶点数*/
#include "string.h"

typedef struct node
{				//边表结点
	int adjvex; //邻接点
	int len;
	struct node *next;
} edgenode;

typedef struct vnode
{						 //头节点类型
	char vertex;		 //顶点信息
	edgenode *firstedge; //邻接表表头指针
	int id;
} vertexnode;

typedef struct
{						   //邻接表类型
	vertexnode adjlist[M]; //存放头节点的顺序表
	int n, e;			   //图的顶点数与边数
} linkedgraph;

int visited[M];

linkedgraph create(char *filename, int c) //c = 0表示创建无向图
{
	linkedgraph g;
	int i, j, k;
	int weight = 0; //边的权值
	edgenode *s;
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp)
	{
		fscanf(fp, "%d%d\n", &g.n, &g.e);
		for (i = 0; i < g.n; i++)
		{
			fscanf(fp, "%c%d ", &g.adjlist[i].vertex, &g.adjlist[i].id);
			g.adjlist[i].firstedge = NULL;
		}
		for (k = 0; k < g.e; k++)
		{
			fscanf(fp, "%d%d%d", &i, &j, &weight);
			s = (edgenode *)malloc(sizeof(edgenode));
			s->adjvex = j;
			s->len = weight;
			s->next = g.adjlist[i].firstedge;
			g.adjlist[i].firstedge = s;
			if (c == 0) //无向图
			{
				s = (edgenode *)malloc(sizeof(edgenode));
				s->adjvex = i;
				s->len = weight;
				s->next = g.adjlist[j].firstedge;
				g.adjlist[i].firstedge = s;
			}
		}
		fclose(fp); //关闭文件流
	}
	else
	{
		g.n = 0;
		printf("文件打开失败！\n");
	}
	return g;
}

//求AOE网络中时间的最早发生时间
/*
事件最早发生的事件向量ve[],AOE网络的拓扑排序向量seq[]
*/
int EarlistTime(linkedgraph *gout, int ve[], int seq[])
{
	int count = 0; //计数器
	int flag[M];   //定义标记数组
	int queue[M];  //定义队列
	int front = 0;
	int rear = 0;
	edgenode *p;
	for (int i = 0; i < gout->n; i++) //初始化每个顶点的最早开始时间ve[i]为0
		ve[i] = 0;
	for (int j = 0; j < gout->n; j++) //初始化标记数组
		flag[j] = 0;
	for (int i = 0; i < gout->n; i++)
		if (gout->adjlist[i].id == 0 && flag[i] == 0)
		{
			queue[rear++] = i;
			flag[i] = 1; //标记被访问过
		}
	while (front < rear)
	{
		int v = queue[front++]; //队首元素出栈
		printf("%c----->", gout->adjlist[v].vertex);
		seq[count] = v; //记录拓扑排序当前元素
		count++;		//计数器 + 1
		p = gout->adjlist[v].firstedge;
		while (p)
		{
			int j = p->adjvex;
			if (--gout->adjlist[j].id == 0 && flag[j] == 0) //若入度为0则将其入队
			{
				queue[rear++] = j;
				flag[j] = 1;
			}
			if (ve[v] + p->len > ve[j])
				ve[j] = ve[v] + p->len; //ve[j]的值是从源点到顶点j的最长距离
			p = p->next;
		}
	}
	return count;
}
//求AOE网络中时间的最晚发生时间
/*
Aov网的入边表gin，事件发生
*/
void LateTime(linkedgraph *gin, int ve[], int vl[], int seq[])
{
	int k = gin->n - 1;
	int j = 0;
	int v = 0;
	edgenode *p = NULL;
	for (int i = 0; i < gin->n; i++)
		vl[i] = ve[seq[gin->n - 1]];
	while (k > -1) //按照拓扑排序求个事件的最晚开始时间
	{
		v = seq[k];
		p = gin->adjlist[v].firstedge;
		while (p)
		{
			j = p->adjvex;
			if (vl[v] - p->len < vl[j])
				vl[j] = vl[v] - p->len;
			p = p->next;
		}
		k--;
	}
}

int TopSort(linkedgraph *g)
{
	int k = 0, i, j, v, flag[M];
	int queue[M]; //定义队列
	int front, rear;
	edgenode *p;
	front = rear = 0; //初始化队列
	for (i = 0; i < g->n; i++)
		flag[i] = 0; //访问标记初始化
	for (i = 0; i < g->n; i++)
	{
		if (g->adjlist[i].id == 0 && flag[i] == 0)
		{
			queue[rear++] = i;
			flag[i] = 1;
		}
	}
	printf("\n该AOV网的拓扑排序为：\n");
	while (front < rear) // 如果当前队列不为空
	{
		v = queue[front++]; //队列首位元素出列
		printf("%c ", g->adjlist[v].vertex);
		k++; //计数器加1
		p = g->adjlist[v].firstedge;
		while (p) //将所有于v邻接的顶点的入度减1
		{
			j = p->adjvex;
			if (--g->adjlist[j].id == 0 && flag[j] == 0) //如果入度为0则将进队
			{
				queue[rear++] = j;
				flag[j] = 1; //标记已经被访问过
			}
			p = p->next;
		}
	}
	printf("\n");
	return k; //返回输出的结点个数
}

int main()
{
	int count = 0;
	int number = 0;
	int ve[10] = {0};  //时间最早发生时间向量
	int vl[10] = {0};  //时间晚发生时间向量
	int seq[10] = {0}; //拓扑排序向量
	char filename[30] = "D:\\Desktop\\Test.txt";
	linkedgraph h;
	h = create(filename, 1);
	number = EarlistTime(&h, ve, seq);
	LateTime(&h, ve, vl, seq);
	printf("\n");
	printf("时间最早发生时间向量：\n");
	for (int i = 0; i < 10; i++)
		printf("%d----->", ve[i]);
	printf("\n");
	printf("时间最晚发生时间向量：\n");
	for (int i = 0; i < 10; i++)
		printf("%d----->", vl[i]);
	printf("\n");

	system("pause");
	return 0;
}