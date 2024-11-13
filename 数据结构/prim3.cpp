#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 5

// 找到最小键值的顶点
int min_key(int key[], bool mst_set[])
{
    int min_value = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < V; v++)
    {
        // 如果顶点的键值小于当前最小值，并且顶点未被包含在最小生成树中
        if (key[v] < min_value && mst_set[v] == false)
        {
            min_value = key[v];
            min_index = v;
        }
    }
    return min_index;
}
// 使用Prim算法找到最小生成树
void prim_mst(int graph[V][V])
{
    int parent[V]; // 存储最小生成树的父节点
    bool mst_set[V]; // 标记顶点是否被包含在最小生成树中
    int key[V]; // 加入到生成树中所需的代价

    // 初始化所有顶点的键值为无穷大，标记为未被包含在最小生成树中
    for (int i = 0; i < V; i++)
    {
        key[i] = INT_MAX;
        mst_set[i] = false;
    }

    key[0] = 0; // 从第一个顶点开始构建最小生成树
    parent[0] = -1; // 第一个顶点没有父节点

    // 构建V-1条边，每次选择一个顶点加入最小生成树
    for (int count = 0; count < V - 1; count++)
    {
        int u = min_key(key, mst_set); // 找到键值最小的顶点
        mst_set[u] = true; // 将顶点标记为已被包含在最小生成树中

        // 更新与选定顶点相邻的未被包含在最小生成树中的顶点的键值和父节点
        for (int v = 0; v < V; v++)
        {
            // 如果顶点v与u相邻，并且顶点v未被包含在最小生成树中，并且边的权值小于v的键值
            if (graph[u][v] && mst_set[v] == false && graph[u][v] < key[v])
            {
                parent[v] = u; // 更新顶点v的父节点为u
                key[v] = graph[u][v]; // 更新顶点v的键值为边的权值
            }
        }
    }

    // 打印最小生成树的边和权值
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
    {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}

int main()
{
    int graph[V][V] = {{0, 2, 0, 6, 0},
                       {2, 0, 3, 8, 5},
                       {0, 3, 0, 0, 7},
                       {6, 8, 0, 0, 9},
                       {0, 5, 7, 9, 0}};

    prim_mst(graph);

    return 0;
}
