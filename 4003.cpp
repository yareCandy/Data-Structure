//OJ 4003
//你有n个初始装水1L的瓶子。你可以将两个包含同样多水的瓶子合并为一个瓶子，水量为两个瓶子的和。 
//我希望最终剩下k个瓶子，但这可能是无法做到的。 
//但你还可以购进若干个初始装水1L的瓶子，这样就能通过上面的操作达到要求。 
//试问，最少需要购进多少个瓶子。

//-----------------------------
//思路
//-----------------------------
//合并的最小剩余瓶子数刚好等于原有瓶子总数化为二进制后的1个数
//原因是：合并就是当前规模数整除2，同讲数转化位2进制时的不断相除，途中的余数就是剩下的瓶子数
//若所要剩余的瓶子数大于初始瓶子数所能达到的最小瓶子数，肯定不需要额外的瓶子
//但若剩余的小于最少瓶子数时，那就需要添加瓶子，使得添加后的规模数中的1刚好等于所要的剩余数，即得最小添加瓶子数

#include<iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;


//统计x中1的数量
int cnt(long long int x)
{
    int sum=0;
    while(x)
    {
        if(x&1)sum++;
        x>>=1;//右移一位
    }
    return sum;
}

int main()
{
    srand(time(0));

    ofstream file("text.txt");

    long long int n,k,i;
    n = rand();
    k = 1;
    file << n << " " << k << '\n';
    long long int ans=0;
    while(cnt(n)>k)//
    {
        for(i=1;;i<<=1)
            if(i&n)//比较各位
                break;
        ans+=i;
        n += i;
    }
    file << ans << endl;
    file.close();
    return 0;
}


//数组法实现
#include <iostream>
#include <cmath>
using namespace std;

int getNum(int a[], int start, int size)
{
    int result = 0;
    for (int i = start; i < size; i ++)
        if (a[i] != 0)  result++;
    return result;
}

void Getmin()
{
    long long int N, k, i = 0, result = 0;
    cin >> N >> k;

    long long int size = log(N)+3;
    int carry, j = 0, *a = new int [size]{0};
    //将数放入数组
    for (j = 0; N >0; N /= 2, j ++)
        a[j] = N % 2; 

    while(getNum(a, i, j) > k)
    {
        carry = 0;
        for (; i < j; i++)
            if (a[i] != 0)
                break;
        result += pow(2, i);
        a[i++] = 0;
        carry = 1;
        while ((carry + a[i]) == 2){ a[i-1] = 0;carry = 1;i ++;}
        a[i] = 1;
    }

    cout << result << '\n';
    delete [] a;
}
