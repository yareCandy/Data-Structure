#include <iostream>
using namespace std;

void quick_sort(int a[], int left, int right)
{
    if (left >= right) return;
    int i = left, j = right;
    int tmp = a[left];
    while(i < j)
    {
        while (i < j && a[j] > tmp) j--;
        if (i < j) a[i++] = a[j];
        while (i < j && a[i] < tmp) i++;
        if (i < j) a[j--] = a[i];
    }
    a[i] = tmp;
    quick_sort(a, left, i-1);
    quick_sort(a, i+1, right);
}

int main()
{
    int N, tmp, result = 0;
    cin >> N;
    int *men = new int [N];
    int *women = new int [N];

    for (int i = 0; i < N; i++)
        cin >> men[i];
    for (int i = 0; i < N; i++)
        cin >> women[i];

    quick_sort(men, 0, N-1);
    quick_sort(women, 0, N-1);

    for(int i = 0; i< N; i++)
    {
        tmp = men[i] - women[i];
        result += (tmp >= 0 ? tmp : (-tmp));
    }

    cout << result << '\n';

    return 0;
}