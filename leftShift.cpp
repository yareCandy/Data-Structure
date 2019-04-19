//leftShift.cpp
//将一个一维数组循环左移p个位置

#include <iostream>
using namespace std;

//辗转相除法寻找最大公约数
int maxCommonPro(int n1, int n2)
{
    int remainder = n1 % n2;
    while (remainder)
    {
        n1 = n2;
        n2 = remainder;
        remainder = n1 % n2;
    }

    return n2;
}

//方法一:设计算法能一次性将元素移动到指定位置
//将Ap移到A0，A2p 移到 Ap。。
//依次循环
template<class T>
void leftShift1(T a[], int size, int p)
{
    int i, j, k, m, d;
    T tmp;
    d = maxCommonPro(size, p);
    int M = size / d;

    for (i = 0; i < d; i++)
    {
        tmp = a[i];
        for (j = i, m = 1; m < M; m++)
        {
            k = (m * p + i) % size;
            a[j] = a[k];
            j = k;
        }
        a[j] = tmp;
    }
}

//方法二：顺序移动p个元素，等同于对数组进行三次逆转
//即：将整个数组逆转，再将前 n-p 个元素逆转， 最后将最后 p 个元素逆转
template<class T>
void invert(T a[], int s, int e)
{
    T w;
    //本函数实现将数组a的s到e之间的元素逆转
    for (int k = s; k < (s+e)/2; k++)
    {
        w = a[k];
        a[k] = a[e-k+s];
        a[e-k+s] = w;
    }
}

template<class T>
void leftShift2(T a[], int size, int p)
{
    //本算法将a的元素循环左移 p 个位置
    invert(a, 0, size-1);
    invert(a, 0, size-p);
    invert(a, size-p, size);
}
