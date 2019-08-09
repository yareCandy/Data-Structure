#include <iostream>
#include <stack>
using namespace std;

int main()
{
    stack<int> stack;
    long long int sum = 0;
    int N, tmp, result = 0;
    cin >> N;
    int *array = new int [N];

    for (int i = 0; i < N; i++)
    {
        cin >> array[i];
        sum += array[i];
    }

    int averge = sum / N;

    for (int i = 0; i < N; i++)
    {
        tmp = array[i] - averge;
        if (stack.empty() || (!stack.empty() && (tmp * stack.top()) >= 0))
        {    if (tmp != 0) stack.push(tmp);}
        else if (!stack.empty())
        {
            while (!stack.empty() && (tmp * stack.top()) < 0)
            {
                tmp += stack.top();
                stack.pop();
                result++;
            }
            if (tmp != 0) stack.push(tmp);
        }
        if (!stack.empty()) cout << stack.top() << " " << tmp << endl;

    }

    cout << result << '\n';

    return 0;
}