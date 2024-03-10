#include<stdio.h>
#include<iostream>


using namespace std;

//采用跟单链表相同的结构体，但初始化的时候与单链表会有不同
typedef struct Lnode {
	int data;
	struct Lnode* next;
}Lnode,*Linklist;

Linklist initRLinklist() {
	Linklist head = (Linklist)malloc(sizeof(Lnode));
	if (head == NULL) {
		cout << "分配失败" << endl;
	}
	head->next = head;
	return head;
}
Linklist createRLinklist(Linklist head) {
	Linklist temp = head;
	int data;
	cout << "请输入" << endl;
	cin >> data;
	while (data != -1) {
		Linklist node = (Linklist)malloc(sizeof(Lnode));
		if (node == NULL) {
			cout << "分配失败" << endl;
		}
		node->data = data;
		node->next = temp->next;
		temp->next = node;
		temp = node;
		cin >> data;
	}
	temp->next = head;
	return head;
}
void printRList(Linklist head) {
	Linklist node = head->next;
	while (node != head) {
		cout << node->data << " ";
		node = node->next;
	}
}
void misPrintRList(Linklist head) {
	//也可以循环的打印链表，感受一下“循环性”
	Linklist node = head->next;
	while (node != NULL) {
		cout << node->data << " ";
		node = node->next;
	}
	//处于头节点的data是没有赋值的因此在执行过程中会打印随机值
}
bool Empty(Linklist head) {
	if (head->next == head) {
		return true;
	}
	else
		return false;
}
int main() {
	Linklist head = initRLinklist();
	createRLinklist(head);
	if (Empty(head)) {
		cout << "链表为空" << endl;
	}
	else {
		cout << "链表不为空" << endl;
	}
	printRList(head);
	//misPrintRList(head);
	//执行效果如下
	/*
	请输入
1
2
3
-1
链表不为空
1 2 3*/
}