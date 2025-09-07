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

    vector<int> dp(N + 2, 0);
    vector<int> T(N + 1, 0);
    vector<int> P(N + 1, 0);

    for(int i = 1; i <= N; i++)
    {
        cin >> T[i] >> P[i];
    }

    for(int i = N; i >= 1; i--)
    {
        if(i + T[i] - 1 <= N)
        {
            dp[i] = max(dp[i + 1], dp[i + T[i]] + P[i]);
        }
        else
        {
            dp[i] = dp[i + 1];
        }
    }

    int ans = 0;
    for(int i = 1; i <= N; i++)
    {
        ans = max(ans, dp[i]);
    }

    cout << ans << '\n';

    return 0;
}

/*

1 <= N <= 1500000...

실행 시간 2초.

1500000^2 = 2,250,000,000,000 이니까

O(N log N)의 복잡도로 쇼부 봐야 함...

대충 시나리오를 짜 보자...

첫째 줄에 N이 주어지고

N개의 줄에 T_i와 P_i가 주어진다.

이것을 어떻게 저장?

vector<pair<int, int>> 로 저장한다고 치자.

그렇게 해서 저장된 걸 0부터 N-1 까지 순회하는데

이걸 대충 max()로 쇼부볼 수 있는 일인가?

그러니까,

dp[] 를 어떻게 정의할 것임?

dp[i] : i일까지 얻을 수 있는 최대 수익

으로 정의하면 맞지 않을까?

생각해보면 vector<pair<int, int>> 로 하는 건 좀 생쇼일 수 있고

애초에 주어진 term인 T_i, P_i를 각각 만들어서 저장하는 게 맞는 것 같다.

점화식을 어떻게 세울 지가 고민이 되는 부분임

예를 들어서 dp[0] = 0이고

dp[1] = ?

1일차에 얻을 수 있는 최대수익은 어떻게 계산해야 하는 것임?

이 상담이 완료되는 날에 수익을 얻는다는 것임?

예시를 통해서 알아보자... 아니 알아볼 수가 있나?

이건 어쩌면 'N일' 에서부터 시작해야 하는 문제인 건가?

그러니까, bottom-up이 아니라, top-down으로 접근해야 하는?

i = n 부터 시작해서, 1씩 감소하면서 순회

dp[i] = max(dp[i + T[i]] + P[i], dp[i + 1])

이런 식으로?

이 때 조건이 있어야 할 텐데

여기서 T[i]와 P[i]를 어떻게 고려해야 하는가...?

dp 배열을 0으로 초기화하면 이러한 순회에서의 문제가 없어지는 건가?

아마 그럴 것 같긴 함

1 <= T <= 50 으로 주어져 있는 상황에서

N + 1일 째에는 퇴사를 한다고 주어져 있으므로 이것에 대해서는 마지막 날 i = n일 때에

T_i가 1이어야만 상담할 수 있는?

이것은... 그냥 조건문의 분기 자체를 잘 설정을 해야 할 것 같은데

if(i + T[i] - 1 <= n)

에 대해서 검사를? 하고?

else에서는 저게 불가능하면 그냥 이전 dp값을 계승하는 식으로 하면

그게 dp[i] = dp[i + 1]에 대한 것으로...

표현되면 그게 되는? 것 같은데

물론 이 dp배열에서... 순차적으로 증가하는 건 아니니까

한 번 더 순회하면서 최대값을 찾아야 하는?

흠...

일단 한 번 구현해볼까요



*/