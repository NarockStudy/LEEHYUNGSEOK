#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int h, w;
        cin >> h >> w;
        vector<string> board(h + 2);
        board[0] = string(w + 2, '.');
        board[h + 1] = string(w + 2, '.');
        for (int i = 1; i <= h; i++) {
            cin >> board[i];
            board[i] = '.' + board[i] + '.';
        }

        string key_input;
        cin >> key_input;
        int initial_mask = 0;
        if (key_input != "0") {
            for (char c : key_input) {
                initial_mask |= (1 << (c - 'a'));
            }
        }

        // BFS: queue of {x, y, mask}
        // vector<vector<vector<bool>>> visited(h + 2, vector<vector<bool>>(w + 2, vector<bool>(1 << 26, false)));
        // queue<tuple<int, int, int>> q;

        // Optimized: Track max mask per position instead of full 3D visited
        vector<vector<int>> max_mask(h + 2, vector<int>(w + 2, -1));
        vector<vector<bool>> collected(h + 2, vector<bool>(w + 2, false)); // To collect docs only once
        queue<tuple<int, int, int>> q;

        q.push({0, 0, initial_mask});
        // visited[0][0][initial_mask] = true;
        max_mask[0][0] = initial_mask;

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        int docs = 0;

        while (!q.empty()) {
            auto [x, y, mask] = q.front();
            q.pop();

            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (nx < 0 || nx >= h + 2 || ny < 0 || ny >= w + 2) continue;
                //if (visited[nx][ny][mask]) continue;
                char cell = board[nx][ny];
                if (cell == '*') continue; // 벽

                int new_mask = mask;
                if (cell >= 'A' && cell <= 'Z') { // 문
                    int need_key = 1 << (cell - 'A');
                    if ((mask & need_key) == 0) continue; // 열쇠 없음, 스킵
                } else if (cell >= 'a' && cell <= 'z') { // 열쇠
                    mask |= (1 << (cell - 'a'));
                } else if (cell == '$') { // 문서
                    docs++;
                    board[nx][ny] = '.'; // 수집 후 빈 칸으로
                }

                //visited[nx][ny][mask] = true;
                //q.push({nx, ny, mask});
                if (new_mask > max_mask[nx][ny]) {
                    max_mask[nx][ny] = new_mask;
                    q.push({nx, ny, new_mask});
                }
            }
        }

        cout << docs << '\n';
    }
    return 0;
}

/*

딴얘긴데... bits/stdc++.h를 쓰면 헤더를 전부 다 포함하는 거라서

편하다는 이야기를 드디어 들었음

근데 시간과 메모리를 더 잡아먹는다고 함

흠...


이건...

visited로 어쩌고 하는 식의 그것이 가능한가? 보통의 그래프 문제처럼

문에 들어갈 수 있는 경로를 이미 지나갔는데 열쇠를 나중에 얻어버리는?

그런 경우를 어떻게 해야 할 것인가...

그리고 출발을 어디서 해야 한다는 거임

ㅋㅋ

여러 아이디어들을 좀 찾아봄 도저히 감이 안 와서

우선

1. 기존 맵 + 외곽에 '.'으로 둘러싼 맵을 새로 만듦
2. 주운 열쇠에 대한 정보를 관리
3. 문의 위치를 관리 - 열 수 있다면 열고, 열 수 없다면 그 위치를 저장



*/