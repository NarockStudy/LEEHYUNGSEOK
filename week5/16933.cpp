#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M, K;
    // N: 행, M: 열, K: 벽을 부술 수 있는 최대 횟수
    if (!(cin >> N >> M >> K)) return 0;
    vector<string> a(N); // 지도 정보 (문자열로 입력받음)
    for (int i = 0; i < N; ++i) cin >> a[i];

    // visited[breaks][r][c][parity]
    // breaks: 지금까지 부순 벽의 개수
    // r, c: 현재 위치
    // parity: 낮/밤 (1=낮, 0=밤)
    vector<vector<vector<array<char,2>>>> visited(
        K+1,
        vector<vector<array<char,2>>>(N, vector<array<char,2>>(M, {0,0}))
    );

    // BFS를 위한 큐: (행, 열, 부순 벽 개수, 현재 시간)
    queue<tuple<int,int,int,int>> q; // r, c, broken, time
    q.emplace(0,0,0,1); // 시작점 (0,0), 벽 0개 부숨, 시간 1(낮)
    visited[0][0][0][1] = 1; // 시작점 방문 표시

    int dr[4] = {-1,1,0,0}, dc[4] = {0,0,-1,1}; // 상하좌우 방향 벡터
    while (!q.empty()) {
        auto [r,c,br,time] = q.front(); q.pop();
        // 목적지에 도달하면 시간 출력 후 종료
        if (r == N-1 && c == M-1) {
            cout << time << '\n';
            return 0;
        }
        int nextParity = (time+1) % 2; // 다음 시간의 낮/밤 판별

        // 4방향 이동 시도
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            // 범위 밖이면 무시
            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
            if (a[nr][nc] == '0') { // 빈 칸이면
                // 아직 방문하지 않았다면 이동
                if (!visited[br][nr][nc][nextParity]) {
                    visited[br][nr][nc][nextParity] = 1;
                    q.emplace(nr, nc, br, time+1);
                }
            } else { // 벽이면
                if (br < K) { // 벽을 더 부술 수 있다면
                    if (time % 2 == 1) { // 낮일 때만 벽을 부술 수 있음
                        if (!visited[br+1][nr][nc][nextParity]) {
                            visited[br+1][nr][nc][nextParity] = 1;
                            q.emplace(nr, nc, br+1, time+1); // 벽 부수고 이동
                        }
                    }
                    // 밤에는 벽을 부술 수 없으므로 대기 필요
                }
            }
        }
        // 현재 위치에서 대기(시간만 증가, 낮/밤 전환)
        // 벽을 부수지 않고, 이동하지 않고, 낮/밤만 바뀜
        if (!visited[br][r][c][nextParity]) {
            visited[br][r][c][nextParity] = 1;
            q.emplace(r, c, br, time+1);
        }
    }

    // 목적지에 도달할 수 없으면 -1 출력
    cout << -1 << '\n';
    return 0;
}

/*

벽을 부술 수 있는데...

낮에만 벽을 부술 수 있고

벽을 몇 개까지 부술 수 있는지가 주어진다

*/