#include <stdio.h>
#include <stdlib.h>

//定义二叉树的结点结构
typedef struct BiTNode {
    char data; //数据域，存储结点的值
    struct BiTNode *lchild, *rchild; //指针域，指向左右子树
} BiTNode, *BiTree;

//按扩展先序遍历序列创建二叉树，用'#'表示空结点
void CreateBiTree(BiTree *T) {
    char ch;
    scanf("%c", &ch); //输入结点的值
    if (ch == '#') {
        *T = NULL; //如果是'#'，则该结点为空
    } else {
        *T = (BiTree)malloc(sizeof(BiTNode)); //否则，分配内存空间
        if (!*T) {
            exit(-1); //如果分配失败，退出程序
        }
        (*T)->data = ch; //给结点赋值
        CreateBiTree(&(*T)->lchild); //递归创建左子树
        CreateBiTree(&(*T)->rchild); //递归创建右子树
    }
}

//二叉树的先序遍历，递归算法
void PreOrderTraverse(BiTree T) {
    if (T == NULL) {
        return; //如果结点为空，直接返回
    }
    printf("%c ", T->data); //先访问根结点，打印其值
    PreOrderTraverse(T->lchild); //再递归访问左子树
    PreOrderTraverse(T->rchild); //最后递归访问右子树
}

//二叉树的中序遍历，递归算法
void InOrderTraverse(BiTree T) {
    if (T == NULL) {
        return; //如果结点为空，直接返回
    }
    InOrderTraverse(T->lchild); //先递归访问左子树
    printf("%c ", T->data); //再访问根结点，打印其值
    InOrderTraverse(T->rchild); //最后递归访问右子树
}

//二叉树的后序遍历，递归算法
void PostOrderTraverse(BiTree T) {
    if (T == NULL) {
        return; //如果结点为空，直接返回
    }
    PostOrderTraverse(T->lchild); //先递归访问左子树
    PostOrderTraverse(T->rchild); //再递归访问右子树
    printf("%c ", T->data); //最后访问根结点，打印其值
}

//二叉树的层次遍历，需要用到队列的数据结构
//定义队列的结构
typedef struct Queue {
    BiTree data[100]; //用数组存储队列中的元素，这里假设二叉树的结点不超过100个
    int front, rear; //队头和队尾的下标
} Queue;

//初始化队列
void InitQueue(Queue *Q) {
    Q->front = Q->rear = 0; //队头和队尾都指向0
}

//判断队列是否为空
int IsEmpty(Queue *Q) {
    return Q->front == Q->rear; //如果队头和队尾相等，说明队列为空
}

//入队操作，将一个元素加入队尾
void EnQueue(Queue *Q, BiTree x) {
    if ((Q->rear + 1) % 100 == Q->front) {
        printf("队列已满，无法入队\n"); //如果队尾的下一个位置是队头，说明队列已满
        return;
    }
    Q->data[Q->rear] = x; //将元素放入队尾
    Q->rear = (Q->rear + 1) % 100; //队尾后移一位，如果到达数组边界，就回到数组头部
}

//出队操作，将队头的元素删除并返回
BiTree DeQueue(Queue *Q) {
    if (IsEmpty(Q)) {
        printf("队列为空，无法出队\n"); //如果队列为空，无法出队
        return NULL;
    }
    BiTree x = Q->data[Q->front]; //取出队头的元素
    Q->front = (Q->front + 1) % 100; //队头后移一位，如果到达数组边界，就回到数组头部
    return x; //返回队头的元素
}

//二叉树的层次遍历，非递归算法
void LevelOrderTraverse(BiTree T) {
    if (T == NULL) {
        return; //如果二叉树为空，直接返回
    }
    Queue Q; //创建一个队列
    InitQueue(&Q); //初始化队列
    EnQueue(&Q, T); //将根结点入队
    while (!IsEmpty(&Q)) { //当队列不为空时，循环执行以下操作
        BiTree p = DeQueue(&Q); //将队头的元素出队，并赋值给p
        printf("%c ", p->data); //打印p的值
        if (p->lchild) {
            EnQueue(&Q, p->lchild); //如果p有左子树，将其左子树入队
        }
        if (p->rchild) {
            EnQueue(&Q, p->rchild); //如果p有右子树，将其右子树入队
        }
    }
}

//主函数，测试以上函数
int main() {
    BiTree T; //创建一个二叉树
    printf("请输入二叉树的扩展先序遍历序列，用'#'表示空结点：\n");
    CreateBiTree(&T); //按扩展先序遍历序列创建二叉树
    printf("二叉树的先序遍历结果为：\n");
    PreOrderTraverse(T); //先序遍历二叉树
    printf("\n");
    printf("二叉树的中序遍历结果为：\n");
    InOrderTraverse(T); //中序遍历二叉树
    printf("\n");
    printf("二叉树的后序遍历结果为：\n");
    PostOrderTraverse(T); //后序遍历二叉树
    printf("\n");
    printf("二叉树的层次遍历结果为：\n");
    LevelOrderTraverse(T); //层次遍历二叉树
    printf("\n");
    return 0;
}
