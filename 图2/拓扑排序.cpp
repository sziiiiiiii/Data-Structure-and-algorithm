#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<queue>
#include<iostream>
#include<stack>
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
       // G->E[index2][index1] = weight;
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
bool TopologicalSort(Graph G) {
    //统计出所有顶点的入度
    vector<int> indegree(G.n + 1, 0);
    for (int i = 1; i <= G.n; i++) {
        for (int j = 1; j <= G.n; j++) {
            if (G.E[j][i] != 0) {
                indegree[i]++;
            }
        }
    }
    //初始化栈，存储入度为0的结点
    stack<int> mystack;
    for (int i = 1; i <= G.n; i++) {
        if (indegree[i] == 0) {
            mystack.push(i);
        }
    }
    int count = 0;//记录已输出顶点数
    while (!mystack.empty()) {
        int index = mystack.top();//元素序号出栈
        cout <<G.V[index] << endl;//打印顶点
        count++;//计数加一
        mystack.pop();
        for (int i = 1; i <= G.n; i++) {
            if (G.E[index][i] != 0) {//遍历所有顶点，对于刚才出栈的元素，例如a,检查所有a指向的节点，将其入度减一
                indegree[i]--;
                if (indegree[i] == 0) {//减一后入度为0就入栈
                    mystack.push(i);
                }
            }
        }
    }
    if (count < G.n) {//count<G.n,说明打印的元素不足，故拓扑排序失败
        cout << "有回路" << endl;
        return false;
    }
    else {
        cout <<  "拓扑排序成功" << endl;
        return true;
    }
}
int main() {
    Graph G;
    InitGraph(&G);      //初始化邻接矩阵 
    CreateGraph(&G);    //建立邻接矩阵 
    cout << "图的邻接矩阵为：" << endl;
    PrintGraph(G);      //输出邻接矩阵 
    bool a=TopologicalSort(G);
}
