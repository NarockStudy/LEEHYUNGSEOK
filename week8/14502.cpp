#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>

using namespace std;

int N, M;
int original_map[8][8];
int temp_map[8][8];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// 바이러스 위치와 빈 칸 위치를 저장할 벡터
vector<pair<int, int>> virus_list;
vector<pair<int, int>> empty_list;

int max_safe_area = 0; // 최대 안전 영역 크기를 저장할 변수

// BFS
void spread_virus() {
    // 임시 맵에 있는 바이러스 위치를 큐에 모두 넣는다.
    queue<pair<int, int>> q;
    for (const auto& v : virus_list) {
        q.push(v);
    }

    // BFS를 통해 바이러스 확산 시뮬레이션
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 맵 범위를 벗어나지 않고, 빈 칸(0)인 경우에만 바이러스 확산
            if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                if (temp_map[nx][ny] == 0) {
                    temp_map[nx][ny] = 2; // 바이러스로 감염
                    q.push({nx, ny});
                }
            }
        }
    }
}

// 안전 영역의 크기를 계산
int calculate_safe_area() {
    int count = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (temp_map[i][j] == 0) {
                count++;
            }
        }
    }
    return count;
}

// 재귀적으로 벽을 3개 세우는 함수 (백트래킹)
// wall_count: 현재까지 세운 벽의 개수
// start_index: 탐색을 시작할 empty_list의 인덱스 (조합을 중복 없이 만들기 위함)
void build_walls(int wall_count, int start_index) {
    // 1. 베이스 케이스: 벽을 3개 모두 세웠을 경우
    if (wall_count == 3) {
        // 원본 맵을 임시 맵으로 복사
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                temp_map[i][j] = original_map[i][j];
            }
        }
        
        // 선택된 3곳에 벽 설치 (temp_map은 이 함수 호출 스택에서만 유효)
        // build_walls 함수가 재귀적으로 호출될 때, original_map은 변하지 않고
        // 이전에 선택되었던 벽의 위치는 백트래킹으로 인해 0으로 복원된 상태.
        // 따라서 현재 선택된 3개의 벽만 설치하면 됨.
        // (이 부분은 재귀 호출 전에 벽을 설치하므로 사실상 없어도 되지만, 명확성을 위해 추가)


        // 2. 바이러스 퍼뜨리기
        spread_virus();
        
        // 3. 안전 영역 계산 및 최댓값 갱신
        max_safe_area = max(max_safe_area, calculate_safe_area());
        
        return;
    }

    // 2. 재귀 호출: 빈 칸에 벽을 세우는 모든 조합 탐색
    for (int i = start_index; i < empty_list.size(); ++i) {
        int x = empty_list[i].first;
        int y = empty_list[i].second;

        // (백트래킹)
        original_map[x][y] = 1; // 1. 벽 세우기
        build_walls(wall_count + 1, i + 1); // 2. 다음 벽 세우러 가기
        original_map[x][y] = 0; // 3. 벽 허물기 (다음 조합을 위해 원래 상태로 복원)
    }
}

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> original_map[i][j];
            if (original_map[i][j] == 0) {
                empty_list.push_back({i, j}); // 빈 칸 위치 저장
            } else if (original_map[i][j] == 2) {
                virus_list.push_back({i, j}); // 바이러스 위치 저장
            }
        }
    }

    build_walls(0, 0);

    cout << max_safe_area << endl;

    return 0;
}

/*



*/