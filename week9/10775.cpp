#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>
#include <set>

using namespace std;

// 각 게이트의 부모를 저장
vector<int> parent;

// x의 루트를 찾고, 경로를 압축하여 최적화
int find(int x) {
    if (parent[x] == x) return x; // x가 루트이면 자신을 반환
    return parent[x] = find(parent[x]); // 재귀적으로 루트를 찾고, 경로 압축
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int G, P; // G: 게이트의 수 (1부터 G까지), P: 비행기의 수
    cin >> G >> P;
    
    parent.resize(G + 1); // 1 ~ G
    for (int i = 1; i <= G; i++) {
        parent[i] = i; // 초기화: 각 게이트 i는 자신을 부모로 설정 (독립된 그룹)
    }
    
    int count = 0; // 도킹된 비행기의 수
    for (int i = 0; i < P; i++) { // P개의 비행기에 대해 반복
        int g; // 현재 비행기가 원하는 게이트 번호
        cin >> g; // 비행기의 게이트 요청 입력
        int root = find(g); // g의 루트를 찾음 (사용 가능한 가장 큰 게이트 번호)
        if (root == 0) break; // 루트가 0이면 더 이상 도킹할 게이트가 없음 (종료)
        parent[root] = root - 1; // 도킹 후, 루트를 root-1로 설정하여 다음 요청 시 더 작은 게이트로 연결
        count++; // 도킹 성공, 카운트 증가
    }
    
    cout << count << endl;
    
    return 0;
}