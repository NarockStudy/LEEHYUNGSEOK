#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>

using namespace std;

int N, M;
int r, c, d;

// 0: 청소되지 않은 빈 칸, 1: 벽, 2: 청소된 칸
int room[50][50];

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int cleaned_count = 0;

void simulate() {
    while (true) {
        // 1. 현재 칸이 아직 청소되지 않은 경우, 현재 칸을 청소한다.
        if (room[r][c] == 0) {
            room[r][c] = 2; // 2는 청소 완료를 의미
            cleaned_count++;
        }

        // 주변 4칸을 탐색하기 위한 변수
        bool can_clean_around = false;

        // 현재 방향을 기준으로 왼쪽부터 4방향을 확인
        for (int i = 0; i < 4; i++) {
            // 3. 반시계 방향으로 90도 회전한다.
            // 북(0) -> 서(3), 동(1) -> 북(0), 남(2) -> 동(1), 서(3) -> 남(2)
            d = (d + 3) % 4;
            
            int next_r = r + dr[d];
            int next_c = c + dc[d];

            // 3-a. 바라보는 방향을 기준으로 앞쪽 칸이 청소되지 않은 빈 칸인 경우
            if (next_r >= 0 && next_r < N && next_c >= 0 && next_c < M && room[next_r][next_c] == 0) {
                // 한 칸 전진하고 1번으로 돌아간다.
                r = next_r;
                c = next_c;
                can_clean_around = true;
                break; // 4방향 탐색을 중단하고 다시 while문의 처음으로
            }
        }

        // for문을 모두 돌았는데 can_clean_around가 false이면
        // 주변 4칸 중 청소되지 않은 빈 칸이 없는 경우
        if (!can_clean_around) {
            // 2-a. 바라보는 방향을 유지한 채로 한 칸 후진
            // 현재 방향의 반대 방향으로 이동
            int back_r = r - dr[d];
            int back_c = c - dc[d];

            // 2-b. 뒤쪽 칸이 벽이라 후진할 수 없다면 작동을 멈춘다.
            if (back_r < 0 || back_r >= N || back_c < 0 || back_c >= M || room[back_r][back_c] == 1) {
                break; // 시뮬레이션 종료
            } else {
                // 후진할 수 있다면 한 칸 후진하고 1번으로 돌아간다.
                r = back_r;
                c = back_c;
            }
        }
    }
}

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    cin >> r >> c >> d;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> room[i][j];
        }
    }

    simulate();

    cout << cleaned_count << endl;

    return 0;
}

/*



*/