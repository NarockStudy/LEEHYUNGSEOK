#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int R, C;
vector<string> lake;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
pair<int,int> swan[2];
queue<pair<int,int>> water, next_water;
queue<pair<int,int>> swanQ, swanNext;
bool visited[1501][1501];

bool in_range(int x, int y) { return x>=0 && x<R && y>=0 && y<C; }

void melt_ice() {
    while (!water.empty()) {
        auto [x,y] = water.front(); water.pop();
        for (int d=0; d<4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (!in_range(nx, ny)) continue;
            if (lake[nx][ny] == 'X') {
                lake[nx][ny] = '.';
                next_water.push({nx, ny});
            }
        }
    }
    water = next_water;
    next_water = queue<pair<int,int>>();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C;
    lake.resize(R);
    swan[0] = {-1,-1}; swan[1] = {-1,-1};
    for (int i=0;i<R;i++) {
        cin >> lake[i];
        for (int j=0;j<C;j++) {
            if (lake[i][j] == 'L') {
                if (swan[0].first == -1) swan[0] = {i,j};
                else swan[1] = {i,j};
            }
            if (lake[i][j] != 'X') water.push({i,j});
        }
    }

    memset(visited, 0, sizeof(visited));
    swanQ.push(swan[0]);
    visited[swan[0].first][swan[0].second] = true;

    int days = 0;
    while (true) {
        // 오늘 백조 이동 시도
        while (!swanQ.empty()) {
            auto [x,y] = swanQ.front(); swanQ.pop();
            for (int d=0; d<4; ++d) {
                int nx = x + dx[d], ny = y + dy[d];
                if (!in_range(nx, ny) || visited[nx][ny]) continue;
                // 백조를 찾음
                if (nx == swan[1].first && ny == swan[1].second) {
                    cout << days << '\n';
                    return 0;
                }
                visited[nx][ny] = true;
                if (lake[nx][ny] == '.') {
                    swanQ.push({nx, ny});
                } else if (lake[nx][ny] == 'X') {
                    // 녹고 나서 이동 가능
                    swanNext.push({nx, ny});
                } else if (lake[nx][ny] == 'L') {
                    // 다른 L은 위에서 처리했지만 일반적으로 처리
                    swanQ.push({nx, ny});
                }
            }
        }

        // 내일 이동할 준비
        swanQ = swanNext;
        swanNext = queue<pair<int,int>>();

        // 한 단계 얼음 녹이기
        melt_ice();
        days++;
    }

    return 0;
}