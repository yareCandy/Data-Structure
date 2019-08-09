#include <iostream>
#include <stack>
using namespace std;
const int SHUT = 317847191;

struct node
{
    int dt;
    node *next;
    node(int d, node *n = nullptr):dt(d), next(n){}
    node():next(nullptr){}
};

int main()
{
    int n, m, tmp;
    char op;
    long long int result, remainder = 1;
    stack<int> stack;
    cin >> n >> m;
    node *head = new node();
    node *p, *q, *tail = head;//head ->next 保存着最小值，tail保存着最大值
    
    for (int i = 0; i < n; i++)
    {
        cin >> tmp;
        remainder = (remainder * tmp) % SHUT;
        stack.push(remainder);
        p = head;
        while (p ->next != nullptr && p ->next ->dt < tmp) 
            p = p ->next;
        if (p ->next == nullptr)
            tail = p ->next = new node(tmp);
        else
        {
            p ->next = new node(tmp, p ->next);
        }
    }

    for (int i= 0; i < m; i ++)
    {
        cin >> op;
        switch(op)
        {
            case 'D': cin >> tmp;
                p = head;
                while (p ->next ->dt != tmp) 
                    p = p ->next;
                q = p ->next;
                p ->next = q ->next;
                delete q;
                stack.pop();
                if (p ->next == nullptr) tail = p;
                break;
            case 'B': cout << tail ->dt << '\n';
                    break;
            case 'S': cout << head ->next ->dt << '\n';
                    break;
            case 'M': result = 1;
                    for (int j = 0; j < head ->next ->dt; j++)
                        result = (tail ->dt * result) % SHUT;
                    cout << result << '\n';
                    break;
            case 'T': cout << stack.top() << '\n';
                    break;
            default: break;
        }
    }

    p = head; 
    while (p != nullptr)
    {
        q = p ->next;
        delete p;
        p = q;
    }

    return 0;
}