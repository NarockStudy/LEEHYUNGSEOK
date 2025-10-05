#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    // B 배열을 오름차순으로 정렬 -> 이분 탐색 할거임
    sort(b.begin(), b.end());

    int pair_count = 0;
    // A의 각 원소 predator에 대해
    for (int predator : a) {
        // B 배열에서 predator보다 작은 원소의 개수를 찾기
        auto it = lower_bound(b.begin(), b.end(), predator);
        pair_count += (it - b.begin());
    }

    cout << pair_count << "\n";
}


int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

/*



*/