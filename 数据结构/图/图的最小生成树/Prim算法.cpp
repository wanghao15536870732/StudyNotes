#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#define M 30  /*预定义图的最大顶点数*/
#define FINITY 5000  //用 5000代替无穷


//最小生成树算法的结构体
typedef struct {
	char vexs[M];  //顶点的数据域
	int edges[M][M];  //定义的邻接矩阵
	int n, e;  //图中的顶点数和边数
}Mgraph;


typedef struct edgedata
{
	int beg, en;  //beg,en都是顶点序号
	int length;  //边长
}edge;



void create(Mgraph *g, char *filename, int c)  //c = 0表示创建无向图 
{
	int weight = 0;  //边的权值
	int front, rear; //变得前驱和后驱
	FILE *file;
	file = fopen(filename, "r"); //从文件读取图的边信息
	if (file)
	{
		fscanf(file, "%d%d\n", &g->n, &g->e);  //读取图的顶点数与边数
		for (int i = 0; i < g->n; i++)
		{
			fscanf(file, "%c", &g->vexs[i]);  //读取图中顶点的信息域
		}
		for (int i = 0; i < g->n; i++)
		{
			for (int j = 0; j < g->n; j++)
			{
				if (i == j)
					g->edges[i][j] = 0;  //对角线上的均为0
				else
					g->edges[i][j] = FINITY;  //没有赋值的域均加成无
			}
		}
		for (int k = 0; k < g->e; k++)
		{
			fscanf(file, "%d%d%d", &front, &rear, &weight);
			g->edges[front][rear] = weight;  //只些相应顺序的，即有向图
			if (c == 0)
				g->edges[rear][front] = weight;  //对称图形，即为无向图
		}
		fclose(file);
	}
	else
	{
		g->n = 0;
		printf("文件打开失败！\n");
	}
}




//最小生成树的prim算法
void prim(Mgraph g, edge tree[M - 1])
{
	edge x;
	/*
	min 保存最小的权值
	s 保存排序后当前节点，用于选择排序，就像选择排序中保存下标值一样

	*/
	int d, min, s, v;
	for (v = 1; v <= g.n - 1; v++)  //v从1开始到顶点数 - 1
	{
		tree[v - 1].beg = 0;  //从顶点v0开始求最小生成树
		tree[v - 1].en = v;  //边顶点
		tree[v - 1].length = g.edges[0][v];  //距离根节点的所有边的权值
	}
	for (int k = 0; k <= g.n - 3; k++)  //依次求当前(第k条)最小两栖边，并加入TREE,基本思想就是选择排序
	{
		min = tree[k].length;  //min用于保存最小权值
		s = k;  //保存交换之前的下标
		for (int j = k + 1; j <= g.n - 2; j++)
		{
			if (tree[j].length < min)
			{
				min = tree[j].length;  //保存最小权值
				s = j; //保存排序后当前的下标
			}
		}
		v = tree[s].en;  //入选的结点
		/*交换两个结构体，就像选择排序中交换两个值一样*/
		x = tree[s];
		tree[s] = tree[k];
		tree[k] = x;
		for (int j = k + 1; j <= g.n - 2; j++)
		{
			d = g.edges[v][tree[j].en];   //从邻接矩阵当中获取接下来的节点到其他节点的权值
			if (d < tree[j].length)  //如果d的权值小于邻接矩阵中的实际权值
			{
				tree[j].length = d; //赋值权值
				tree[j].beg = v; //赋值
			}
		}
	}

	printf("\n最小生成树为：\n");
	for (int j = 0; j <= g.n - 2; j++)
	{
		printf("\n%c---%c %d\n", g.vexs[tree[j].beg], g.vexs[tree[j].en], tree[j].length);
	}

	printf("\n根节点为：%c\n", g.vexs[0]);
}

int main()
{
	Mgraph h;
	edge tree[M - 1];
	char filename[20] = "D:\\Desktop\\Test.txt";
	create(&h, filename, 0);
	prim(h, tree);
	system("pause");
	return 0;
}

