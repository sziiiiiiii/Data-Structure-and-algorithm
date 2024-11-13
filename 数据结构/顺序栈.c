#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10
typedef int ElemType;
typedef struct {
    int top;
    ElemType data[MAX];
}seqstack;

void initstack(seqstack *sq){
     sq->top=-1;
     return;
}
void pushstack(seqstack *sq){
     ElemType num;
     scanf("%d",&num);
     while(num!=-1){
        if(sq->top==MAX-1){
            printf("栈已满");
            return;
        }
        sq->top++;
        sq->data[sq->top]=num;
         scanf("%d",&num);
     }
     return;
}
int popstack(seqstack *sq){
    if(sq->top==-1){
        printf("栈空");
        return -1;
    }
    int num;
    num=sq->data[sq->top];
    sq->top--;
    return num;
}
bool isempty(seqstack *sq){
    if(sq->top==-1)
    return 1;
    else
    return 0;
}
int main(){
    printf("你好");
    seqstack sq;
    initstack(&sq);
    pushstack(&sq);
    while(!isempty(&sq)){
        int num=popstack(&sq);
        printf("%d",num);
    }

}