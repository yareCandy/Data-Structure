
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
typedef struct
{
	int up;
	int down;
}Loct;
Loct s[50005];
int n, step;
long long in[100005];
vector<int> v[50005];
void Sech(int x, int p);
int lowbit(int k)
{
	return k&-k;
}
void Update(int k, int y)
{
	while(k<=2*n)
	{
		in[k] += y;
		k += lowbit(k);
	}
}
long long Query(int k)
{
	long long sum;
	sum = 0;
	while(k>=1)
	{
		sum += in[k];
		k -= lowbit(k);
	}
	return sum;
}
int main(void)
{
	int T, m, i, a, b, t;
    cin >> T;
	while(T--)
	{
		cin >>n >> m;
		step = 0;
		memset(in, 0, sizeof(in));
		for(i=1;i<=n;i++)
			v[i].clear();

		for(i=1;i<=n-1;i++)
		{
			cin >> a >>b;
			v[a].push_back(b), v[b].push_back(a);
		}
		Sech(1, 0);
		for(i=1;i<=m;i++)
		{
			cin >> t;
			if(t==1)
			{
				cin >> a >> b;
				Update(s[a].down, -b);
				Update(s[a].up, b);
			}
			if(t==2)
			{
				cin >> a;
				cout << Query(n*2)-Query(s[a].up-1) << '\n';
			}
		}
	}
	return 0;
}
 
void Sech(int x, int p)
{
	int i, temp;
	s[x].down = ++step;
    int S = v[x].size();
	for(i=0;i < S; i++)
	{
		temp = v[x][i];
		if(temp==p)
			continue;
		Sech(temp, x);
	}
	s[x].up = ++step;
}