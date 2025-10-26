#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

// 서로소 집합(Union-Find) 자료구조: 미리 연결된 통신선을 빠르게 병합/확인
struct DisjointSet {
    vector<int> parent;
    vector<int> rank;

    // 각 정점을 자기 자신이 루트가 되도록 초기화한다.
    explicit DisjointSet(int n) : parent(n + 1), rank(n + 1, 0) {
        for (int i = 0; i <= n; ++i) {
            parent[i] = i;
        }
    }

    // 경로 압축을 이용해 대표 노드를 찾는다.
    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    // 랭크 기반 합치기: 두 정점이 서로 다른 컴포넌트면 병합한다.
    bool merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            ++rank[a];
        }
        return true;
    }
};

struct Edge {
    int u;
    int v;
    double w;
};

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // n: 우주신(정점) 수, m: 이미 연결된 통신선(간선) 수
    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    // 각 우주신의 좌표를 1번부터 저장한다.
    vector<pair<double, double>> coords(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> coords[i].first >> coords[i].second;
    }

    DisjointSet dsu(n);

    // 이미 연결된 우주신 쌍은 미리 병합하여 같은 컴포넌트로 만든다.
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        dsu.merge(a, b);
    }

    vector<Edge> edges;
    edges.reserve(n * (n - 1) / 2);

    // 모든 우주신 쌍 간의 거리(간선 가중치)를 계산해 후보 간선 목록을 만든다.
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            double dx = coords[i].first - coords[j].first;
            double dy = coords[i].second - coords[j].second;
            double dist = sqrt(dx * dx + dy * dy);
            edges.push_back({i, j, dist});
        }
    }

    // 간선을 거리 오름차순으로 정렬하여 크루스칼 MST에 사용할 준비를 한다.
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    double answer = 0.0;

    // 크루스칼 알고리즘: 아직 연결되지 않은 컴포넌트를 잇는 간선만 선택한다.
    for (const auto& edge : edges) {
        if (dsu.merge(edge.u, edge.v)) {
            answer += edge.w;
        }
    }

    // 추가로 필요한 케이블 길이를 소수점 둘째 자리까지 출력한다.
    cout << fixed << setprecision(2) << answer << '\n';

    return 0;
}

/*



*/