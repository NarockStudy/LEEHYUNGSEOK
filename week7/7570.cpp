#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>

using namespace std;

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    if (n <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    // 각 번호의 위치를 저장
    vector<int> pos(n + 1); 
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        pos[num] = i;
    }

    int max_len = 1;      // 옮기지 않아도 되는 최대 인원
    int current_len = 1;  // 현재 연속적으로 증가하는 길이

    // 번호가 연속적으로 증가하는 가장 긴 부분 수열 찾기
    for (int i = 1; i < n; ++i) {
        // i번 어린이보다 (i+1)번 어린이가 더 뒤에 있다면 연속된 것
        if (pos[i] < pos[i + 1]) {
            current_len++;
        } else {
            // 연속이 끊겼으므로 현재 길이를 1로 초기화
            current_len = 1;
        }
        max_len = max(max_len, current_len);
    }

    // 전체 어린이 수 - 옮기지 않아도 되는 최대 인원
    int moves = n - max_len;
    cout << moves << "\n";

    return 0;
}

/*



*/