#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 100 // 最大顶点数设为100
#define INFINITY 65535 // ∞设为双字节无符号整数的最大值65535
typedef int Vertex; // 用顶点下标表示顶点,为整型
typedef int WeightType; // 边上权值的数据类型
typedef char DataType; // 顶点存储的数据类型

// 邻接矩阵图结构体
typedef struct {
    int Nv; // 顶点数
    int Ne; // 边数
    WeightType G[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 邻接矩阵
    DataType Data[MAX_VERTEX_NUM]; // 存储顶点数据
} MGraph;

// 初始化一个有VertexNum个顶点但没有边的图
MGraph* CreateGraph(int VertexNum) {
    Vertex V, W;
    MGraph* Graph;
    Graph = (MGraph*)malloc(sizeof(MGraph)); // 建立图
    Graph->Nv = VertexNum; // 初始化顶点数
    Graph->Ne = 0; // 初始化边数
    // 初始化邻接矩阵
    // 注意：默认顶点编号从0开始，到(Graph->Nv - 1)
    for (V = 0; V < Graph->Nv; V++)
        for (W = 0; W < Graph->Nv; W++)
            Graph->G[V][W] = INFINITY;
    return Graph;
}

// 插入一条边
void InsertEdge(MGraph* Graph, Vertex V1, Vertex V2, WeightType W) {
    // 插入边<V1, V2>
    Graph->G[V1][V2] = W;
    // 若是无向图，还要插入边<V2, V1>
    Graph->G[V2][V1] = W;
}

// 建立一个图的邻接矩阵表示
MGraph* BuildGraph() {
    MGraph* Graph;
    Vertex V1, V2;
    WeightType W;
    int Nv, i;
    scanf("%d", &Nv); // 读入顶点个数
    Graph = CreateGraph(Nv); // 初始化一个有Nv个顶点但没有边的图
    scanf("%d", &(Graph->Ne)); // 读入边数
    if (Graph->Ne != 0) { // 如果有边
        // 读入边，格式为"起点 终点 权重"，插入邻接矩阵
        for (i = 0; i < Graph->Ne; i++) {
            scanf("%d %d %d", &V1, &V2, &W);
            InsertEdge(Graph, V1, V2, W);
        }
    }
    // 如果顶点有数据的话，读入数据
    for (V1 = 0; V1 < Graph->Nv; V1++)
        scanf(" %c", &(Graph->Data[V1]));
    return Graph;
}

// 打印邻接矩阵
void PrintGraph(MGraph* Graph) {
    Vertex V, W;
    printf("图的顶点为:\n");
    for (V = 0; V < Graph->Nv; V++)
        printf("%c ", Graph->Data[V]);
    printf("\n输出邻接矩阵:\n");
    printf("\t");
    for (V = 0; V < Graph->Nv; V++)
        printf("\t%8c", Graph->Data[V]);
    for (V = 0; V < Graph->Nv; V++) {
        printf("\n\n%8c", Graph->Data[V]);
        for (W = 0; W < Graph->Nv; W++) {
            if (Graph->G[V][W] == INFINITY)
                printf("\t%8s", "∞");
            else
                printf("\t%8d", Graph->G[V][W]);
        }
        printf("\n");
    }
}

// 主函数
int main() {
    MGraph* Graph;
    Graph = BuildGraph(); // 建立图的邻接矩阵
    PrintGraph(Graph); // 打印邻接矩阵
    return 0;
}
