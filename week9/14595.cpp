#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>
#include <set>

using namespace std;

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // N: 방의 개수 (1 <= N <= 1000000), M: 벽의 개수 (0 <= M <= 100000)
    int N, M;
    cin >> N >> M;
    
    // intervals: 각 벽의 구간 [L, R]을 저장하는 벡터
    vector<pair<int, int>> intervals;
    for(int i = 0; i < M; i++) {
        int L, R;
        cin >> L >> R;
        intervals.push_back({L, R});
    }
    
    // 벽이 하나도 없으면 각 방이 독립적이므로 방 개수 N 출력
    if(M == 0) {
        cout << N << '\n';
        return 0;
    }
    
    // 구간들을 시작점 기준으로 정렬하여 병합을 용이하게 함
    sort(intervals.begin(), intervals.end());
    
    // merged: 겹치는 구간을 병합한 결과 저장
    vector<pair<int, int>> merged;
    // 첫 번째 구간을 current로 설정
    pair<int, int> current = intervals[0];
    
    // 나머지 구간들을 순회하며 병합
    for(int i = 1; i < M; i++) {
        // 현재 구간과 다음 구간이 겹치거나 인접하면 병합
        if(current.second >= intervals[i].first) {
            // 끝점을 최대값으로 업데이트
            current.second = max(current.second, intervals[i].second);
        } else {
            // 겹치지 않으면 현재 구간을 merged에 추가하고 다음 구간으로 이동
            merged.push_back(current);
            current = intervals[i];
        }
    }
    // 마지막 구간 추가
    merged.push_back(current);
    
    // total_covered: 병합된 구간들이 커버하는 총 방 개수 계산
    long long total_covered = 0;
    for(auto& p : merged) {
        total_covered += (long long)p.second - p.first + 1;
    }
    
    // empty_rooms: 커버되지 않은 방 개수 = 전체 방 - 커버된 방
    long long empty_rooms = (long long)N - total_covered;
    
    // components: 최종 컴포넌트 개수 = 병합된 그룹 수 + 빈 방 수
    long long components = merged.size() + empty_rooms;
    
    // 결과 출력
    cout << components << '\n';
    
    return 0;
}