#include <stdio.h>
#include <limits.h>

#define V 6  // 图中顶点的数量

// 从尚未包括在最短路径树中选择最小距离的顶点
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// 打印最终的最短路径
void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

// 执行Dijkstra算法来计算从源到所有其他顶点的最短路径
void dijkstra(int graph[V][V], int src) {
    int dist[V];     // 存储从源到每个顶点的最短路径
    int sptSet[V];   // 为已包括在最短路径树中的顶点创建一个布尔数组

    // 初始化所有距离为无穷大，sptSet为假（0）
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // 源顶点到自身的距离为0
    dist[src] = 0;

    // 寻找到达所有顶点的最短路径
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);

        // 将选定的顶点标记为已包括
        sptSet[u] = 1;

        // 更新距离值
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // 打印最终结果
    printSolution(dist);
}

int main() {
    // 一个示例邻接矩阵表示图
    int graph[V][V] = {
        {0, 2, 4, 0, 0, 0},
        {0, 0, 1, 7, 0, 0},
        {0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 2, 0, 5},
        {0, 0, 0, 0, 0, 0}
    };

    int src = 0;  // 源顶点的索引

    printf("Shortest paths from source vertex %d:\n", src);
    dijkstra(graph, src);

    return 0;
}
