#include"stdio.h"
#include"stdlib.h"
#define M 20  /*预定义图的最大顶点数*/
#include"string.h"

typedef struct node{  //边表结点 
	int adjvex;        //邻接点 
	struct node *next;
}edgenode;

typedef struct vnode{   //头节点类型 
	char vertex;        //顶点信息 
	edgenode *firstedge;  //邻接表表头指针 
}vertexnode;

typedef struct{         //邻接表类型 
	vertexnode adjlist[M];  //存放头节点的顺序表 
	int n,e;     //图的顶点数与边数 
}linkedgraph;

int visited[M];

void createwithfile(linkedgraph *g,char *filename,int c)  //c = 0表示创建无向图 
{
	int i,j,k;
	edgenode *s;
	FILE *fp;
	fp = fopen(filename,"r");
	if(fp)
	{
		fscanf(fp,"%d%d",&g->n,&g->e); //读入顶点数与边数 
		for(i = 0;i < g->n;i ++)
		{
			fscanf(fp,"%d",&g->adjlist[i].vertex);  //读入顶点信息 
			g->adjlist[i].firstedge = NULL;       //边表置为空表 
		}
		for(k =0 ;k < g->e;k ++)    //循环e次建立边表 
		{
			fscanf(fp,"%d%d",&i,&j);      //读入无序对（i,j) 
			s = (edgenode*)malloc(sizeof(edgenode));
			s->adjvex = j;       //邻接点序号为j 
			s->next = g->adjlist[i].firstedge;
			g->adjlist[i].firstedge = s;  //将新节点*s插入顶点Vi的边表头部 
			if(c == 0)
			{
				s = (edgenode*)malloc(sizeof(edgenode));
			    s->adjvex = i;  //邻接点序号为i 
			    s->next = g->adjlist[j].firstedge;  //将新节点*s插入顶点Vj的边表头部 
			    g->adjlist[j].firstedge = s;
			}
		}
		fclose(fp);
	}
	else
		g->n = 0;  ///文件打开失败 

}

linkedgraph *create(int c)  //c = 0表示创建无向图 
{
	linkedgraph *g;
	g = (linkedgraph *)malloc(sizeof(linkedgraph));
	int i,j,k;
	edgenode *s;
	printf("输入结点数和边数：\n");
	scanf("%d%d",&g->n,&g->e); //读入顶点数与边数
	printf("输入结点值：\n");
	getchar();
	for(i = 0;i < g->n;i ++)
	{
		scanf("%c",&g->adjlist[i].vertex);  //读入顶点信息 
		getchar();
		g->adjlist[i].firstedge = NULL;       //边表置为空表 
	}
	if(c == 0)
		printf("输入无序对：\n");
	else
		printf("输入有序对：\n");
	for(k = 0 ;k < g->e;k ++)    //循环e次建立边表 
	{
		scanf("%d%d",&i,&j);      //读入无序对（i,j) 
		s = (edgenode *)malloc(sizeof(edgenode));
		s->adjvex = j;       //邻接点序号为j 
		s->next = g->adjlist[i].firstedge;
		g->adjlist[i].firstedge = s;  //将新节点*s插入顶点Vi的边表头部 
		if(c == 0)
		{
			s = (edgenode*)malloc(sizeof(edgenode));
		    s->adjvex = i;  //邻接点序号为i 
		    s->next = g->adjlist[j].firstedge;  //将新节点*s插入顶点Vj的边表头部 
		    g->adjlist[j].firstedge = s;
		}
	}
	return g;
}

void dfs(linkedgraph *g,int i)
{
	edgenode *p;
	printf("visit vertex：%c \n",g->adjlist[i].vertex);  //访问顶点i 
	visited[i] = 1;
	p = g->adjlist[i].firstedge;
	while(p)   //从p的邻接点出发进行深度优先搜索 
	{
		if(!visited[p->adjvex])
			dfs(g,p->adjvex);
		p = p->next;
	}
}
void dfstraverse(linkedgraph *g)
{
	int i;
	for(i = 0;i < g->n;i ++)
		visited[i] = 0;
	for(i = 0;i < g->n;i ++)
		if(!visited[i])
			dfs(g,i);
}

void bfs(linkedgraph *g,int i)
{
	int j;
	edgenode *p;
	int queue[M],front,rear;  //创建一个队列 
	front = rear = 0;  //初始化空队列
	printf("%c ",g->adjlist[i].vertex);  //访问根节点 
	visited[i] = 1;
	queue[rear ++] = i;  //被访问结点进队 
	while(rear > front)
	{
		j = queue[front ++]; //出队
		p = g->adjlist[i].firstedge;
		while(p)
		{
			if(visited[p->adjvex] == 0)
			{
				printf("%c ",g->adjlist[p->adjvex].vertex);
				queue[rear ++] = p->adjvex;
				visited[p->adjvex] = 1;
			} 
			p = p->next; 
		} 
	} 
}

int bfstraverse(linkedgraph *g)
{
	int i,count = 0;
	for(i = 0;i < g->n;i ++)
		visited[i] = 0;
	for(i = 0;i < g->n;i ++)
		if(!visited[i])  //vi未被访问过
		{
			printf("\n");
			count ++;
			bfs(g,i); 
		} 
	return count;
} 



int main()
{
	linkedgraph *h;
	h = create(0); 
	printf("深度遍历：\n");
	dfstraverse(h);
	printf("广度遍历：\n");
	int count = bfstraverse(h);
	printf("\n此图的连通分量为：\n");
	printf("%d\n",count);
	return 0;
}


