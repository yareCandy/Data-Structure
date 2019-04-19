//fullArray.cpp
//用递归和非递归实现输出n个数的全排列

#include <iostream>
using namespace std;

//递归法实现全排列
//思想：要打印n个数的全排列，只需要打印n -1 个数的全排列
//      再将第n个数插入n - 1 的各空

void print (int a[], int start, int n);

void package(int n)
{
    int *a = new int [n];
    for (int i = 1; i <= n; i++)
        a[i - 1] = i;
    print(a, 0, n);
}

void swap(int &n1, int &n2)
{
    int tmp = n1;
    n1 = n2;
    n2 = tmp;
}

void print(int a[], int cur_size, int tot_size)//第一个表示当前打印到第几个，tot_size表示总n
{
    if (cur_size == tot_size)//到最后一个数字了
    {
        for (int i = 0; i < tot_size; i++)
            cout << a[i] << ' ';
        cout << endl;
        return;
    }

    for (int i = cur_size; i < tot_size; i++)//交换k与k后每一位上的数字
    {
        swap(a[cur_size], a[i]);
        print(a, 1+cur_size, tot_size);//不能使用 cur_size++，否则出现下标越界
        swap(a[cur_size], a[i]);
    }

}


int main()
{
    int n;

    cout << "Input the n: " << endl;
    cin >> n;
    package(n);

    return 0;
}


