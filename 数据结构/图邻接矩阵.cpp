#include <stdio.h>
#include<iostream>
using namespace std;
#define MAXSIZE 100
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
        
        
        cout << "输入第"<<i<<"个顶点：" << endl;
        cin >> G->V[i];
    }
    for (k = 0; k < G->e; k++) {
       
        
        cout << "建立第"<<k+1<<"条边（以空格隔开）" << endl;
        cin >> ch1 >> ch2;
        for (i = 1; i <= G->n; i++)
            for (j = 1; j <= G->n; j++)
                if (ch1 == G->V[i] && ch2 == G->V[j]) {
                    G->E[i][j] = 1;
                    G->E[j][i] = 1;
                    break;
                }
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
        for (int i = 1; i <= G->n; i++) {
            for (int j = 1; j <= G->n; j++) {
                if (ch == G->V[i] && c == G->V[j]) {
                    G->E[i][j] = 1;
                    G->E[j][i] = 1;
                }
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
/*主函数*/
int main() {
    Graph G;
    InitGraph(&G);      //初始化邻接矩阵 
    CreateGraph(&G);    //建立邻接矩阵 
    cout << "图的邻接矩阵为：" << endl;
    PrintGraph(G);      //输出邻接矩阵 
    Insert(&G);       //插入结点
    PrintGraph(G);
    DeleteVertex(&G);//删除结点
    PrintGraph(G);
}
