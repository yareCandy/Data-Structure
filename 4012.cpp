#include <iostream>
#include <queue>
using namespace std;

int main()
{
    priority_queue<int, vector<int>, greater<int> >que;
    int N, j = 0;
    cin >> N;
    int array[20000] = {0};
    int tmp, result = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> tmp;
        que.push(tmp);
    }        
    
    result = que.top(); que.pop();
    while (!que.empty())
    {
        tmp = que.top(); que.pop();
        que.push(tmp + result);
        array[j++] = tmp + result;
        result = que.top();
        que.pop();
    }
    result = 0;
    for (int i = 0; i < N-1; i++)
        result += array[i];
    cout << result << '\n';

    return 0;
}