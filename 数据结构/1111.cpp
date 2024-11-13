#include <iostream>
#include<queue>
#include <deque>
using namespace std;
using namespace std;

const int N = 55;

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int T, m, n, cnt, g[N][N];
bool st[N][N];
char c;

// 函数声明
void dfs_0(int x, int y);
void dfs_1(int x, int y);

// 8个方向搜水路
void dfs_0(int x, int y)
{
    st[x][y] = true;
    
    for(int i = -1; i <= 1; i ++)
    {
        for(int j = -1; j <= 1; j ++)
        {
            if(i == 0 && j == 0) continue;
            
            int nx = x + i, ny = y + j;
            if(nx < 0 || nx > m || ny < 0 || ny > n || st[nx][ny]) continue;
            
            if(g[nx][ny] == 0) dfs_0(nx, ny);
            else cnt ++, dfs_1(nx, ny);
        }
    }
}

// 4个方向搜岛屿
void dfs_1(int x, int y)
{
    st[x][y] = true;
    
    for(int k = 0; k < 4; k ++)
    {
        int nx = x + dx[k], ny = y + dy[k];
        if(nx < 0 || nx > m || ny < 0 || ny > n || st[nx][ny] || g[nx][ny] == 0) continue;
        
        dfs_1(nx, ny);
    }
}

int main()
{
    cin >> T;
    while(T --)
    {
        // 初始化
        memset(g, 0, sizeof g);
        memset(st, false, sizeof st);
        cnt = 0;
        
        // 输入
        cin >> m >> n;
        
        for(int i = 1; i <= m; i ++)
        {
            for(int j = 1; j <= n; j ++)
            {
                cin >> c;
                g[i][j] = c - '0';
            }
        }
        
        // 外层包括一圈水路,方便从水路开始搜索
        m ++, n ++;
        
        dfs_0(0, 0);
        
        cout << cnt << endl;
        
    }
    return 0;
}
/*const int maxn = 55;
int dx[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int dy[8] = {0, 1, 0, -1, -1, 1, 1, -1};
char g[maxn][maxn];
bool t[maxn][maxn], st[maxn][maxn];
int n, m, res = 0;

void io() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
}

int judge(int i, int j) {
    queue<pair<int, int>> que;
    que.push({ i, j });
    while (!que.empty()) {
        int x = que.front().first, y = que.front().second;
        que.pop();
        if (st[x][y]) continue;
        st[x][y] = true;
        if (x == 1 || x == n || y == 1 || y == m) {
			return true;
		}
		for (int i = 0; i < 8; i++) {
            int xx = x + dx[i], yy = y + dy[i];
            if (st[xx][yy] || g[xx][yy] == '1') {
				continue;
			}
			que.push({ xx, yy });
        }
    }
    return false;
}

void bfs(int i, int j) {
	queue<pair<int, int>> que;
	que.push({i, j});
	while (!que.empty()) {
		int x = que.front().first, y = que.front().second;
		que.pop();
		if (t[x][y]) {
			continue;
		}
		t[x][y] = true;
		for (int i = 0; i < 4; i++) {
			int xx = x + dx[i], yy = y + dy[i];
			if (t[xx][yy] || xx < 1 || xx > n || yy < 1 || yy > m || g[xx][yy] == '0') {
				continue;
			}
			que.push({xx, yy});
		}
	}
}

void solve() {
	memset(t, 0, sizeof(t));
	res = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> g[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!t[i][j] && g[i][j] == '1') {
				bfs(i, j);
				memset(st, false, sizeof(st));
				if (judge(i, j)) {
					res++;
				}
			}
		}
	}
	cout << res << '\n';
}

int main() {
	io();
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
*/