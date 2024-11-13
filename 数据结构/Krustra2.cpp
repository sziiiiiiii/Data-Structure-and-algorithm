#include <stdio.h>
#include <stdbool.h>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<iostream>
#include<queue>
#include<stack>
#include<list>
#include <algorithm>
#include<set>
#include<map>
#define MAX_EDGES 100

typedef struct
{
    int src, dest, weight;
} Edge;

typedef struct
{
    int parent, rank;
} Subset;

// 查找根节点
int find(Subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// 合并两个子集
void Union(Subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// 比较函数，用于排序边的权重
int compare(const void *a, const void *b)
{
    Edge *a1 = (Edge *)a;
    Edge *b1 = (Edge *)b;
    return a1->weight - b1->weight;
}

// Kruskal算法计算最小生成树
void KruskalMST(Edge edges[], int V, int E)
{
    Edge result[MAX_EDGES];
    int e = 0;
    int i = 0;

    // 对边按权重进行排序
    qsort(edges, E, sizeof(Edge), compare);

    // 创建V个子集，每个子集只包含一个顶点
    Subset *subsets = (Subset *)malloc(V * sizeof(Subset));
    for (int v = 0; v < V; v++)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // 选择E个边，直到生成树中包含V-1条边
    while (e < V - 1 && i < E)
    {
        Edge next_edge = edges[i++];

        // 查找边的两个顶点所属的子集
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // 如果两个顶点不属于同一个子集，则将边加入生成树中，并合并两个子集
        if (x != y)
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // 输出最小生成树的边和权重
    printf("Edge \tWeight\n");
    for (i = 0; i < e; i++)
        printf("%d - %d \t%d\n", result[i].src, result[i].dest, result[i].weight);
}

int main()
{
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    Edge edges[MAX_EDGES];
    printf("Enter the source, destination, and weight of each edge:\n");
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    KruskalMST(edges, V, E);

    return 0;
}
/*
这段代码实现了Kruskal算法，用于求解最小生成树。下面是对代码的详细注释：

find函数：查找顶点所属的子集，采用路径压缩的方式。
Union函数：合并两个子集，根据子集的rank值进行合并。
compare函数：比较函数，用于对边按权重进行排序。
KruskalMST函数：Kruskal算法计算最小生成树。
创建一个空的结果数组result和一个大小为V的子集数组subsets。
对边按权重进行排序。
遍历排序后的边，选择权重最小且两个顶点不在同一个子集的边。
将边加入结果数组，并合并两个顶点所属的子集。
输出最小生成树的边和权重。
main函数：读取输入的顶点数和边数，以及每条边的起点、终点和权重。调用KruskalMST函数计算最小生成树。
注意：这只是Kruskal算法的一个简单实现示例，实际应用中可能需要根据具体情况进行适当修改和优化。
*/
