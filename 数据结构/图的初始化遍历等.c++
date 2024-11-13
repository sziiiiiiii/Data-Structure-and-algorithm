#include <stdio.h>
#include<iostream>
#include<queue>
using namespace std;
#define MAXSIZE 100
typedef struct {
	int n,edge;
	char v[MAXSIZE];
	int e[MAXSIZE][MAXSIZE];
}graph;

void initgraph(graph* p) {
	cout << "请输入顶点数" << endl;
	cin >> p->n;
	for (int i = 0; i < p->n; i++) {
		for (int j = 0; j < p->n; j++) {
			p->e[i][j] = 0;
		}
	}
}
void creategraph(graph* p) {
	cout << "请输入顶点信息" << endl;
	for (int i = 0; i < p->n; i++) {
		cin >> p->v[i];
		//cout << "p->n" << p->n << endl;
	}
	cout << "请输入边的数目" << endl;
	cin >> p->edge;
	char ch1, ch2;
	for (int i = 0; i < p->edge; i++) {
		cout << "请输入边" << endl;
		cin >> ch1;
		cin >> ch2;
		for (int i = 0; i < p->n; i++) {
			for (int j = 0; j < p->n; j++) {
				if (ch1 == p->v[i] && ch2 == p->v[j]) {
					p->e[i][j] = 1;
					p->e[j][i] = 1;
				}
			}
		}
	}
	
}
void printgraph(graph* p) {
	for (int i = 0; i < p->n; i++) {
		for (int j = 0; j < p->n; j++) {
			cout << p->e[i][j] << " ";
		}
		cout << endl;
	}
}
void bfs(graph* p) {
	int visited[MAXSIZE];
	queue<int> q;
	for (int i = 0; i < p->n; i++) {
		visited[i] = false;
	}
	for (int i = 0; i < p->n; i++) {
		if (!visited[i]) {
			q.push(i);
			visited[i] = true;
			cout << p->v[i];
			while (!q.empty()) {
				int index = q.front();
				q.pop();
				for (int j = 0; j < p->n; j++) {
					if (!visited[j] && p->e[index][j] == 1) {
						q.push(j);
						cout << p->v[j];
						visited[j] = true;
					}
				}
			}
		}
	}
}
void BFS(graph* p) {//广度搜索最短路径
	bool visited[MAXSIZE];
	int d[MAXSIZE];
	int path[MAXSIZE];
	queue<int> q;
	for (int i = 0; i < p->n; i++) {
		visited[i] = false;
		d[i] = MAXSIZE;
		path[i] = -1;
	}
	int u;
	cout << "输入第几个节点开始" << endl;
	cin >> u;
	d[u] = 0;//从第二个节点开始
	visited[u] = true;
	q.push(u);
	while (!q.empty()) {
		cout << "--";
		int index = q.front();
		q.pop();
		for (int i = 0; i < p->n; i++) {
			if (p->e[index][i]!=0&&visited[i] ==false) {
				d[i] = d[index] + 1;
				visited[i] = true;
				q.push(i);
			}
		}
	}
	for (int i = 0; i < p->n; i++) {
		cout << "第" << i << "个顶点与u的距离为" << d[i] << endl;
	}
}
int main() {
	graph p;
	initgraph(&p);
	creategraph(&p);
	printgraph(&p);
	bfs(&p);
}

