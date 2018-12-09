#include "stdio.h"
#include "stdlib.h"
#define M 20 /*预定义图的最大顶点数*/
#include "string.h"

typedef struct node
{               //边表结点
    int adjvex; //邻接点
    int len;
    struct node *next;
} edgenode;

typedef struct vnode
{                        //头节点类型
    char vertex;         //顶点信息
    edgenode *firstedge; //邻接表表头指针
    int id;
} vertexnode;

typedef struct
{                          //邻接表类型
    vertexnode adjlist[M]; //存放头节点的顺序表
    int n, e;              //图的顶点数与边数
} linkedgraph;

int visited[M];

linkedgraph *create(int c) //c = 0表示创建无向图
{
    linkedgraph *g;
    g = (linkedgraph *)malloc(sizeof(linkedgraph));
    int i, j, k;
    edgenode *s;
    printf("输入结点数和边数：\n");
    scanf("%d%d", &g->n, &g->e); //读入顶点数与边数
    printf("输入结点值：\n");
    getchar();
    for (i = 0; i < g->n; i++)
    {
        scanf("%c", &g->adjlist[i].vertex); //读入顶点信息
        getchar();
        g->adjlist[i].firstedge = NULL; //边表置为空表
    }
    if (c == 0)
        printf("输入无序对：\n");
    else
        printf("输入有序对：\n");
    for (k = 0; k < g->e; k++) //循环e次建立边表
    {
        scanf("%d%d%d", &i, &j, &); //读入无序对（i,j)
        s = (edgenode *)malloc(sizeof(edgenode));
        s->adjvex = j; //邻接点序号为j
        s->next = g->adjlist[i].firstedge;
        g->adjlist[i].firstedge = s; //将新节点*s插入顶点Vi的边表头部
        if (c == 0)
        {
            s = (edgenode *)malloc(sizeof(edgenode));
            s->adjvex = i;                     //邻接点序号为i
            s->next = g->adjlist[j].firstedge; //将新节点*s插入顶点Vj的边表头部
            g->adjlist[j].firstedge = s;
        }
    }
    return g;
}

//求AOE网络中时间的最早发生时间
int EarlistTime(linkedgraph gout, int ve[], int seq[])
{
    int count = 0; //计数器
    int flag[M];   //定义标记数组
    int queue[M];  //定义队列
    int front = 0, int rear = 0;
    edgenode *p;
    for (int i = 0; i < gout.n; i++) //初始化每个顶点的最早开始时间ve[i]为0
        ve[i] = 0;
    for (int j = 0; j < gout.n; j++) //初始化标记数组
        flag[j];
    for (int i = 0; i < gout.n; i++)
        if (gout.adjlist[i].id == 0 && flag[i] == 0)
        {
            queue[rear++] = i;
            flag[i] = 1; //标记被访问过
        }
    while (front < rear)
    {
        int v = queue[front++]; //队首元素出栈
        printf("%c----->", gout.adjlist[v].vertex);
        seq[count] = v; //记录拓扑排序当前元素
        count++;        //计数器 + 1
        p = gout.adjlist[v].firstedge;
        while (p)
        {
            int j = p->adjvex;
            if (--gout.adjlist[j].id == 0 && flag[0] == 0) //若入度为0则将其入队
            {
                queue[rear++] = j;
                flag[j] == 1;
            }
            if (ve[v] + p->len > ve[j])
                ve[j] = ve[v] + p->len; //ve[j]的值是从源点到顶点j的最长距离
            p = p->next;
        }
    }
    return count;
}
//求AOE网络中时间的最晚发生时间
void LateTime(linkedgraph gin, int ve[], int vl[], int seq[])
{
    int length = gin.n - 1;
    edgenode *p;
    for (int i = 0; i < gin.n; i++)
        vl[i] = ve[seq[gin.n - 1]];
    while (length > -1) //按照拓扑排序求个事件的岁晚开始时间
    {
        int v = seq[k];
        p = gin.adjlist[v].firstedge;
        while (p)
        {
            j = p->adjvex;
            if (vl[v] - p->len < vl[j])
                vl[j] = vl[v] - p->len;
            p = p->next;
        }
        length--;
    }
}

int main()
{
    linkedgraph *h;
    h = create(1);

    system("pause");
    return 0;
}