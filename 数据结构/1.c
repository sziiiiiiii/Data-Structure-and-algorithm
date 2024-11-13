#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
//////////////////////////////////////////// 

//定义结点类型 
typedef struct Node
{
    ElemType data;              //单链表中的数据域 
    struct Node* next;          //单链表的指针域 
}Node, * LinkedList;

LinkedList initLinkedlist() {
    LinkedList head;
    head = (LinkedList)malloc(sizeof(head));
    if (head == NULL) {
        printf("初始化失败");
    }
    head->next = NULL;
    return head;
}
LinkedList createlisthead(LinkedList head) {
    ElemType num;
    scanf("%d", &num);
    while (num != -1) {
        LinkedList node;
        node = (LinkedList)malloc(sizeof(LinkedList));
        if (node == NULL) {
            printf("分配空间失败");
        }
        node->data = num;
        node->next = head->next;
        head->next = node;
        scanf("%d", &num);
    }
    return head;
}

LinkedList createlisttail(LinkedList head) {
    ElemType num;
    LinkedList r;
    r = head;
    scanf("%d", &num);
    while (num != -1) {
        LinkedList node;
        node= (LinkedList)malloc(sizeof(LinkedList));
        if (node == NULL) {
            printf("分配空间失败");
        }
        node->data = num;
        r->next = node;
        r = node;
        scanf("%d", &num);
    }
    r->next = NULL;
    return head;
}

LinkedList insertlist(LinkedList head, ElemType pos, ElemType num) {
    Node* pre;
    pre = head;
    for (int i = 0; i < pos - 1; i++) {
        pre = pre->next;
    }
    Node* p;
    p = (Node*)malloc(sizeof(Node*));
    p->data = num;
    p->next = pre->next;
    pre->next = p;
    return head;
}


LinkedList searchnode(LinkedList head, ElemType num) {
    LinkedList current = head;
    while(current != NULL) {
        if (current->data == num) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//LinkedList deletenode(LinkedList head, ElemType num) {//删除节点的函数有bug
//    LinkedList current = head;
//    while (current->next != NULL) {
//        if (current->next->data == num) {
//            current->next = current->next->next;
//            free(current->next);
//            return head;
//        }
//        current = current->next;
//    }
//    return head;
//}

void printlist(LinkedList head) {
    LinkedList current = head->next;

    while(current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}
int main() {

    LinkedList head;
    head = initLinkedlist();
    //head = createlisthead(head);
    head = createlisthead(head);
    
    
    printlist(head);

}