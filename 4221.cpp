//第一次机考题

#include <iostream>
#include <stack>
using namespace std;

struct node
{
    int dt;
    int dir;//方向
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    stack<node> st;
    int i, size,result = 0;
    cin >> size;

    node *a = new node[size];
    for (i = 0; i < size; i++)
    {
        cin >> a[i].dt;
        cin >> a[i].dir;
    }

    for (i = 0; i < size; i++)
    {
        if (st.empty() && a[i].dir == 0) {result++;continue;}

        if (a[i].dir == 1) {st.push(a[i]); continue;}

        else //st非空
        {
            while (!st.empty() && st.top().dt < a[i].dt)
            {
                st.pop();
            }
            if (st.empty()) {result++;}
            else
            {
                continue;
            }
        } 
    }

    while (!st.empty()) {st.pop(); result++;}

    cout << result<< '\n';

    return 0;
}