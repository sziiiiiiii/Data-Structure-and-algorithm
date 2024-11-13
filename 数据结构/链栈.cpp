#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
typedef struct Linkstack {
	int data;
	struct Linkstack* next;
}Linkstack, * Linkstacknode;
Linkstacknode initstack() {
	Linkstacknode top;
	top = (Linkstack*)malloc(sizeof(Linkstack));
	if (top == NULL) {
		cout << "分配失败" << endl;
	}
	top->next=NULL;
	return top;
}
Linkstacknode pushstack(Linkstacknode top) {
	int num;
	cin >> num;
	while (num != -1) {
		Linkstacknode node;
		node = (Linkstack*)malloc(sizeof(Linkstack));
		if (node == NULL) {
			cout << "分配失败" << endl;
		}
		node->data = num;
		node->next = top->next;
		top->next = node;
		cin >> num;
	}
	return top;	
}

Linkstacknode popstack(Linkstacknode top) {
	Linkstacknode s;
	s = top->next;
	while (s->next != NULL) {
		cout << s->data;
		top->next = s->next;
		free(s);
		s = top->next;
	}
	return top;
}




int main() {
	Linkstacknode top = initstack();
	top=pushstack(top);
	popstack(top);
}

