//authorized by LHS
//ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//#define _CRT_SECURE_NO_WARNINGS
// 백준. 15644
#include <bits/stdc++.h>
#define X first
#define Y second
#define Z third
#define INF 987654321
#define ll long long
using namespace std;
int n, m;
int dx[4] = { -1,1,0,0 }; // 북 남 동 서
int dy[4] = { 0,0,1,-1 };
char dir[4] = { 'U','D','R','L' };
int vis[11][11][11][11];
queue<pair<int, int>> red, blue;
string board[11];
int rx, ry, bx, by, flag, cnt;
string di;
queue<string> q;
void move(int& x, int& y, int i) {
	while (1) {
		if (board[x][y] == 'O') break;
		if (board[x][y] == '#') {
			x -= dx[i]; y -= dy[i];
			break;
		}
		x += dx[i]; y += dy[i];
	}

}
int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> board[i];
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 'R') {
				red.push({ i,j });
				rx = i; ry = j;
			}
			else if (board[i][j] == 'B') {
				blue.push({ i,j });
				bx = i; by = j;
			}
		}
	}
	q.push("");
	vis[rx][ry][bx][by] = 1;

	while (!red.empty()) {
		int r_sz = red.size();
		while (r_sz--) {
			auto r = red.front();
			red.pop();
			auto b = blue.front();
			blue.pop();
			di = q.front();
			q.pop();

			if (cnt > 10) break;

			if (board[r.X][r.Y] == 'O') {
				flag = 1; break;
			}

			for (int i = 0; i < 4; i++) {


				int rnx = r.X + dx[i];
				int rny = r.Y + dy[i];
				int bnx = b.X + dx[i];
				int bny = b.Y + dy[i];
				string qd = di;

				move(rnx, rny, i);
				move(bnx, bny, i);

				if (board[bnx][bny] == 'O') {
					continue;
				}

				if (rnx == bnx && rny == bny) {
					switch (i)
					{
					case 0: r.X < b.X ? bnx++ : rnx++; break;
					case 1: r.X < b.X ? rnx-- : bnx--; break;
					case 2:r.Y < b.Y ? rny-- : bny--; break;
					case 3:r.Y < b.Y ? bny++ : rny++; break;
					}
				}

				if (!vis[rnx][rny][bnx][bny]) {
					
					vis[rnx][rny][bnx][bny] = 1;
					red.push({ rnx,rny });
					blue.push({ bnx,bny });
					qd += dir[i];

					q.push(qd);
				}
			}

		}
		if (flag) break;
		else {

			cnt++;
		}
	}
	if (flag) cout << cnt << '\n' << di;
	else cout << -1;

	return 0;
}