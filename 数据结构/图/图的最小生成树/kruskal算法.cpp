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

//快速排序
void QuickSort(edge edges[], int left, int right) //升序算法
{
    edge x;
    int i, j, flag = 1;
    if (left < right)
    {
        i = left;
        j = right;
        x = edges[i];
        while (i < j)
        {
            while (i < j && x.length < edges[j].length)
                j--;
            if (i < j)
                edges[i++] = edges[j];
            while (i < j && x.length > edges[i].length)
                i++;
            if (i < j)
                edges[j--] = edges[i];
        }
        edges[i] = x;
        //通过递归进行另一半的排序
        QuickSort(edges, left, i - 1);
        QuickSort(edges, i + 1, right);
    }
}

//从图g的邻接矩阵读取图的所有边信息
void GetEdge(Mgraph g, edge edges[])
{
    int i, j, k = 0;
    for (i = 0; i < g.n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (g.edges[i][j] != 0 && g.edges[i][j] < FINITY)
            {
                edges[k].beg = i;
                edges[k].en = j;
                edges[k++].length = g.edges[i][j];
            }
        }
    }
}

//克鲁斯卡尔最小生成树算法
void Kruskal(Mgraph g)
{
    int i, j, k = 0, ltfl;
    int cnvx[M];
    edge edges[M * M];            //用于存放图的所有边
    edge tree[M];                 //用于存放最小生成树的边信息
    GetEdge(g, edges);            //读取所有的边
    QuickSort(edges, 0, g.e - 1); //对边进行升序排序
    for (i = 0; i < g.n; i++)
        cnvx[i] = i;              //设置每一个顶点的连通分量为其顶点编号
    for (i = 0; i < g.n - 1; i++) //树中共有g.n - 1条边
    {
        while (cnvx[edges[k].beg] == cnvx[edges[k].en]) //找到属于两个连通分量权最小的边
            k++;
        tree[i] = edges[k];       //将边k加入到生成树当中
        ltfl = cnvx[edges[k].en]; //记录选中边的终点的连通分量编号
        for (j = 0; j < g.n; j++)
        {
            if (cnvx[j] == ltfl)
                cnvx[j] = cnvx[edges[k].beg];
        }
        k++;
    }
    printf("最小生成树是：\n");
    for (j = 0; j < g.n - 1; j++)
        printf("%c---%c%6d\n", g.vexs[tree[j].beg], g.vexs[tree[j].en], tree[j].length);
}

// 图的最短路径
typedef

    int
    main()
{
    Mgraph h;
    edge tree[M - 1];
    char filename[20] = "D:\\Desktop\\Test.txt";
    create(&h, filename, 0);
    Kruskal(h);
    system("pause");
    return 0;
}
