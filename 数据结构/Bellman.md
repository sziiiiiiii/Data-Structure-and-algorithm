```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 定义图的边
struct Edge {
    int src, dest, weight;
};

// 定义图
struct Graph {
    int V, E;
    struct Edge* edge;
};

// 创建图
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// 实现Bellman-Ford算法
void BellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    // 初始化距离数组
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // 通过松弛操作更新距离数组
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // 检测负权回路
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("图中包含负权回路\n");
            return;
        }
    }

    // 打印最短路径
    printf("顶点\t距离源点的最短距离\n");
    for (int i = 0; i < V; i++)
        printf("%d\t%d\n", i, dist[i]);
}

int main() {
    int V = 5; // 图的顶点数
    int E = 8; // 图的边数
    struct Graph* graph = createGraph(V, E);

    // 添加图的边
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = -1;

    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 4;

    graph->edge[2].src = 1;
    graph->edge[2].dest = 2;
    graph->edge[2].weight = 3;

    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 2;

    graph->edge[4].src = 1;
    graph->edge[4].dest = 4;
    graph->edge[4].weight = 2;

    graph->edge[5].src = 3;
    graph->edge[5].dest = 2;
    graph->edge[5].weight = 5;

    graph->edge[6].src = 3;
    graph->edge[6].dest = 1;
    graph->edge[6].weight = 1;

    graph->edge[7].src = 4;
    graph->edge[7].dest = 3;
    graph->edge[7].weight = -3;

    BellmanFord(graph, 0);

    return 0;
}
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 定义边的结构体
struct Edge {
    int source; // 边的起点
    int destination; // 边的终点
    int weight; // 边的权重
};

// 定义图的结构体
struct Graph {
    int V; // 图的顶点数
    int E; // 图的边数
    struct Edge* edge; // 图的边数组
};

// 创建图的函数
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V; // 设置顶点数
    graph->E = E; // 设置边数
    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge)); // 分配边数组的内存
    return graph;
}

// Bellman-Ford算法实现
void BellmanFord(struct Graph* graph, int source) {
    int V = graph->V; // 获取顶点数
    int E = graph->E; // 获取边数
    int distances[V]; // 存储从源点到每个顶点的距离

    // 初始化距离数组，除了源点为0，其余都为无穷大
    for (int i = 0; i < V; i++)
        distances[i] = INT_MAX;
    distances[source] = 0;

    // 松弛操作，进行V-1次
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].source;
            int v = graph->edge[j].destination;
            int weight = graph->edge[j].weight;
            // 如果u点的距离不是无穷大且通过u到v的距离比当前存储的要小，则更新v的距离
            if (distances[u] != INT_MAX && distances[u] + weight < distances[v])
                distances[v] = distances[u] + weight;
        }
    }

    // 检测负权回路，再进行一次松弛操作，如果还能更新距离，则存在负权回路
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].source;
        int v = graph->edge[i].destination;
        int weight = graph->edge[i].weight;
        if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
            printf("图中存在负权回路");
            return;
        }
    }

    // 打印结果，显示从源点到每个顶点的最短距离
    printf("顶点距离源点的最短距离:\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, distances[i]);
}

// 主函数
int main() {
    int V = 5; // 顶点数
    int E = 8; // 边数
    struct Graph* graph = createGraph(V, E);

    // 添加边的信息。例如：graph->edge[0].source = 0; graph->edge[0].destination = 1; graph->edge[0].weight = -1;

    // 调用BellmanFord算法，以0号顶点为源点
    BellmanFord(graph, 0);

    return 0;
}

```

### 实际用例  https://kamacoder.com/problempage.php?pid=1152
```c
#include <iostream>
#include <vector>
#include <list>
#include <climits>
using namespace std;

int main() {
    int n, m, p1, p2, val;
    cin >> n >> m;

    vector<vector<int>> grid;

    // 将所有边保存起来
    for(int i = 0; i < m; i++){
        cin >> p1 >> p2 >> val;
        // p1 指向 p2，权值为 val
        grid.push_back({p1, p2, val});

    }
    int start = 1;  // 起点
    int end = n;    // 终点

    vector<int> minDist(n + 1 , INT_MAX/2);
    minDist[start] = 0;
    for (int i = 1; i < n; i++) { // 对所有边 松弛 n-1 次
        for (vector<int> &side : grid) { // 每一次松弛，都是对所有边进行松弛
            int from = side[0]; // 边的出发点
            int to = side[1]; // 边的到达点
            int price = side[2]; // 边的权值
            // 松弛操作 
            // minDist[from] != INT_MAX/2 防止从未计算过的节点出发
            if (minDist[to] > minDist[from] + price && minDist[from] != INT_MAX/2) { 
                minDist[to] = minDist[from] + price;  
            }
        }
    }
    if (minDist[end] == INT_MAX/2) cout << "unconnected" << endl; // 不能到达终点
    else cout << minDist[end] << endl; // 到达终点最短路径

}
```



