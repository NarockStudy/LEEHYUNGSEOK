#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>

using namespace std;

int N, K, L;
int board[101][101];
queue<pair<int, char>> turns;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    for (int i = 0; i < K; ++i) 
    {
        int r, c;
        cin >> r >> c;
        board[r][c] = 1;
    }

    cin >> L;
    for (int i = 0; i < L; ++i) 
    {
        int x;
        char c;
        cin >> x >> c;
        turns.push({x, c});
    }

    // 뱀의 몸통을 저장
    deque<pair<int, int>> snake;

    // 초기 상태 설정
    int time = 0;           // 게임 시간
    int dir = 0;            // 초기 방향은 동쪽 (0:동, 1:남, 2:서, 3:북)
    int head_r = 1, head_c = 1; // 뱀의 머리 위치

    snake.push_front({head_r, head_c}); // 뱀의 초기 위치를 덱에 추가
    board[head_r][head_c] = 2;          // 보드에 뱀의 위치 표시 (뱀은 2)

    // 게임 시작
    while (true) {
        time++;

        // 다음 머리 위치 계산
        int next_r = head_r + dx[dir];
        int next_c = head_c + dy[dir];

        // 벽 또는 자기자신과 부딪히는지 확인

        // 보드 범위를 벗어나거나, 다음 칸이 자기 몸(2)인 경우
        if (next_r < 1 || next_r > N || next_c < 1 || next_c > N || board[next_r][next_c] == 2) {
            break; // 게임 종료
        }

        // 뱀 머리 이동
        head_r = next_r;
        head_c = next_c;
        snake.push_front({head_r, head_c}); // 머리를 다음 칸에 위치시킴

        // 이동한 칸에 사과가 있는지 확인
        if (board[head_r][head_c] == 1) {
            // 사과가 있으면 사과가 없어지고 꼬리는 그대로 둠
            board[head_r][head_c] = 2; // 이제 이 칸은 뱀의 몸통이 됨
        } else {
            // 사과가 없으면 몸길이를 줄여서 꼬리가 위치한 칸을 비워줌
            pair<int, int> tail = snake.back(); // 꼬리 위치
            board[tail.first][tail.second] = 0; // 꼬리가 있던 칸을 빈 칸(0)으로 변경
            snake.pop_back();                   // 덱에서 꼬리 제거
        }

        // 머리가 이동한 후, 보드에 뱀의 위치를 갱신
        board[head_r][head_c] = 2;

        // 현재 시간이 방향 전환 시간인지 확인
        if (!turns.empty() && turns.front().first == time) {
            char turn_dir = turns.front().second;
            turns.pop();

            if (turn_dir == 'D') { // 오른쪽으로 90도 회전
                dir = (dir + 1) % 4;
            } else { // 왼쪽으로 90도 회전
                dir = (dir + 3) % 4; // (dir - 1 + 4) % 4
            }
        }
    }

    cout << time << endl;

    return 0;
}

/*



*/