#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
typedef int ElemType;
#define MAX_SIZE 5  // 定义队列的最大容量
typedef struct {
    int data[MAX_SIZE];  // 存储队列元素的数组
    int front;           // 队头指针
    int rear;            // 队尾指针
} SeqQueue;

void initqueue(SeqQueue *sq) {
    sq->front = 0;
    sq->rear = 0;
}
bool isfull(SeqQueue* sq){
    if ((sq->rear + 1) % MAX_SIZE == sq->front) {
        return true;
    }
    else
        return false;
}
bool isempty(SeqQueue* sq) {
    if (sq->front == sq->rear) {
        return true;
    }
    else
        return false;
}
void enqueue(SeqQueue *sq,int x) {
    if (isfull(sq)) {
        cout << "队列已满" << endl;
        return;
    }
    else {
        sq->data[sq->rear] = x;
        sq->rear = (sq->rear + 1) % MAX_SIZE;
        return;
    }  
}
void dequeue(SeqQueue* sq) {
    if (isempty(sq)) {
        cout << "队列已空" << endl;
        return;
    }
    else {
        cout << sq->data[sq->front] << endl;
        sq->front = (sq->front + 1) % MAX_SIZE;
        return;
    }
}

int main() {
    SeqQueue sq;
    initqueue(&sq);
    enqueue(&sq, 1);
    enqueue(&sq, 2);
    enqueue(&sq, 3);
    enqueue(&sq, 4);
    enqueue(&sq, 5);
    enqueue(&sq, 6);
    dequeue(&sq);
    dequeue(&sq);
    dequeue(&sq);
    dequeue(&sq);
    dequeue(&sq);
}