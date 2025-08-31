#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>

using namespace std;

deque<int> parseArray(const string& arr, int n)
{
    deque<int> result;
    string num;
    for (char c : arr)
    {
        if(isdigit(c))
        {
            num.push_back(c);
        }
        else if(c == ',')
        {
            if(!num.empty())
            {
                result.push_back(stoi(num));
                num.clear();
            }
        }
    }

    if(!num.empty())
    {
        result.push_back(stoi(num));
        num.clear();
    }
    return result;
}

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;

    cin >> T;

    while(T--)
    {
        string p;
        cin >> p;

        int n;
        cin >> n;

        string arr;
        cin >> arr;

        deque<int> array = parseArray(arr, n);

        bool isReversed = false;
        bool error = false;

        for(char cmd : p)
        {
            if(cmd == 'R')
            {
                isReversed = !isReversed;
            }
            else // D 일 때
            {
                if(array.empty())
                {
                    cout << "error" << '\n';
                    error = true;
                    break;
                }
                else
                {
                    if(isReversed)
                    {
                        array.pop_back();
                    }
                    else
                    {
                        array.pop_front();
                    }
                }
            }
        }
        if(!error)
        {
            if(!array.empty())
            {
                if(isReversed)
                {
                    reverse(array.begin(), array.end());
                }
                cout << "[";
                for(int i = 0; i < array.size(); i++)
                {
                    if(i != array.size() - 1)
                    {
                        cout << array[i] << ',';
                    }
                    else
                    {
                        cout << array[i];
                    }
                }
                cout << "]" << '\n';
            }
            else
            {
                cout << "[]" << '\n';
            }
        }
       
    }

    return 0;
}

/*

테스트 케이스의 개수 T가 주어짐. T는 최대 100.

각 테스트 케이스의 첫째 줄에 수행할 함수 p가 주어짐. 

p는 R과 D가 있다. 

R은 배열에 있는 수의 순서를 뒤집는다.
D는 첫 번째 수를 버린다. 배열이 비어있는데 D를 사용한 경우에는 에러가 발생. 'error'

함수는 조합해서 한 번에 사용할 수 있음... RDD는 한 번 뒤집고 처음 두 수를 버린다.

그 다음 줄에는 배열의 크기 n이 주어짐.

그 다음 줄에는 배열에 들어 있는 정수가 주어짐

할 만 한데...?

while(T--) 로 시작해서

string p를 받는데... 이 p가 100000까지 주어진다는 부분이 좀 경악스럽긴 함

그리고 여기서 RDD 등이 있다... 만약 deque를 사용한다고 했을 때 좀 편하지 않나
DRD를 한다고 하면
굳이 카운트를 하고 어쩌고... 를 생각하지 않고
그냥 int flag를 하나 만들어서

front 기준으로 1과 0을 반복하는 것...

DRD가 있다고 하면
D : front에서 1개 삭제
R : flag를 반전
D : flag를 보고 하면 됨 ㅇㅇ;;

int flag로 하지 말자
bool isReversed로 두고

true면 -> D 시에 pop_back을 하고
false면 -> D 시에 pop_front를 하면 된다.

그런데 주어지는 꼬라지를 보아하니

그냥 수를 주는 게 아니라

[1,2,3,4]로 넣어서 주네
이걸 또 파싱해야 한다. 이건 별도의 함수를 만들까?

아무튼
string을 받고, 거기서 string의 size를 체크하고 조건문을 돌리자.
그리고 '[', ',', ']' 를 체크해야 한다.
그리고 그 사이에 두 자리 수의 자연수가 있을 수 있다. string 객체를 하나 만들어서,
push_back을 하고, ','가 나오면 그 string을 int로 만들어서 deque에 넣는다.

오케이...



*/