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

    while(true)
    {
        int n;
        cin >> n;

        if(n == 0)
        {
            break;
        }

        vector<long long int> height(n);
        long long int max_area = 0;

        for(int i = 0; i < n; i++)
        {
            cin >> height[i];
        }

        deque<int> dq;

        for(int i = 0; i <= n; i++)
        {
            long long int current = (i == n) ? 0 : height[i]; // 이걸 추가해야 비워진다...

            while(!dq.empty() && height[dq.back()] > current)
            {
                long long int h = height[dq.back()];
                dq.pop_back();

                long long int width = 0;

                if(dq.empty())
                {
                    width = i;
                }
                else
                {
                    width = i - dq.back() - 1;
                }

                max_area = max(max_area, h * width);
            }

            dq.push_back(i);
        }

        cout << max_area << '\n';

    }

    return 0;
}

/*

그냥 문제 읽기도 전에
바킹독 영상을 잘 좀 볼 걸 싶음
아니라면 다른 사람들의 인사이트나 풀이나... 이런 걸 좀 많이 봤어야 했는데
박치기 공룡 식으로 하니까 그냥 시간을 너무 많이 쓰게 된다
아무튼 또 보면
히스토그램 문제인데 히스토그램에서 가장 넓이가 큰 직사각형을 구하는 프로그램을 만들어라...

ㅅㅂ 어케함

모든 가로 길이는 1이고 높이가 주어진다

일단 첫 번쨰로 직사각형의 개수 n이 주어지고
n개의 정수가 주어진다...
근데 이게 최대 1억이 가능하다는 건 가로가 만약 22라면 int를 넘게 되니까
넓이는 일단 long long int 여야 할 것 같고

이거 굉장히 머리가 아프네...

어쨌든 '제법 큰 수'의 높이를 가진... 그것의 연속을 찾고?
그 연속에 따른 가로 길이(연속되는 인덱스)를...

어떻게 최적화 해야 하지?

일단

n이 주어지고, 같은 줄에 공백으로 직사각형의 높이들이 주어짐.

그리고 나서 새 줄에서 0이 들어오면 프로그램이 종료된다.

입력:

7 2 1 4 5 1 3 3
4 1000 1000 1000 1000
0

출력:

8
4000

인데...

산술 기하 평균으로 접근해야 하나?

생각할 시간을 좀 가져봤는데

이게 deque로 해결할 문제가 맞나?

뭔가 DP 스러운 부분이 좀 있다.

주어진 높이에 따라서 계속해서 넓이를 계산해가면서

최대 넓이를 갱신해가는... 그런 부분이 있는 것 같은데

deque든 stack이든 사실 큰 상관은 없고

갱신을 해 나간다는... 그런 부분에 집중을 해 보자.

흠 이게 아닌가?

이것 또한... 배열 별개... deque 별개... 값이 아니라 인덱스를 저장... 뭐 그런 느낌인가

그래 이게... 결국 인덱스 자체가 가로 길이가 되니까

인덱스를 deque에 저장하는 게 맞을 수 있다

그러면 덩달아 배열에 높이들을 저장하고...

어쨌든... 더 높은 높이가 들어오면 그럴 수 있다

하지만 낮은 높이가 들어오면 그 때부터 인덱스는 초기화하고...

그 모든 과정에서 넓이는 계속 집어넣으면서 최고 기록을 갱신하고...

그니까 가장 back에 있는 인덱스... 이것이 갱신되고

더 높은 높이가 나오더라도 일단 지금을 계산하고 다음 반복에서 이것을 처리하고...

그 때 pop 하면서 조건문 분기하고...

이런 ㅅㅂ... stack이나 deque나 STL을 돌리는 조건에 대해서 디버깅을 좀 해야

이게 등호를 붙이냐 마냐까지도 좀...

*/