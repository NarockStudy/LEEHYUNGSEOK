#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>

using namespace std;

int N, M, G, R;
vector<vector<int>> board;
vector<pair<int, int>> candidates;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int max_flowers = 0;

// BFS로 배양액 퍼짐 시뮬레이션
int simulate(vector<pair<int, int>>& green, vector<pair<int, int>>& red) {
    vector<vector<int>> dist(N, vector<int>(M, -1));
    vector<vector<int>> state(N, vector<int>(M, 0)); // 0: 빈, 1: 초록, 2: 빨강, 3: 꽃
    queue<pair<int, int>> gq, rq;
    
    // 초록 배양액 초기화
    for (auto& p : green) {
        int x = p.first, y = p.second;
        gq.push({x, y});
        dist[x][y] = 0;
        state[x][y] = 1;
    }
    // 빨강 배양액 초기화
    for (auto& p : red) {
        int x = p.first, y = p.second;
        rq.push({x, y});
        dist[x][y] = 0;
        state[x][y] = 2;
    }
    
    int flowers = 0;
    while (!gq.empty() || !rq.empty()) {
        // 이번 턴에 퍼질 위치들을 임시로 저장
        queue<pair<int, int>> next_gq, next_rq;
        
        // 초록 배양액 퍼짐
        while (!gq.empty()) {
            auto [x, y] = gq.front(); gq.pop();
            if (state[x][y] == 3) continue; // 꽃이면 스킵
            
            for (int d = 0; d < 4; ++d) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < N && ny >= 0 && ny < M && 
                    (board[nx][ny] == 1 || board[nx][ny] == 2) && state[nx][ny] == 0) {
                    state[nx][ny] = 1;
                    dist[nx][ny] = dist[x][y] + 1;
                    next_gq.push({nx, ny});
                }
            }
        }
        
        // 빨강 배양액 퍼짐
        while (!rq.empty()) {
            auto [x, y] = rq.front(); rq.pop();
            if (state[x][y] == 3) continue;
            
            for (int d = 0; d < 4; ++d) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < N && ny >= 0 && ny < M && 
                    (board[nx][ny] == 1 || board[nx][ny] == 2)) {
                    if (state[nx][ny] == 0) {
                        state[nx][ny] = 2;
                        dist[nx][ny] = dist[x][y] + 1;
                        next_rq.push({nx, ny});
                    } else if (state[nx][ny] == 1 && dist[nx][ny] == dist[x][y] + 1) {
                        // 초록과 빨강이 같은 시간에 도달 -> 꽃
                        state[nx][ny] = 3;
                        flowers++;
                        // 꽃이 핀 곳은 더 이상 퍼지지 않으므로 큐에서 제거
                        queue<pair<int, int>> temp;
                        while (!next_gq.empty()) {
                            auto p = next_gq.front(); next_gq.pop();
                            if (!(p.first == nx && p.second == ny)) {
                                temp.push(p);
                            }
                        }
                        next_gq = temp;
                    }
                }
            }
        }
        
        gq = next_gq;
        rq = next_rq;
    }
    return flowers;
}

// G+R개를 선택하는 조합
void select_positions(int idx, int selected_count, vector<int>& selected) {
    if (selected_count == G + R) {
        // 선택된 G+R개 중에서 G개를 초록으로 선택하는 조합
        vector<int> green_indices;
        for (int i = 0; i < G + R; ++i) {
            if (i < G) green_indices.push_back(1);
            else green_indices.push_back(0);
        }
        
        do {
            vector<pair<int, int>> green, red;
            for (int i = 0; i < G + R; ++i) {
                if (green_indices[i] == 1) {
                    green.push_back(candidates[selected[i]]);
                } else {
                    red.push_back(candidates[selected[i]]);
                }
            }
            max_flowers = max(max_flowers, simulate(green, red));
        } while (prev_permutation(green_indices.begin(), green_indices.end()));
        
        return;
    }
    
    for (int i = idx; i < candidates.size(); ++i) {
        selected.push_back(i);
        select_positions(i + 1, selected_count + 1, selected);
        selected.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M >> G >> R;
    board.assign(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> board[i][j];
            if (board[i][j] == 2) candidates.push_back({i, j});
        }
    }
    
    vector<int> selected;
    select_positions(0, 0, selected);
    
    cout << max_flowers << '\n';
    return 0;
}

/*

이번 문제도 2초에 512MB

그런데 이번에는 50x50까지도 커진다

하...

ㄱ-

배양액을 뿌린다고?

배양액을 뿌리면 인접한 곳으로 배양액이 퍼져감

하얀색에는 배양액을 못 뿌림
하늘색... 호수에도 못 뿌림
황토색에는 뿌릴 수 있음

초록색 배양액과 빨간색 배양액이 동일한 시간에 도달하면 그 자리에서는 꽃이 핀다

꽃이 피면 그 자리에서는 배양액이 퍼지거나 하는 일은 없음

와 이게 뭔 ㅋㅋ

출력은 피울 수 있는 꽃의 최대 개수 인데...

이거 또... 빨간색 배양액 또는 초록색 배양액 중 하나가 0인 상황도 고려해야 하고

state가 어떻게 되나...

0 : 배양액 없음
1 : 초록색 배양액
2 : 빨간색 배양액
3 : 꽃
4 : 호수
5 : 뿌릴 수 없는 땅

뭐 이렇게?

이것도 설마 2차원을 1차원으로 펴야 하나?

그렇지는 않을 수도 있다...

그래야 하나?

아오

문제 다시 보니까

0은 호수
1은 뿌릴 수 없는 땅
2는 뿌릴 수 있는 땅

이렇게 되어 있네요...

그러면 state를 다시 

0 : 호수
1 : 뿌릴 수 없는 땅
2 : 뿌릴 수 있는 땅
3 : 초록색 배양액
4 : 빨간색 배양액
5 : 꽃

이렇게 해야 하나?

그럴 필요는 없을 지도...

저 대로 가되...





*/