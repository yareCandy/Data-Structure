//排序算法
#include <iostream>
using namespace std;

//=======================================
// 快速排序
//=======================================
void quick_sort(int a[], int left, int right)
{
    if (left >= right) return;
    int i = left;
    int j = right;
    int init = a[i];
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

//=====================================
// 希尔排序
//=====================================

void shell_sort(int a[], int size)
{
    int gp = size/2;
    int i, j, cur;
    for (; gp >0; gp /=2)
    {
        for (i = gp; i < size; i++)
        {
            cur = a[i];
            j = i;
            while (j >= gp && cur < a[j - gp])
            {
                a[j] = a[j-gp];
                j -= gp;
            }
            a[j] = cur;
        }
    }
}

//====================================
// 归并排序
//====================================
//稳定的 O（OlogN）
void merge(int a[], int size1, int size)
{
    int i = 0, j = size1, k = 0;
    int array[size];

    while (i < size1 && j < size)
    {
        if (a[i] < a[j]) array[k++] = a[i++];
        else array[k++] = a[size1+j++];
    }

    while(i < size1)
        array[k++] = a[i++];

    while(j < size)
        array[k++] = a[j++];

    for (int k = 0; k < size; k++)
        a[k] = array[k];
}

void merge_sort(int a[], int size)
{
    if (size < 2) return;
    int mid = size/2;

    merge_sort(a, mid);
    merge_sort(a+mid, size - mid);

    merge(a, mid, size);
}

//===============================================
// 口袋排序（基数排序）
//===============================================
//设置十个口袋，分别代表0-9，然后依次从小到大往出倒

struct node
{
    int dt;
    node *next;
    node (){next = nullptr;}
    node (int d):dt(d){next= nullptr;}
};

void bucket_sort(node *&p, int d)
{
    node *bucket[10], *last[10], *tail = nullptr;
    int i, j, k, base = 1;

    for (i = 1; i <= d; i ++)
    {
        for (j = 0; j <= 9; j++)
            bucket[j] = last[j] = nullptr;
        while(p != nullptr)
        {
            k = p ->dt / base % 10;
            if (bucket[k] == nullptr)
                bucket[k] = last[k] = p;
            else last[k] = last[k] ->next = p;
            p = p ->next;
        }
        p = nullptr;
        for (j = 0; j <= 9; j++)
        {
            if (bucket[j] == nullptr) continue;
            if (p == nullptr) p = bucket[j];
            else tail ->next = bucket[j];
            tail = last[j];
        }
        tail ->next = nullptr;
        base *= 10;
    }
}

int main()
{
    int d = 0, tmp, maxN = 0;

    node *head = nullptr, *p = head;

    for (int i = 0; i < 12; i ++)
    {
        cin >> tmp;
        if (head == nullptr)
            p = head = new node(tmp);
        else p = p ->next = new node(tmp);

        if (tmp > maxN) maxN = tmp;
    }

    while (maxN > 0)
    {
        maxN /= 10;
        d++;
    }

    bucket_sort(head, d);

    p = head;
    while (p != nullptr)
    {
        cout << p ->dt << " ";
        p = p ->next;
    }
    cout << endl;

    p = head;
    while (p != nullptr)
    {
        p = head ->next;
        delete head;
        head = p;
    }

    return 0;
}


//========================================================================
// 查找
//========================================================================

//----------------------------二分查找------------------------

int bin_search(int a[], int left, int right, int d)
{
    if (left >= right) return -1;
    int mid;
    while (left <= right)
    {
        mid = (left + right) /2;
        if (a[mid] == d) return mid;
        else if (a[mid] > d)
            right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

//========================快速排序的应用====================================
//对一个N个元素的数组，确定是否有两个元素和为指定值，输出全部的可能解

void nLogN(int a[], int size, int k)
{
    quick_sort(a, 0, size-1);

    int j = size -1, i =0;
    while (i < j)
    {
        if (a[i] + a[j] == k)
            cout << a[i++] << " " << a[j--] << '\n';
        else if (a[i] + a[j] < k)
            i++;
        else j--;
    }
}