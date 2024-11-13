#include <stdio.h>
#include <stdlib.h>
const int V =4;
const int E=5;
// 边的结构体
struct Edge {
    int src, dest, weight;
};

// 图的结构体
struct Graph {
    int V, E;
    struct Edge* edge;
};

// 创建图的函数
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));
    return graph;
}

// 查找集合的根节点
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// 集合的合并函数
void Union(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    if(xset != yset) {
        parent[xset] = yset;
    }
}

// 比较函数，用于qsort
int compare(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

// Kruskal算法的主函数
void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];  // 保存最小生成树的边
    int e = 0;  // 结果数组的索引
    int i = 0;  // 排序后所有边的索引

    // 步骤1：按边的权重排序
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compare);

    // 分配内存
    int *parent = (int*) malloc(V * sizeof(int));

    // 初始化所有顶点都是独立的集合
    memset(parent, -1, sizeof(int) * V);

    // 步骤2：遍历所有的边，选择不构成环的边
    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edge[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        // 如果选择的边不构成环，则加入结果中
        if (x != y) {
            result[e++] = next_edge;
            Union(parent, x, y);
        }
        // 否则，丢弃该边
    }

    // 打印构成的最小生成树
    printf("构成的最小生成树包括以下边:\n");
    int minimumCost = 0;
    for (i = 0; i < e; ++i) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("最小生成树的权重是 %d\n", minimumCost);

    // 清理内存
    free(parent);
    free(graph->edge);
    free(graph);
}

// 主函数
int main() {
    /* 示例输入:
       顶点数 = 4
       边数 = 5
       边: (0, 1, 10), (0, 2, 6), (0, 3, 5), (1, 3, 15), (2, 3, 4)
    */
    /*int V = 4;  // 顶点数
    int E = 5;  // 边数*/
    struct Graph* graph = createGraph(V, E);

    // 添加边 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;

    // 添加边 0-2
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;

    // 添加边 0-3
    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;

    // 添加边 1-3
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;

    // 添加边 2-3
    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;

    // 运行Kruskal算法
    KruskalMST(graph);

    return 0;
}
/*这行代码的作用是初始化`parent`数组，它代表了图中每个顶点的父节点。
在Kruskal算法的开始，我们假设图中的每个顶点都是一个独立的集合，即每个顶点都是自己集合的代表或根节点。

在`parent`数组中，我们用`-1`来表示一个顶点是集合的根节点。
所以，`memset(parent, -1, sizeof(int) * V);`这行代码将整个`parent`数组的值都设置为`-1`，从而表示一开始每个顶点都是一个独立的集合的根节点。

在算法执行过程中，当我们选择一条边，如果这条边连接的两个顶点属于不同的集合，
我们就将它们合并成一个集合。这时，我们会更新`parent`数组来反映这些变化。
这样，我们可以保证选择的边不会形成环，因为环会意味着图中存在一个顶点可以通过两条不同的路径到达，
这违反了最小生成树的性质。希望这能帮助您更好地理解这段代码的作用！如果还有其他问题，欢迎继续提问。*/