#include <stdio.h>
#include <stdlib.h>

// 定义十字链表结点
typedef struct ArcNode {
    int tailvex;             // 边的起点
    int headvex;             // 边的终点
    struct ArcNode *hlink;   // 指向下一个以该顶点为终点的边
    struct ArcNode *tlink;   // 指向下一个以该顶点为起点的边
} ArcNode;

// 顶点表头结点
typedef struct VNode {
    int data;                // 顶点信息
    ArcNode *firstin;        // 指向第一条以该顶点为终点的边
    ArcNode *firstout;       // 指向第一条以该顶点为起点的边
} VNode;

// 图的结构定义
typedef struct {
    VNode *vertices;         // 顶点数组
    int vexnum, arcnum;      // 顶点数和边数
} OrthogonalList;

// 初始化图
OrthogonalList* initGraph(int vexnum) {
    OrthogonalList *G = (OrthogonalList*)malloc(sizeof(OrthogonalList));
    G->vexnum = vexnum;
    G->arcnum = 0;
    G->vertices = (VNode*)malloc(vexnum * sizeof(VNode));
    
    for (int i = 0; i < vexnum; i++) {
        G->vertices[i].data = i;
        G->vertices[i].firstin = NULL;
        G->vertices[i].firstout = NULL;
    }
    return G;
}

// 添加边
void addEdge(OrthogonalList *G, int tail, int head) {
    ArcNode *arc = (ArcNode*)malloc(sizeof(ArcNode));
    arc->tailvex = tail;
    arc->headvex = head;

    // 插入到tail顶点的出边表中
    arc->tlink = G->vertices[tail].firstout;
    G->vertices[tail].firstout = arc;

    // 插入到head顶点的入边表中
    arc->hlink = G->vertices[head].firstin;
    G->vertices[head].firstin = arc;

    G->arcnum++;
}

// 打印图的结构
void printGraph(OrthogonalList *G) {
    printf("Graph structure:\n");
    for (int i = 0; i < G->vexnum; i++) {
        printf("Vertex %d:\n", G->vertices[i].data);
        
        // 打印出边
        printf("  Out edges:");
        ArcNode *out = G->vertices[i].firstout;
        while (out) {
            printf(" %d -> %d", out->tailvex, out->headvex);
            out = out->tlink;
        }
        printf("\n");

        // 打印入边
        printf("  In edges:");
        ArcNode *in = G->vertices[i].firstin;
        while (in) {
            printf(" %d -> %d", in->tailvex, in->headvex);
            in = in->hlink;
        }
        printf("\n");
    }
}

// 释放图的内存
void freeGraph(OrthogonalList *G) {
    for (int i = 0; i < G->vexnum; i++) {
        ArcNode *arc = G->vertices[i].firstout;
        while (arc) {
            ArcNode *temp = arc;
            arc = arc->tlink;
            free(temp);
        }
    }
    free(G->vertices);
    free(G);
}

// 主函数示例
int main() {
    int vexnum = 4; // 顶点数量
    OrthogonalList *G = initGraph(vexnum);

    // 添加边
    addEdge(G, 0, 1);
    addEdge(G, 0, 2);
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);

    // 打印图
    printGraph(G);

    // 释放内存
    freeGraph(G);

    return 0;
}
