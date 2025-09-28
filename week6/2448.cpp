#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>

using namespace std;

char star[3072][6144];

void draw(int y, int x, int n) {
    if (n == 3) {
        star[y][x] = '*';
        star[y+1][x-1] = '*';
        star[y+1][x+1] = '*';
        for (int i = -2; i <= 2; i++)
            star[y+2][x+i] = '*';
        return;
    }
    int half = n/2;
    draw(y, x, half);
    draw(y+half, x-half, half);
    draw(y+half, x+half, half);
}

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    memset(star, ' ', sizeof(star));
    draw(0, N-1, N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2*N-1; j++)
            cout << star[i][j];
        cout << '\n';
    }

    return 0;
}

/*

일단...

이것도 2447의 구조를 갖고 가면 될 것 같긴 함

*/