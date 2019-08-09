#include <iostream>
using namespace std;
const int MAX = 1000001;
typedef long long ll;

struct node
{
    long long value;
    int times;
    node *next;
    node(long long v, int t = 1, node *n = nullptr)
        :value(v), times(t), next(n){}
    node(): next(nullptr){}
};

void quick_sort(long long a[], int left, int right)
{
    if (left >= right) return;
    int i = left;
    int j = right;
    long long init = a[i];
    //int tmp = left;
    while(i < j)
    {
        while(i < j && a[j] > init) j--;
        if (i < j) a[i++] = a[j];
        while(i < j && a[i] < init) i++;
        if (i < j) a[j--] = a[i];
    }
    a[i] = init;
    quick_sort(a, left, i-1);
    quick_sort(a, i+1, right);
}

int main()
{
    int N ;
    long long tmp, pre = -1;
    cin >> N;
    node **a = new node *[MAX];
    long long value[200002];
    for (int i = 0; i < MAX; i++)
        a[i] = nullptr;
    
    for (int i = 0; i < N; i++)
    {
        cin >> tmp;
        value[i] = tmp;
        if (a[tmp % MAX] == nullptr)
            a[tmp % MAX] = new node(tmp);
        else
        {
            node *p = a[tmp % MAX];
            if (p ->value == tmp)
            {
                p ->times++;
                continue;
            }

            while (p ->next != nullptr && p ->next ->value != tmp)
                p = p ->next;
            if (p ->next != nullptr) p ->next ->times ++;
            else p ->next = new node(tmp);
        }
    }

    quick_sort(value, 0, N-1);

    for (int i = 0; i < N; i++)
    {
        if (pre == value[i]) continue;
        tmp = value[i] % MAX;
        node *p = a[tmp];
        while (p != nullptr && p ->value != value[i])
            p = p ->next;
        cout << value[i] << " " << p ->times << '\n';
        pre = value[i];
    }
    
    return 0;
}