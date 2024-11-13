#include <stdio.h>
#include<queue>
#include<iostream>
using namespace std;
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
        G->E[index1][index2] = 1;
        G->E[index2][index1] = 1;
       //若建立有向图的话，只需要G->E[index1][index2] = 1;一次赋值即可
    }
}
void Insert(Graph* G) {
    cout << "输入你要添加的顶点信息" << endl;
    char ch;
    cin >> ch;
    G->n++;
    G->V[G->n] = ch;
    cout << "输入要和哪个点建立边" << endl;
    char c;
    while (cin >> c) {
        if (c == '#')
            break;
        for (int i = 1; i < G->n; i++) {
            if (c == G->V[i]) {
                G->E[i][G->n] = 1;
                G->E[G->n][i] = 1;
            }
        }
    }
    cout << "添加完成" << endl;
}

void DeleteVertex(Graph* G) {
    cout << "要删除的节点元素是：" << endl;
    char ch;
    cin >> ch;
    for (int i = 1; i <= G->n; i++) {
        if (G->V[i] == ch) {
            for (int j = 1; j <= G->n; j++) {
                G->E[i][j] = 0;
                G->E[j][i] = 0;
            }
            break;
        }
    }
    cout << "删除完毕" << endl;
    //若删除元素为a，即就是将矩阵中a元素所在行所在列全部设为0
}
/*输出邻接矩阵*/
void PrintGraph(Graph G) {
    int i, j;
    for (i = 1; i <= G.n; i++) {
        for (j = 1; j <= G.n; j++)
            cout << G.E[i][j];
        cout << endl;
    }
}
vector<int> FindNeighbor(Graph *G,int ch) {//找到某个节点所有的邻接节点
    vector<int> result;
    for (int i = 1; i <= G->n; i++) {
        if (G->V[ch] == G->V[i]) {
            for (int j = 1; j <= G->n; j++) {
                if (G->E[i][j] == 1) {
                    result.push_back(j);
                }
            }
        }
    }
    return result;
}
void BFS(Graph *G,char ch) {//广度优先遍历  ch为要遍历的节点的开始
    queue<int> myque;
    for (int i = 1; i <= G->n; i++) {
        if (ch == G->V[i]) {
            visited[i] = true;
            myque.push(i);
            break;
        }
    }
    while (!myque.empty()) {
        int temp = myque.front();
        cout << G->V[temp];
        myque.pop();
        vector<int> result=FindNeighbor(G,temp);
        for (int i = 0; i < result.size(); i++) {
            if (visited[result[i]] == false) {
                myque.push(result[i]);
                visited[result[i]] = true;
            }
        }
    }
    //到这里广度优先搜索已经完成，但是如果是非连通图，通过这一个BFS函数也无法全部遍历
    //所以借助visited数组可以看看哪些元素没有被遍历，再进行BFS遍历
    //我们可以借助BFSTraverse函数来调用BFS函数完成这件事
    //如果图是连通的，可直接调用BFS 
}
void BFSTraverse(Graph* G) {
    for (int i = 1; i <= G->n; i++) {
        if (!visited[i]) {
            BFS(G, G->V[i]);
        }
    }
}


void DFS(Graph* G,char ch) {
    int index = 0;
    for (int i = 1; i <= G->n; i++) {
        if (ch == G->V[i]) {
            visited[i] = true;
            cout << ch;
            index = i;
            break;
        }
    }
    vector<int> result = FindNeighbor(G, index);
    for (int i = 0; i < result.size(); i++) {
        if (visited[result[i]] == false) {
            DFS(G, G->V[result[i]]);
        }
    }
    //对于深度优先搜索和前面的广度优先搜索一样，对于非连通图，得再写一个函数进行判断
}

void DFSTraverse(Graph* G) {
    for (int i = 1; i <= G->n; i++) {
        if (!visited[i]) {
            DFS(G, G->V[i]);
        }
    }
}
//求某个顶点到其他顶点的最短路径
void BFSminDistance(Graph* G) { //只适合于不带权图
    vector<int> d((G->n + 1), MAXDISTANCE);
    vector<int> path((G->n + 1), -1);
    queue<int> myque;
    char ch;//输入你要求的顶点
    cout << "输入你要求的顶点" << endl;
    cin >> ch;
    int index = 0;
    for (int i = 1; i <= G->n; i++) {
        if (ch == G->V[i])
            index = i;
    }
    d[index] = 0;
    visited[index] = true;
    myque.push(index);
    while (!myque.empty()) {
        int temp = myque.front();
        myque.pop();
        vector<int> result = FindNeighbor(G, temp);
        for (int i = 0; i < result.size(); i++) {
            if (!visited[result[i]]) {
                d[result[i]] = d[temp] + 1;
                path[result[i]] = temp;
                visited[result[i]] = true;
                myque.push(result[i]);
            }
        }
    }
    //广度优先遍历结束后 ，d[i]中的每个值代表着各个顶点到所求顶点的距离，path[]代表最短路劲从哪过来
    for (int i = 1; i < d.size(); i++) {
        if (d[i] == MAXDISTANCE) {
            cout << G->V[i] << "无法到达" << ch << endl;
        }
        else
        cout << G->V[i] << "距离" << ch << "为" << d[i] << endl;
    }

}


/*主函数*/
int main() {
   
    Graph G;
    InitGraph(&G);      //初始化邻接矩阵 
    CreateGraph(&G);    //建立邻接矩阵 
    cout << "图的邻接矩阵为：" << endl;
    PrintGraph(G);      //输出邻接矩阵 
    DFSTraverse(&G);
    //BFSTraverse(&G);
    //Insert(&G);       //插入结点
    //PrintGraph(G);
    //DeleteVertex(&G);//删除结点
    //PrintGraph(G);
}




