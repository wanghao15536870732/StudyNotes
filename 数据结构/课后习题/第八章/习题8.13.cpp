/*编写一个非递归深度优先遍历图的函数。
【答】：图的深度优先遍历类似于二叉树的前序遍历，非递归实现时可以用一个栈保存已访问
过的结点，这些结点的邻接点可能还没有全部访问完成，遍历过程中可能需要回溯。
参考程序如下：*/

#include <stdlib.h>
#include <stdio.h>

#define m 20 /*预定义图的最大顶点数*/
#define MAXSIZE 100 /*定义栈的最大容量*/

int visited[m];

typedef char datatype; /*顶点信息数据类型*/
typedef struct node
{               /*边表结点*/
    int adjvex; /*邻接点*/
    struct node *next;
} edgenode;

typedef struct vnode
{                        /*头结点类型*/
    datatype vertex;     /*顶点信息*/
    edgenode *firstedge; /*邻接链表头指针*/
} vertexnode;

typedef struct
{                          /*邻接表类型*/
    vertexnode adjlist[m]; /*存放头结点的顺序表*/
    int n, e;              /*图的顶点数与边数*/
} adjgraph;


void dfs(adjgraph g, int i)
{ /*以vi为出发点对邻接表表示的图g进行深度优先遍历*/
    edgenode *p;
    edgenode *stack[MAXSIZE]; /*栈用来保存回溯点*/
    int top = -1;
    printf("visit vertex: %c ", g.adjlist[i].vertex); /*访问顶点i*/
    visited[i] = 1;
    p = g.adjlist[i].firstedge;
    while (top > -1 || p) /*当栈不空或p不空时*/
    {
        if (p) /*优先处理p不空的情况*/
            if (visited[p->adjvex])
                p = p->next;
            else
            {
                printf("%c ", g.adjlist[p->adjvex].vertex);
                visited[p->adjvex] = 1;
                stack[++top] = p;
                p = g.adjlist[p->adjvex].firstedge;
            }
        else /*从栈中进行回溯*/
            if (top > -1)
            {
                p = stack[top--];
                p = p->next;
            }
    }
}

void dfstraverse(adjgraph g)
{
    int i;
    for (i = 0; i < g.n; i++)
        visited[i] = 0; /*初始化标志数组*/
    for (i = 0; i < g.n; i++)
        if (!visited[i]) /*vi未访问过*/
            dfs(g, i);
}