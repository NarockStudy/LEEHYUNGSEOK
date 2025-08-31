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

    int N;
    cin >> N;

    vector<int> height(N, -1);

    for(int i = 0 ; i < N; i++)
    {
        cin >> height[i];
    }

    stack<pair<int, int>> s;

    long long int answer = 0;

    for(int i = 0; i < N; i++)
    {
        int count_pair = 1;

        while(!s.empty() && s.top().first < height[i])
        {
            answer += s.top().second;
            s.pop();
        }

        if(!s.empty() && s.top().first == height[i])
        {
            count_pair = s.top().second + 1;
            answer += s.top().second;
            s.pop();

            if(!s.empty())
            {
                answer++;
            }
        }
        else if(!s.empty()) // 현재 숫자가 top보다 큰 경우임
        {
            answer++;
        }

        s.push({height[i], count_pair});
    }

    cout << answer << '\n';

    return 0;
}

/*

대충 이 3문제들이
모노톤 스택을 써서 해결하는... 그런 것들인 것은 이제 알겠는데

이제 이게 난이도 순서대로
모노톤 스택으로 오른쪽 놈 보기... 를 2문제 풀었고
이제는 내가 볼 수 있는 양 쪽의 사람 + 서로 볼 수 있는 '쌍의 수' 까지 구해야 한다?

Oh...

예제에서 N : 7
주어진 수열은 H = {2, 4, 1, 2, 2, 5, 1} 임

두 사람 A와 B가 서로 볼 수 있으려면, 두 사람 사이에 A 또는 B보다 키가 큰 사람이 없어야 한다.

H[0], H[1] : 서로 볼 수 있음

H[1], H[2] : 서로 볼 수 있음
H[1], H[3] : 서로 볼 수 있음
H[1], H[4] : 서로 볼 수 있음
H[1], H[5] : 서로 볼 수 있음

H[2], H[3] : 서로 볼 수 있음

H[3], H[4] : 서로 볼 수 없음
H[3], H[5] : 서로 볼 수 있음

H[4], H[5] : 서로 볼 수 있음

H[5], H[6] : 서로 볼 수 있음

음...

출력은 쌍의 수 임... 서로 볼 수 있는

예제 출력에서 10이고, 실제로 센 것도 10이다

이걸 어떻게 구현하냐

H[0] = 2 는 우선 빈 스택에 무조건 넣는다.
다음 인덱스를 본다.
H[1] = 4를 본다. 현재 스택의 top은 2이다.
지금 상태에서 작고 크고를 비교할 일은 아닌 것 같다. H[1]을 push한다

H[0]과 H[1]은 한 쌍으로 기록될 수 있다.

이걸 어떻게 기록할 수 있는가? 만약 answer++; 를 해준다고 가정하고 진행해보자.

H[2] = 1을 본다. 현재 스택의 top은 4이다. H[2]는 4보다 작다. 이 때
뭘 해줘야 하는가...

일단 스택의 top은 수열의 현재 인덱스와 서로 볼 수 있다. top을 따로 int temp에 저장?

어쩌면 자료 구조를 바꿔야 할 것 같다.

크고 작고... 하는 것들에 대해서 비교는 할 수 있어도

저장되는 정보가 부족하다. 뭐가 부족한가?

ㅅㅂ 미치겠네

생각도 해보고 찾아도 봤는데

애초에 이 스택에 단일 int가 아니라 쌍을 넣는 것에 대한 힌트를 얻었다

그니까... 높이에 대한 것과

그 높이를 가진 사람의 수를 가지고

같은 그룹으로 묶는 것이다... 예를 들면 {..., 2, 2, ...}의 형태로 나타나면

이것을 스택에 {2, 2}로 push 하는 것이 아니라

{{2, 2}}로 push 하면서 그 이 2개의 2 다음에 오는 숫자들에 대해서 처리하는 것이다.

그렇게되면...

어쨌든 pop은 계속 이루어지는데?

세 가지 경우로 나눠보자.

1. 같은 숫자임
- 이 경우에는 pop을 하긴 하는데, 이 쌍의 second를 +1 한다. 그리고, 다시 push한다.

2. 현재 숫자가 top보다 작음
- 이 경우에는 top의 pair 즉, 여러 숫자로 이루어진 그룹일 수도 있고 단일 숫자일 수도 있는 것이
현재 숫자를 모두 볼 수 있다. 그러니까 top의 second를 답에 더해준다.

3. 현재 숫자가 top보다 큼
- 이 경우에는 top의 pair가 더 큰 숫자와 쌍을 이루게 된다. 그 이후에는?




*/