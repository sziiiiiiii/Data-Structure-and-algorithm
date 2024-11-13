#include <stdio.h>
#include<iostream>
#include<vector>
using namespace std;
#define INF 99999
#define MAXSIZE 100
#define MAXDISTANCE 10000 
bool visited[MAXSIZE] = { false };
typedef struct {
    int n, e;      //图的顶点、图的边
    char V[MAXSIZE];    //一维数组，存储顶点
    int E[MAXSIZE][MAXSIZE];  //二维数组，存储顶点之间关系
} Graph;
/*初始化邻接矩阵*/
void InitGraph(Graph* G) {
    int i, j;
    for (i = 0; i < MAXSIZE; i++)
        for (j = 0; j < MAXSIZE; j++)
            G->E[i][j] = 0;
}
/*图的邻接矩阵建立*/
void CreateGraph(Graph* G) {
    int i, j, k;
    char ch1, ch2, X;

    cout << "请输入图的顶点数目：" << endl;
    cin >> G->n;

    cout << "请输入图的边的数目：" << endl;
    cin >> G->e;

    cout << "请输入各顶点的信息：" << endl;
    for (i = 1; i <= G->n; i++) {
        cout << "输入第" << i << "个顶点：" << endl;
        cin >> G->V[i];
    }
    for (k = 0; k < G->e; k++) {
        cout << "建立第" << k + 1 << "条边（以空格隔开）" << endl;
        cin >> ch1 >> ch2;
        cout << "输入这条边的权值" << endl;
        int weight;
        cin >> weight;
        int index1 = 0;
        int index2 = 0;
        for (int i = 1; i <= G->n; i++) {
            if (ch1 == G->V[i]) {
                index1 = i;
            }
            if (ch2 == G->V[i]) {
                index2 = i;
            }
        }
        G->E[index1][index2] = weight;
        G->E[index2][index1] = weight;
        //若建立有向图的话，只需要G->E[index1][index2] = 1;一次赋值即可
    }
}
void PrintGraph(Graph G) {
    int i, j;
    for (i = 1; i <= G.n; i++) {
        for (j = 1; j <= G.n; j++)
            cout << G.E[i][j];
        cout << endl;
    }
}
//Dijkstra算法如下
//注意：Dijkstra算法不能求带有负权值的图
void Floyd(Graph* G) {
    vector<vector<int>> dist((G->n + 1), vector<int>((G->n + 1), 0));
    for (int i = 1; i < dist.size(); i++) {
        for (int j = 1; j < dist[0].size(); j++) {
            if (i != j && G->E[i][j] == 0) {
                dist[i][j] = INF;
            }
            else
            dist[i][j] = G->E[i][j];
        }
       
    }
    for (int k = 1; k <= G->n; k++) {
        for (int i = 1; i <= G->n; i++) {
            for (int j = 1; j <= G->n; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    for (int i = 1; i < dist.size(); i++) {
        for (int j = 1; j < dist[0].size(); j++) {
            if (dist[i][j] != 0)
                cout << G->V[i] << "到" << G->V[j] << "距离" << dist[i][j] << " ";
            else if(i!=j&&dist[i][j]==INF)
                cout << "不可达" << endl;
        }
        cout << endl;
    }
}
int main() {   
    Graph G;
    InitGraph(&G);      //初始化邻接矩阵 
    CreateGraph(&G);    //建立邻接矩阵 
    cout << "图的邻接矩阵为：" << endl;
    PrintGraph(G);      //输出邻接矩阵 
    Floyd(&G);
}
/*

Floyd算法和Dijkstra算法是两种经典的图算法，用于解决最短路径问题。它们在时间复杂度上有所不同。

1.Dijkstra算法的时间复杂度：

在使用邻接表表示图的情况下，Dijkstra算法的时间复杂度为O((V + E)logV)，
其中V是顶点数，E是边数。这是因为在每次选择最短路径时，需要通过堆或优先队列来寻找最短路径的顶点，
每个顶点的插入和删除操作都需要logV的时间复杂度。
在使用邻接矩阵表示图的情况下，Dijkstra算法的时间复杂度为O(V^2)，
其中V是顶点数。这是因为需要对每个顶点进行松弛操作，每个顶点都需要查找其邻接顶点的最短路径，
而邻接矩阵查找邻接顶点的时间复杂度为O(V)。


2.Floyd算法的时间复杂度：

Floyd算法的时间复杂度为O(V^3)，其中V是顶点数。
这是因为Floyd算法通过三重循环来计算每对顶点之间的最短路径。
每个循环的迭代次数都是V，因此总的时间复杂度为O(V^3)。

需要注意的是，Dijkstra算法适用于解决单源最短路径问题，
即从一个顶点到其他所有顶点的最短路径。而Floyd算法适用于解决多源最短路径问题，
即任意两个顶点之间的最短路径。
因此，在实际应用中，根据具体的问题需求选择合适的算法。
*/