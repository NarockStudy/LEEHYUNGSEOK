#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>

using namespace std;

vector<string> combinations;

vector<string> board(5); // Y, S로 구성된 5x5 배치도 행렬

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

void select_check(int start, int cnt, vector<int>& sel, int& answer)
{
    // 7명을 모두 선택했을 때의 검증
    if(cnt == 7)
    {
        int s_count = 0;
        bool sel_map[25] = {false};
        for(int idx : sel)
        {
            sel_map[idx] = true;
            if(board[idx / 5][idx % 5] == 'S') ++s_count;
        }
        if(s_count < 4) return; // S가 4개 미만이면 종료


        // BFS로 연결 검사
        vector<vector<bool>> visited(5, vector<bool>(5, false));
        queue<pair<int, int>> q;
        int first_x = sel[0] / 5;
        int first_y = sel[0] % 5;
        q.push({first_x, first_y});
        visited[first_x][first_y] = true;
        int connected_count = 1;

        while(!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            for(int dir = 0; dir < 4; dir++)
            {
                // 상하좌우 (늘 하던 그것)
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if(nx >= 0 && nx < 5 && ny >= 0 && ny < 5 && !visited[nx][ny])
                {
                    // 2차원 -> 1차원
                    int ni = nx * 5 + ny;
                    if(sel_map[ni])
                    {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                        connected_count++;
                    }
                }
            }
        }

        // 7명 모두 연결이 되어있다면

        if(connected_count == 7)
        {
            answer++;
        }
        return;
    }

    // 재귀
    for(int i = start; i <= 25 - (7 - cnt); i++)
    {
        sel.push_back(i); // i번째 학생 선택
        select_check(i + 1, cnt + 1, sel, answer); // 
        sel.pop_back();
    }

}

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int answer = 0;

    for(int i = 0; i < 5; i++)
    {
        string row;
        cin >> row;
        for(int j = 0; j < 5; j++)
        {
            board[i][j] = row[j];
        }
    }

    vector<int> sel;
    select_check(0, 0, sel, answer);

    cout << answer;

    return 0;
}

/*

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	256 MB	19032	10432	6756	52.662%
문제
총 25명의 여학생들로 이루어진 여학생반은 5×5의 정사각형 격자 형태로 자리가 배치되었고, 얼마 지나지 않아 이다솜과 임도연이라는 두 학생이 두각을 나타내며 다른 학생들을 휘어잡기 시작했다. 곧 모든 여학생이 ‘이다솜파’와 ‘임도연파’의 두 파로 갈라지게 되었으며, 얼마 지나지 않아 ‘임도연파’가 세력을 확장시키며 ‘이다솜파’를 위협하기 시작했다.

위기의식을 느낀 ‘이다솜파’의 학생들은 과감히 현재의 체제를 포기하고, ‘소문난 칠공주’를 결성하는 것이 유일한 생존 수단임을 깨달았다. ‘소문난 칠공주’는 다음과 같은 규칙을 만족해야 한다.

이름이 이름인 만큼, 7명의 여학생들로 구성되어야 한다.
강한 결속력을 위해, 7명의 자리는 서로 가로나 세로로 반드시 인접해 있어야 한다.
화합과 번영을 위해, 반드시 ‘이다솜파’의 학생들로만 구성될 필요는 없다.
그러나 생존을 위해, ‘이다솜파’가 반드시 우위를 점해야 한다. 따라서 7명의 학생 중 ‘이다솜파’의 학생이 적어도 4명 이상은 반드시 포함되어 있어야 한다.
여학생반의 자리 배치도가 주어졌을 때, ‘소문난 칠공주’를 결성할 수 있는 모든 경우의 수를 구하는 프로그램을 작성하시오.

입력
'S'(이다‘솜’파의 학생을 나타냄) 또는 'Y'(임도‘연’파의 학생을 나타냄)을 값으로 갖는 5*5 행렬이 공백 없이 첫째 줄부터 다섯 줄에 걸쳐 주어진다.

출력
첫째 줄에 ‘소문난 칠공주’를 결성할 수 있는 모든 경우의 수를 출력한다.

예제 입력 1 
YYYYY
SYSYS
YYYYY
YSYYS
YYYYY
예제 출력 1 
2
힌트
가능한 방법은 아래와 같다.

.....    .....
SYSYS    SYSYS
....Y    .Y...
....S    .S...
.....    .....

이게... 뭐냐

뭔가

실제 사례로 추상화된 느낌이 있어서 조금 구체화 해보면

두 종류의 문자열로 구성된 문자열 행렬이 5x5로 주어진다.

이 행렬에서 연속된 7개의 칸을 선택해야 한다.

이 때 연속이라는 것은 대각선이 아닌 가로/세로로 인접한 것을 의미한다.

그리고 7개의 칸을 선택하면서 문자열 S가 최소 4개 이상 포함되어야만 한다.

입출력 제한 조건을 고려하려고 했는데

무조건 5x5 행렬이 주어진다. 시간제한 2초에 256MB 면

어떻게든 똥꼬쇼를 하면 풀리긴 한다는 얘기다.

그런데 이걸 노션에 백트래킹으로 분류를 해 뒀으니

백트래킹을 한 번 적용해보자. 

사실 백트래킹을 잘 모름

보고 옵시다

사이즈도 작고 할만 할듯

vector<vector<string>> board(5, vector<string>(5, ' '));

이렇게 하면 5x5 행렬에서 접근할 수 있나?

vector<vector<int>> visited(5, vector<int>(5, 0));

여기서 함수 하나를 만들어서

재귀? 반복문 내에서 실행?


아니 실제로 구현하려니까 좀 까다롭네

뭔가 생각을 잘 못 한 것 같음...

백트래킹으로, Y와 S가 섞여 있는 조합들을 모두 먼저 만드는 게 우선일듯?

조건에 맞게 경우의 수들을 모두 모아서 배열에 넣고

이게 실제로 가능한지에 대해서 BFS든 DFS든 해서 확인하는 방향 이게 맞을듯



개삽질해보니 그냥 백트래킹을 갈겨서 4개 이상이 S인... 경우를 모두 만든다 << 이것은 옳지 않을 수 있다.

주어진 보드에서 7개를 고르는데, 거기서 S가 4개 이상이어야 한다.

그러니까... 주어진 보드를 일단 모두 펴 버리고

그니까 2차원 배열을 1차원으로 만들어버리고 거기서 7개를 고르는데 S가 4개 이상인... 백트래킹을 하는 게 맞는 것 같다.

펴서 생각한다 << 여기까지 간다는 게 그냥 호러네 ㅅㅂ





*/