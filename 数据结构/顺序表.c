#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100  // 定义最大大小

typedef struct {
    int data[MAX_SIZE];  // 存储元素的数组
    int length;          // 表示顺序表的当前长度
} SeqList;

void initList(SeqList* list) {
    list->length = 0;  // 初始化长度为0
}
// 插入操作，位置从1开始计算
int insert(SeqList* list, int position, int value) {
    if (position < 1 || position > list->length + 1 || list->length == MAX_SIZE) {
        return 0;  // 插入位置不合法或表已满
    }
    for (int i = list->length; i >= position; i--) {
        list->data[i] = list->data[i - 1];  // 向后移动元素
    }
    list->data[position - 1] = value;  // 插入新元素
    list->length++;
    return 1;
}
// 删除操作，位置从1开始计算
int delete1(SeqList* list, int position) {
    if (position < 1 || position > list->length) {
        return 0;  // 删除位置不合法
    }
    for (int i = position; i < list->length; i++) {
        list->data[i - 1] = list->data[i];  // 向前移动元素
    }
    list->length--;
    return 1;
}

// 查找操作
int find(SeqList* list, int value) {
    for (int i = 0; i < list->length; i++) {
        if (list->data[i] == value) {
            return i + 1;  // 返回位置（从1开始计算）
        }
    }
    return -1;  // 找不到时返回-1
}
int main() {
    SeqList list;
    initList(&list);

    // 示例：插入操作
    insert(&list, 1, 10);
    insert(&list, 2, 20);

    // 示例：删除操作
    delete1(&list, 1);

    // 示例：查找操作
    int pos = find(&list, 20);
    if (pos != -1) {
        printf("Element found at position: %d\n", pos);
    }
    else {
        printf("Element not found\n");
    }

    return 0;
}