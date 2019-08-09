#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
typedef pair<int,int> ii;
const int N=55;
char s[N][N];
int n,m,vis[N][N],mp[N*N],num=0,tot=0;
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};
vector<ii> a;
void dfs(int x,int y)
{
	vis[x][y]=1;
	tot++;
	if(s[x][y]=='?')
		num++;
	for(int i=0;i<4;i++)
	{
		int a=x+dx[i],b=y+dy[i];
		if(a>=1&&a<=n&&b>=1&&b<=m&&(!vis[a][b])&&s[a][b]!='#')
			dfs(a,b);
	}
}
void fun(int x,int y)
{
	vis[x][y]=1;
	s[x][y]='#';
//	cout<<x<<' '<<y<<endl;
	for(int i=0;i<4;i++)
	{
		int a=x+dx[i],b=y+dy[i];
		if(a>=1&&a<=n&&b>=1&&b<=m&&(!vis[a][b])&&s[a][b]=='?')
			fun(a,b);
	}
}
int check()
{
	int cnt=0;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i][j]!='#'&&!vis[i][j])
				dfs(i,j),cnt++;
	return cnt;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++)
			if(s[i][j]=='?')
				a.push_back(ii(i,j));		
	}
	int p=0;
	if(check()>1)
	{
		for(int i=0;i<a.size();i++)
		{
			if(s[a[i].first][a[i].second]=='#')
				continue; 
			num=tot=0;	
			memset(vis,0,sizeof(vis));
			dfs(a[i].first,a[i].second);
			//cout<<i<<' '<<num<<' '<<tot<<endl;
			if(num==tot)
			{
				memset(vis,0,sizeof(vis));
				fun(a[i].first,a[i].second);
			}
		}
		if(check()>1)
		{
			puts("Impossible");
			return 0;
		}
	}
	bool flag=true;
	for(int i=p;i<a.size();i++)
	{
		int x=a[i].first,y=a[i].second;

		if(s[x][y]=='#')	continue;
		s[x][y]='#';
		if(check()==1)
			flag=false;
		s[x][y]='.';
    
	}
	if(!flag)
		puts("Ambiguous");
	else
		for(int i=1;i<=n;i++)
			printf("%s\n",s[i]+1);
		
	return 0;
}