#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>

using namespace std;

int N;

int black_max = 0;
int white_max = 0;

void select_check(int row, int col, int count, string color, 
                    const vector<vector<int>>& board, 
                    vector<bool>& left_diag, vector<bool>& right_diag)
{
    if(col >= N)
    {
        row++;
        if(color == "black")
        {
            col = (row % 2 == 0) ? 0 : 1;
        }
        else
        {
            col = (row % 2 == 0) ? 1 : 0;
        }
    }

    if(row >= N)
    {
        if(color == "black")
        {
            black_max = max(black_max, count);
        }
        else
        {
            white_max = max(white_max, count);
        }
        return;
    }

    if(board[row][col] == 1 && !left_diag[col - row + N - 1] && !right_diag[row + col])
    {
        left_diag[col - row + N - 1] = true;
        right_diag[row + col] = true;
        select_check(row, col + 2, count + 1, color, board, left_diag, right_diag);
        left_diag[col - row + N - 1] = false;
        right_diag[row + col] = false;
    }

    select_check(row, col + 2, count, color, board, left_diag, right_diag);
}

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    vector<vector<int>> board(N, vector<int>(N, 0)); // 비숍을 놓을 수 있는지를 저장하는 행렬

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> board[i][j];
        }
    }

    int size = 2 * N - 1;
    vector<bool> diag_left(size, false);
    vector<bool> diag_right(size, false);

    select_check(0, 0, 0, "black", board, diag_left, diag_right);
    select_check(0, 1, 0, "white", board, diag_left, diag_right);

    cout << black_max + white_max;

    return 0;
}

/*

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
10 초	128 MB	35033	9122	6364	25.088%
문제
서양 장기인 체스에는 대각선 방향으로 움직일 수 있는 비숍(bishop)이 있다. < 그림 1 >과 같은 정사각형 체스판 위에 B라고 표시된 곳에 비숍이 있을 때 비숍은 대각선 방향으로 움직여 O로 표시된 칸에 있는 다른 말을 잡을 수 있다.



< 그림 1 >

그런데 체스판 위에는 비숍이 놓일 수 없는 곳이 있다. < 그림 2 >에서 체스판에 색칠된 부분은 비숍이 놓일 수 없다고 하자. 이와 같은 체스판에 서로가 서로를 잡을 수 없도록 하면서 비숍을 놓는다면 < 그림 3 >과 같이 최대 7개의 비숍을 놓을 수 있다. 색칠된 부분에는 비숍이 놓일 수 없지만 지나갈 수는 있다.



< 그림 2 >



< 그림 3 >

정사각형 체스판의 한 변에 놓인 칸의 개수를 체스판의 크기라고 한다. 체스판의 크기와 체스판 각 칸에 비숍을 놓을 수 있는지 없는지에 대한 정보가 주어질 때, 서로가 서로를 잡을 수 없는 위치에 놓을 수 있는 비숍의 최대 개수를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 체스판의 크기가 주어진다. 체스판의 크기는 10이하의 자연수이다. 둘째 줄부터 아래의 예와 같이 체스판의 각 칸에 비숍을 놓을 수 있는지 없는지에 대한 정보가 체스판 한 줄 단위로 한 줄씩 주어진다. 비숍을 놓을 수 있는 곳에는 1, 비숍을 놓을 수 없는 곳에는 0이 빈칸을 사이에 두고 주어진다.

출력
첫째 줄에 주어진 체스판 위에 놓을 수 있는 비숍의 최대 개수를 출력한다.

예제 입력 1 
5
1 1 0 1 1
0 1 0 0 0
1 0 1 0 1
1 0 0 0 0
1 0 1 1 1
예제 출력 1 
7

첫째 줄에서 N이 하나 주어지고

그 다음 N개의 줄에 N개의 숫자가 주어지면서 NxN 체스판이 주어짐...

이것도 2차원을 1차원으로 펴서 풀어야 하나?

하...

일단 비숍... 대각선만 고려한다는 것이

무슨 일이 있어도 인접한 인덱스와는 상관이 없다는 것에 대한 생각을 함...

이 NxN에서

짝수 인덱스 홀수 인덱스를 나누고... 2차원 배열을 1차원으로 펴서 보고...

하면 되는 것일지?

아마 맞을 것 같은데...

그리고 이것도 백트래킹에서

모든 경우의 수를 고려... 그것에서 반드시 하나만의 정답이 나오는가? 하면 그것은 ㅇㅋ지만

그걸 구하는 과정에서 여러 경우의 수를 탐색해야 하는... 그것이니까

짝수 홀수를 나눈다? 이게

흑 백을 나눈다는 개념을 생각한 건데

실제로 0 2 4 다음 줄은 1 3이 되니까
짝수 홀수가 번갈아가면서 나오는 것에 대한 고려도 해 줘야 할 것 같음

하~~

대각 에서 우측의 상/하, 좌측의 상/하 도 고려를 해야 하네 이런

*/