#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>
#include <set>

using namespace std; 

struct Point {
    long long x, y;
};

struct Line {
    Point p1, p2;
};

// ccw 함수: Counter-Clockwise 알고리즘.
// 세 점 a, b, c에 대해, b에서 a로의 벡터와 b에서 c로의 벡터의 외적을 계산하여 방향을 판정.
// 반환값: 1 (반시계 방향), -1 (시계 방향), 0 (일직선상).
// 외적 계산: (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)
// 양수면 반시계, 음수면 시계, 0이면 일직선.
int ccw(Point a, Point b, Point c) {
    long long val = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}

// intersect 함수: 두 선분 l1과 l2가 교차하는지 판정.
// 교차 조건: 선분이 실제로 교차하거나 끝점이 겹치는 경우 포함.
// CCW를 사용하여 방향을 확인.
// ab = ccw(a,b,c) * ccw(a,b,d): 점 c와 d가 선분 ab의 양쪽에 있는지.
// cd = ccw(c,d,a) * ccw(c,d,b): 점 a와 b가 선분 cd의 양쪽에 있는지.
// 일반 교차: ab <= 0 && cd <= 0
// 일직선상(collinear)인 경우: 겹치는지 확인 (x와 y 범위 모두 겹침).
bool intersect(Line l1, Line l2) {
    Point a = l1.p1, b = l1.p2, c = l2.p1, d = l2.p2;
    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);
    if (ab == 0 && cd == 0) {
        // 두 선분이 일직선상에 있음. 겹치는지 확인.
        // x축과 y축 모두에서 범위가 겹치는지 체크.
        if (min(a.x, b.x) <= max(c.x, d.x) && max(a.x, b.x) >= min(c.x, d.x) &&
            min(a.y, b.y) <= max(c.y, d.y) && max(a.y, b.y) >= min(c.y, d.y)) return true;
    }
    // 일반적인 교차 판정: 각 선분의 끝점들이 상대 선분의 양쪽에 있음.
    return ab <= 0 && cd <= 0;
}

// Union-Find 자료구조의 부모 배열.
// parent[i]는 i의 부모 노드를 가리킴. 초기에는 자기 자신.
vector<int> parent;

// find 함수: 경로 압축을 사용한 재귀적 찾기.
// x의 루트 노드를 찾아 반환. 동시에 경로 압축으로 부모를 루트로 설정하여 효율성 향상.
int find(int x) {
    return x == parent[x] ? x : parent[x] = find(parent[x]);
}

// unite 함수: 두 집합을 합침.
// x의 루트를 y의 루트의 부모로 설정.
void unite(int x, int y) {
    parent[find(x)] = find(y);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;  // 선분의 개수
    cin >> N;

    vector<Line> lines(N);
    for (int i = 0; i < N; i++) {
        cin >> lines[i].p1.x >> lines[i].p1.y >> lines[i].p2.x >> lines[i].p2.y;
    }

    // Union-Find 초기화: 각 선분의 부모를 자기 자신으로 설정.
    parent.resize(N);
    for (int i = 0; i < N; i++) parent[i] = i;

    // 모든 선분 쌍에 대해 교차 여부 확인.
    // N <= 3000이라 O(n^2)도 가능할듯
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (intersect(lines[i], lines[j])) {
                // 교차하면 같은 그룹으로 합침.
                unite(i, j);
            }
        }
    }

    // 그룹 수와 최대 그룹 크기를 계산
    set<int> groups;  // 그룹의 루트 노드들을 저장(중복 제거 -> 그룹 수 계산)
    vector<int> groupSize(N, 0);  // 각 그룹의 크기를 저장 (인덱스는 루트 노드)
    for (int i = 0; i < N; i++) {
        int p = find(i);  // i의 루트 찾기
        groups.insert(p);  // 그룹 집합에 추가
        groupSize[p]++;   // 해당 그룹 크기 증가
    }

    // 최대 그룹 크기 찾기
    int maxSize = 0;
    for (int s : groupSize) maxSize = max(maxSize, s);

    // 출력: 첫 줄 그룹 수, 둘째 줄 최대 그룹 크기.
    cout << groups.size() << endl;
    cout << maxSize << endl;

    return 0;
}