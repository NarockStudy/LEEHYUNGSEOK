#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

vector<vector<char>> star;

void draw(int x, int y, int n)
{
    if (n == 1) {
        star[x][y] = '*';
        return;
    }
    int div = n / 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) continue; // 가운데는 공백
            draw(x + i * div, y + j * div, div);
        }
    }
}

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    star.assign(N, vector<char>(N, ' '));
    draw(0, 0, N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << star[i][j];
        }
        cout << '\n';
    }
    return 0;
}

/*

N은 3의 거듭제곱의 형태로 주어짐

기본 단위를 먼저 함수화 하고 이걸 재귀로 찍어내는 게 맞나? 싶은데

N = 3일때는 5

N = 9일때도 5



*/