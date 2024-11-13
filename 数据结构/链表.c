#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
struct Node {
    int data;
    struct Node* next;
};

// 初始化链表
struct Node* initializeList() {
    return NULL;
}

// 在链表头部插入节点
struct Node* insertAtBeginning(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        return head;
    }
    newNode->data = data;
    newNode->next = head;
    return newNode;
}

// 在链表尾部插入节点
struct Node* insertAtEnd(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        return head;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

// 在链表中查找节点
struct Node* search(struct Node* head, int data) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// 从链表中删除节点
struct Node* deleteNode(struct Node* head, int data) {
    if (head == NULL) {
        return NULL;
    }

    if (head->data == data) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    struct Node* current = head;
    while (current->next != NULL) {
        if (current->next->data == data) {
            struct Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
            return head;
        }
        current = current->next;
    }

    printf("未找到要删除的节点\n");
    return head;
}

// 打印链表元素
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 释放链表内存
void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node* head = initializeList();

    head = insertAtBeginning(head, 10);
    head = insertAtBeginning(head, 20);
    head = insertAtEnd(head, 30);
    head = insertAtEnd(head, 40);

    printf("链表元素: ");
    printList(head);

    struct Node* searchResult = search(head, 30);
    if (searchResult != NULL) {
        printf("查找结果: 找到 %d\n", searchResult->data);
    }
    else {
        printf("查找结果: 未找到\n");
    }

    head = deleteNode(head, 30);
    printf("删除节点后的链表: ");
    printList(head);

    freeList(head);
    return 0;
}
