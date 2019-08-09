//OJ1225
//统计不相同数字的个数

#include <iostream>
using namespace std;

/*
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, num, result = 0;
    cin>>N;

    bool flag[1000000] = {0};

    for (int i = 0; i < N; i++)
    {
        cin >> num;
        flag[num] = 1;
    }

    for (int i = 0; i < 1000000; i++)
        if (flag[i] != 0) result ++;

    cout << result << '\n';

    return 0;
}
*/


void quick_sort(int a[], int left, int right)
{
    if (left >= right) return;
    int i = left, j = right, cur = a[left];

    while(i < j)
    {
        while (i < j && a[j] > cur) j--;
        if ( i < j) a[i++] = a[j];

        while (i < j && a[i] < cur) i++;
        if (i < j) a[j--] = a[i];
    }
    a[i] = cur;
    quick_sort(a, left, i-1);
    quick_sort(a, i+1, right);
}

int main()
{
    int N, cur, result = 0;
    cin >> N;
    int *array = new int [N];

    for (int i = 0; i < N; i ++)
        cin >> array[i];

    quick_sort(array, 0, N-1);
    cur = array[0];
    int i = 0;

    while(i < N)
    {
        result++;
        while (i < N && array[i] == cur) i++;
        if (i == N) break;
        else {cur = array[i];}
    }

    cout << result << '\n';
    delete [] array;
    return 0;
}

