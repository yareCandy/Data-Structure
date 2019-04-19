//4219.cpp
//求n个元素中前k大的元素的和

#include <iostream>
using namespace std;

struct node
{
    int dt;
    node *next;
    node(int d = 0, node *n = nullptr): dt(d), next(n){}
};
void insert(node *, int);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dt, size, T, k;
    cin >> T;//访问次数
    cin >> size;//元素集合规模
    node *p, *head = new node;

    for (int i = 0; i < size; i++)
    {
        cin >>dt;
        insert(head, dt);
    }
    
    for (int j = 0; j< T; j++)
    {
        int result = 0;
        cin >> k;
        p = head ->next;
        for (int i = 0; i < k; i++)
            result += p ->dt;
        cout << result << '\n';
    }
}

void insert(node *head, int d)
{
    node *p = head;
    while(p ->next != nullptr && p ->next ->dt > d)
        p = p ->next;
    p ->next = new node(d, p ->next);
}