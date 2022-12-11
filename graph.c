/*
如何用c语言写图的遍历。
要求：
1.利用邻接矩阵和邻接表两种方法创建图。
2.图的深度和广度优先搜索结果。
3.判断图是否为连通图，并打印其连通分量。
4.判断图中是否存在顶点v1到顶点v2的简单路径，并输出该路径上的顶点。
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTEX_NUM 20 // 最大顶点数
// 定义图的邻接矩阵类型
typedef struct
{
    int vertexNum;                          // 顶点数
    int edgeNum;                            // 边数
    bool g[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 邻接矩阵
} MatrixGraph;

// 定义邻接表中的结点
typedef struct LNode
{
    int v;              // 该结点对应的顶点编号
    struct LNode *next; // 指向下一个结点的指针
} LNode;

// 定义图
typedef struct ListGraph
{
    int vertexNum;                  // 图中顶点的个数
    int edgeNum;                    // 图中边的个数
    LNode *adjList[MAX_VERTEX_NUM]; // 邻接表
} ListGraph;

// 初始化图 邻接矩阵
void initGraph_J(MatrixGraph *graph)
{
    int i, j;
    // 输入顶点数和边数
    printf("请输入顶点数和边数：\n");
    scanf("%d%d", &graph->vertexNum, &graph->edgeNum);
    // 初始化邻接矩阵
    for (i = 0; i < graph->vertexNum; i++)
    {
        for (j = 0; j < graph->vertexNum; j++)
        {
            graph->g[i][j] = false;
        }
    }
    // 输入边的信息
    printf("请输入各边的两个端点（以空格分隔）：\n");
    for (i = 0; i < graph->edgeNum; i++)
    {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        graph->g[v1][v2] = graph->g[v2][v1] = true;
    }
}

// 初始化图 邻接表
void initGraph_B(ListGraph *graph)
{
    int i;
    // 输入顶点数和边数
    printf("请输入顶点数和边数：\n");
    scanf("%d%d", &graph->vertexNum, &graph->edgeNum);
    // 初始化邻接表
    for (i = 0; i < graph->vertexNum; i++)
    {
        graph->adjList[i] = NULL;
    }
    // 输入边的信息
    printf("请输入各边的两个端点（以空格分隔）：\n");
    for (i = 0; i < graph->edgeNum; i++)
    {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        // 在链表v1的头部插入结点v2
        LNode *node1 = (LNode *)malloc(sizeof(LNode));
        node1->v = v2;
        node1->next = graph->adjList[v1];
        graph->adjList[v1] = node1;
        // 在链表v2的头部插入结点v1
        LNode *node2 = (LNode *)malloc(sizeof(LNode));
        node2->v = v1;
        node2->next = graph->adjList[v2];
        graph->adjList[v2] = node2;
    }
}

// 深度优先搜索
void DFS(MatrixGraph *graph, int v, bool visited[], int path[])
{
    int i;
    // 标记顶点v为已访问
    visited[v] = true;
    // 遍历顶点v的所有邻接点
    for (i = 0; i < graph->vertexNum; i++)
    {
        if (graph->g[v][i] && !visited[i])
        {
            // 记录遍历到顶点i时，它的上一个顶点
            path[i] = v;
            DFS(graph, i, visited, path);
        }
    }
}

// 广度优先搜索
void BFS(MatrixGraph *graph, int v, bool visited[])
{
    int i, j, q[MAX_VERTEX_NUM], front = 0, rear = 0;
    // 标记顶点v为已访问
    visited[v] = true;
    printf("%d ", v); // 输出遍历到的顶点
    // 将顶点v加入队列
    q[rear++] = v;
    // 循环队列，直到队列为空
    while (front != rear)
    {
        // 取出队首元素
        i = q[front++];
        // 枚举顶点i的所有邻接点
        for (j = 0; j < graph->vertexNum; j++)
        {
            if (graph->g[i][j] && !visited[j])
            { // 如果顶点j与i相邻且未被访问
                visited[j] = true;
                printf("%d ", j); // 输出遍历到的顶点
                q[rear++] = j;    // 将顶点j加入队列
            }
        }
    }
}

// 判断图是否为连通图，并打印其联通分量
void printConnectedComponent(MatrixGraph *graph)
{
    int path[MAX_VERTEX_NUM];

    int i, j;
    bool visited[MAX_VERTEX_NUM];
    // 初始化所有顶点为未访问
    for (i = 0; i < graph->vertexNum; i++)
    {
        visited[i] = false;
    }
    // 枚举图中所有顶点
    for (i = 0; i < graph->vertexNum; i++)
    {
        if (!visited[i])
        { // 如果顶点i未被访问过
            // 以i为起点进行深度优先搜索
            DFS(graph, i, visited, path);
            printf("\n"); // 换行
        }
    }
}

// 判断图中是否存在顶点v1到顶点v2的简单路径
bool hasPath(MatrixGraph *graph, int v1, int v2)
{
    int path[MAX_VERTEX_NUM];

    int i, j;
    bool visited[MAX_VERTEX_NUM];
    // 初始化所有顶点为未访问
    for (i = 0; i < graph->vertexNum; i++)
    {
        visited[i] = false;
    }
    // 以v1为起点进行深度优先搜索
    DFS(graph, v1, visited, path);
    // 如果v2被访问过，说明v1到v2之间存在简单路径
    return visited[v2];
}

// 输出顶点v1到顶点v2的简单路径上的顶点
void printPath(MatrixGraph *graph, int v1, int v2)
{
    int i, j;
    bool visited[MAX_VERTEX_NUM];
    int path[MAX_VERTEX_NUM]; // 记录遍历到每个顶点时，它的上一个顶点
    int pathLen = 0;          // 记录简单路径的长度
    // 初始化所有顶点为未访问
    for (i = 0; i < graph->vertexNum; i++)
    {
        visited[i] = false;
    }
    // 以v1为起点进行深度优先搜索
    DFS(graph, v1, visited, path);
    // 如果v2被访问过，说明v1到v2之间存在简单路径
    if (visited[v2])
    {
        // 计算简单路径的长度
        while (v2 != v1)
        {
            path[pathLen++] = v2;
            v2 = path[v2];
        }
        path[pathLen++] = v1;
        // 输出简单路径
        for (i = pathLen - 1; i >= 0; i--)
        {
            printf("%d ", path[i]);
        }
        printf("\n");
    }
}
int main()
{
    return 0;
}