#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<queue>
#include<iostream>
#include<stack>
using namespace std;
/*

bool comp(const Edge& a, const Edge& b) {
	return a.weight < b.weight;
}

*/
int n = 6;
vector<int> fa(n, 0);
bool compare(const vector<int>& a, const vector<int>& b) {
	return a[2] < b[2];
}

int find(int i) {
	if (fa[i] == i) {
		return i;
	}
	else {
		fa[i] = find(fa[i]);
		return fa[i];
	}
}
void unionfunc(int i, int j) {
	int i_fa = find(i);
	int j_fa = find(j);
	fa[i_fa] = j_fa;
}
vector<vector<int>> Kruskal(vector<vector<int>> nums) {
	vector<vector<int>> result;//存取最小树的边
	
	for (int i = 0; i < n; i++) {
		fa[i] = i;
	}
	sort(nums.begin(), nums.end(), compare);
	for (vector<int>& num : nums) {
		if (find(num[0]) != find(num[1])) {
			unionfunc(num[0], num[1]);
			result.push_back({ num[0],num[1],num[2] });
		}
	}
	return result;
}
int main() {
	vector<vector<int>> nums = {
		{0,3,1},{0,2,5},{2,3,4},{2,5,2},{3,5,4},{0,1,6},{1,4,3},{1,3,5}
		
	};
	vector<vector<int>> result = Kruskal(nums);
	for (int i = 0; i < result.size(); i++) {
		cout << result[i][0] << " " << result[i][1] << " " << result[i][2] << endl;
	}
}
int gcd(int num1,int num2){
	if(num2==0){
		return num1;
	}
	return gcd(num2,num1%num2);
}
int lcm(int a,int b){
	return a*b/gcd(a,b);
}