#include<stdio.h>
#include<iostream>


using namespace std;

typedef struct Lnode {
	int data;
	struct Lnode* next;
}Lnode,*Linklist;
Linklist initlinklist() {
	Linklist head;
	head = (Linklist)malloc(sizeof(Lnode));
	if (head == NULL) {
		cout << "分配失败" << endl;
	}
	head->next = NULL;
	return head;
}
Linklist createListHead(Linklist head) {//头插法 注意头插法在输出遍历时的顺序是倒序
	int data;
	cout << "请输入" << endl;
	cin >> data;
	while (data!=-1) {
		Linklist node= (Linklist)malloc(sizeof(Lnode));
		if (node == NULL) {
			cout<< "分配失败" << endl;
		}
		node->data = data;
		node->next = head->next;
		head->next = node;
		cin >> data;
	}
	return head;
}
Linklist createListTail(Linklist head) {//尾插法
	int data;
	cout << "请输入" << endl;
	cin >> data;
	Linklist temp = head;
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
	return head;
}
int lengthLinklist(Linklist head) {
	Linklist temp = head;
	int length = 0;
	while (temp->next != NULL) {
		temp = temp->next;
		length++;
	}
	return length;
}
Linklist DeleteNodeVal(Linklist head,int value) {//按照数值删除节点
	Linklist temp = head;
	while (temp->next != NULL) {
		if (temp->next->data == value) {
			Linklist res = temp->next;
			temp->next = temp->next->next;
			free(res);
		}
		else {
			temp = temp->next;
		}
	}
	return head;
}
Linklist DeleteNodePos(Linklist head, int pos) {//按照位置删除节点
	Linklist temp = head;
	while (pos-1) {
		temp = temp->next;
		pos--;
	}
	if (temp->next == NULL) {
		cout << "删除节点的位置有误" << endl;
		return head;
	}
	Linklist res = temp->next;
	temp->next = temp->next->next;
	free(res);
	return head;
}
Linklist insertNode(Linklist head,int pos,int value) {//Pos指在第Pos个节点后插入一个新节点
	Linklist temp = head;
	while (pos) {
		temp = temp->next;
		pos--;
	}
	if (temp == NULL) {
		cout << "插入位置有误" << endl;
		return head;
	}
	
	Linklist node = (Linklist)malloc(sizeof(Lnode));
	node->data = value;
	node->next = temp->next;
	temp->next = node;
	return head;
}
void printList(Linklist head) {//遍历整个链表然后输出打印
	Linklist node = head->next;
	while (node!= NULL) {
		cout << node->data << " ";
		node = node->next;
	}
	cout << endl;
}


int main() {
	Linklist head=initlinklist();
	createListTail(head);
	DeleteNodeVal(head, 3);
	cout << "删除值为3的节点后" << endl;
	printList(head);
	DeleteNodePos(head,5);
	cout << "删除位置为5的节点" << endl;
	printList(head);
	insertNode(head, 2, 6);
	cout << "在第二个位置后插入值为6的节点" << endl;
	printList(head);
	cout << "链表长度为"<<lengthLinklist(head);
	//执行效果如下
	/*
	请输入
    1
    2
    3
    4
    5
    6
    7
    -1
删除值为3的节点后
1 2 4 5 6 7
删除位置为5的节点
1 2 4 5 7
在第二个位置后插入值为6的节点
1 2 6 4 5 7
链表长度为6
	*/
}
