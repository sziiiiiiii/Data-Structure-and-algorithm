#include<stdio.h>
#include<iostream>


using namespace std;
//----双链表
typedef struct DNode {
	int data;
	struct DNode* prior, * next;
}DNode,*DLinklist;

DLinklist initDlinkList() {
	DLinklist head;
    head = (DLinklist)malloc(sizeof(DNode));
	if (head == NULL) {
		cout << "分配失败" << endl;
	}
	head->next = NULL;
	head->prior = NULL;
	return head;
}
DLinklist createDLinklistHead(DLinklist head) {
	DLinklist temp = head;
	int data;
	cout << "请输入" << endl;
	cin >> data;
	while (data != -1) {
		DLinklist node = (DLinklist)malloc(sizeof(DNode));
		//若写成这样：head = (DLinklist)malloc(sizeof(head));，则会报错
		//但对于单向链表来说并不会，不知道为什么
		node->data = data;
		node->next = temp->next;
		node->prior = temp;
		temp->next = node;
		temp = node;
		cin >> data;		
	}
	return head;
}
void printDLinklistPre(DLinklist head) {//从头向尾遍历
	DLinklist temp = head->next;
	cout << "从头向尾遍历的结果为:" << endl;
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}
void printDLinklistPost(DLinklist head) {//从尾向头遍历
	DLinklist temp = head->next;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	cout << "从尾向头遍历的结果为:" << endl;
	while (temp != head) {//头结点处没有data，所以只需要判断是否到头节点为止
		cout << temp->data << " ";
		temp = temp->prior;
	}
	cout << endl;
}
DLinklist DLinklistInsert(DLinklist head,int position,int value) {//指定位置处的插入
	//position代表插入到第position个元素之后(不算入头节点)
	DLinklist temp = head;
	while (position&&temp!=NULL) {
		temp = temp->next;
		position--;
	}
	if (temp == NULL) {
		cout << "插入出错" << endl;
		return head;
	}
	DLinklist node = (DLinklist)malloc(sizeof(DNode));
	node->data = value;
	if (temp->next != NULL) {//保证插入的位置不是最后一个节点
		temp->next->prior = node;
	}
	node->next = temp->next;
	temp->next = node;
	node->prior = temp;
	
	return head;
}
DLinklist DeleteNextDnode(DLinklist head,int position) {//position表示删除第几个元素
	DLinklist temp = head;
	while (position-1&&temp->next!=NULL ) {
		temp = temp->next;
		position--;
	}
	if (temp->next == NULL) {
		cout << "删除元素的位置出错" << endl;
		return head;
	}
	if (temp->next->next == NULL) {//删除元素为最后一个元素的对应情况
		DLinklist res = temp->next;
		temp->next = temp->next->next;
		free(res);
		return head;
	}
	DLinklist res = temp->next;
	temp->next->next->prior = temp;
	temp->next = temp->next->next;
	free(res);
	return head;
}

int main() {
	DLinklist head=initDlinkList();
	createDLinklistHead(head);
	
	DLinklistInsert(head, 1, 5);//在第一个节点后插入5
	
	DeleteNextDnode(head, 4);//删除第四个节点
	
	printDLinklistPre(head);
	
	printDLinklistPost(head);
	//执行效果如下
	/*
	请输入
1
2
3
4
5
6
-1
从头向尾遍历的结果为:
1 5 2 4 5 6
从尾向头遍历的结果为:
6 5 4 2 5 1
	*/
}