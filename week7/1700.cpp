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

    int n, k;
    cin >> n >> k;

    vector<int> schedule(k);
    for (int i = 0; i < k; ++i) {
        cin >> schedule[i];
    }

    vector<int> multitap; // 현재 멀티탭에 꽂혀있는 전기용품 목록
    int unplug_count = 0;

    for (int i = 0; i < k; ++i) {
        int current_item = schedule[i];
        bool is_plugged = false;

        // 1. 현재 사용하려는 제품이 이미 꽂혀있는지 확인
        for (int plugged_item : multitap) {
            if (plugged_item == current_item) {
                is_plugged = true;
                break;
            }
        }
        if (is_plugged) {
            continue; // 이미 꽂혀있으면 넘어감
        }

        // 2. 멀티탭에 빈 자리가 있는 경우
        if (multitap.size() < n) {
            multitap.push_back(current_item); // 꽂아 그럼
            continue;
        }

        // 3. 멀티탭이 꽉 찬 경우
        // 가장 나중에 사용될 플러그를 찾아서 뽑음
        int item_to_unplug_idx = -1;
        int latest_next_use = -1;

        // 멀티탭에 꽂힌 각 제품에 대해
        for (int j = 0; j < multitap.size(); ++j) {
            int plugged_item = multitap[j];
            int next_use_pos = k + 1; // 앞으로 사용되지 않는 경우를 대비해 큰 값으로 초기화

            // 앞으로의 사용 스케줄에서 언제 다시 사용되는지 찾음
            for (int l = i + 1; l < k; ++l) {
                if (schedule[l] == plugged_item) {
                    next_use_pos = l;
                    break; // 가장 가까운 사용 시점을 찾아서
                }
            }
            
            // 더 나중에 사용되는 제품으로 교체
            if (next_use_pos > latest_next_use) {
                latest_next_use = next_use_pos;
                item_to_unplug_idx = j;
            }
        }

        // 가장 나중에 사용될 제품을 뽑고, 현재 제품을 꽂는다.
        multitap[item_to_unplug_idx] = current_item;
        unplug_count++;
    }

    cout << unplug_count << "\n";


    return 0;
}

/*



*/