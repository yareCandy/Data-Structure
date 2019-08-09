#include <iostream>
using namespace std;


int init[501] = {0};
int people[501];
bool flag[501] = {0};

struct node
{
    int label;
    node *next;
    node(int i, node *n = nullptr){label = i; next = n;}
    node(){next = nullptr;}
};

void quick_sort(int a[], int left, int right)
{
    if (left >= right) return;
    int i = left;
    int j = right;
    int init = a[i];

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

int search(int a[], int left, int right, int d)
{
    if (left >= right) return 0;

    int mid, tmp = right;
    while (left <= right)
    {
        mid = (left + right) /2;
        if (a[mid] == d) break;
        else if (a[mid] > d)
            right = mid - 1;
        else left = mid + 1;
    }
    if (a[mid] == d) return tmp+1;
    else return 0;
}

int main()
{
    int n, M, result = 0, head[501][500];
    int k = 0, m, x, tmp;
    
    cin >> n >> M;//总人数， 组数

    for (int i = 0; i < M; i++)
    {
        cin >> x;
        people[i] = x;//每组的人数
        for (int j = 0; j < x; j++)
        {
            cin >> m;
            head[i][j] = m;
            if (head[i][j] == 0)
                init[k++] = i;
        }
    }

    //分别对每组进行排序
    for(int i = 0; i < M; i++)
        quick_sort(head[i], 0, people[i]-1);

    for(k--; k >= 0; k--)
    {
        for (int i = 0; i < people[init[k]]; i++)
        {
            tmp = 0;
            for (int j = 0; j < M; j++)
            {
                if (flag[j]) continue;
                tmp = search(head[j], 0, people[j]-1, head[init[k]][i]);
                if (!tmp) flag[j] = true;
                result += tmp;
            }
        }
    }

    cout << result << '\n';

    return 0;
}