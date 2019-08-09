#include <iostream>
using namespace std;
typedef long long ll;

//取模运算的规则
//a * b mod c = (a mod c) * (b mod c) mod c
//(a + b) mod c = ((a % c) + (b % c) )% c
 
const int MOD = 1E9 + 7;

ll quick_power(int n, int k)
{
    ll ans = 1, base = n;
    while (k)
    {
        if (k & 1)//奇数次幂
            ans = (ans % MOD) * (base % MOD) % MOD;
        base = (base % MOD) *(base % MOD) % MOD;
        k /= 2;
    }

    return ans;
}

void mul(ll a[][2], ll b[][2], ll c[][2])//计算矩阵的幂
{
    ll temp[][2] = {{0, 0}, {0, 0}};
    for (int i = 0; i < 2; i ++ )
        for (int j = 0; j < 2; j ++ )
            for (int k = 0; k < 2; k ++ )
            {
                temp[i][j] = (temp[i][j] % MOD + (a[i][k] % MOD) * (b[k][j] % MOD) % MOD) % MOD;
            }

    for (int i = 0; i < 2; i ++ )
        for (int j = 0; j < 2; j ++ )
            c[i][j] = temp[i][j];
}


ll Fibonacci(ll n)
{
    ll x[2] = {1, 1};
    ll res[2][2] = {{1, 0}, {0, 1}};
    ll t[2][2] = {{1, 1}, {1, 0}};

    ll k = n - 1;

    while (k)
    {
        if (k % 2 != 0) mul(res, t, res);//
        mul(t, t, t);
        k = k / 2;
    }

    int c[2] = {0, 0};
    for (int i = 0; i < 2; i ++ )
        for (int j = 0; j < 2; j ++ )
        {
            c[i] = (c[i] % MOD + (x[j] % MOD) * (res[i][j] % MOD) % MOD) % MOD;
        }

    return c[0];
}


int main()
{
    ll n;

    //cin >> n >> k;
    //cout << quick_power(n, k) << endl;
    
    cin >> n;
    if (n == 0) {cout << 1 << endl; return 0;}
    cout << Fibonacci(n) << endl;
    
    return 0;
}