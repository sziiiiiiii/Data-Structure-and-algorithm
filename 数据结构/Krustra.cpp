#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 边结构体
struct Edge {
    int src, dest, weight;
};

// 用于排序的比较函数
bool comp(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// 查找集合的根（使用路径压缩）
int find(vector<int>& parent, int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

// 合并两个集合
void Union(vector<int>& parent, vector<int>& rank, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// Kruskal算法主函数
void KruskalMST(vector<Edge>& edges, int V) {
    sort(edges.begin(), edges.end(), comp); // 按边权重排序

    vector<int> parent(V);
    vector<int> rank(V, 0);

    // 初始化每个顶点的集合
    for (int i = 0; i < V; ++i)
        parent[i] = i;

    vector<Edge> mst; // 存储最小生成树的边

    for (Edge e : edges) {
        int x = find(parent, e.src);
        int y = find(parent, e.dest);

        // 如果包含这条边不会形成环路
        if (x != y) {
            mst.push_back(e);
            Union(parent, rank, x, y);
        }
    }

    // 打印最小生成树的边
    cout << "Following are the edges in the constructed MST\n";
    for (Edge e : mst)
        cout << e.src << " -- " << e.dest << " == " << e.weight << endl;
}

// 测试代码
int main() {
    int V = 4; // 顶点数目
    int E = 5; // 边数目
    vector<Edge> edges(E);

    // 添加边 0-1
    edges[0].src = 0;
    edges[0].dest = 1;
    edges[0].weight = 10;

    // 添加边 0-2
    edges[1].src = 0;
    edges[1].dest = 2;
    edges[1].weight = 6;

    // 添加边 0-3
    edges[2].src = 0;
    edges[2].dest = 3;
    edges[2].weight = 5;

    // 添加边 1-3
    edges[3].src = 1;
    edges[3].dest = 3;
    edges[3].weight = 15;

    // 添加边 2-3
    edges[4].src = 2;
    edges[4].dest = 3;
    edges[4].weight = 4;

    KruskalMST(edges, V);

    return 0;
}
