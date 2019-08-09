#include <iostream>
using namespace std;

int N, mincost = 1000000;
int map[17][17]{0};
bool visited[5]{0};

void Dfs(int cost, int start, int num);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> map[i][j];
    Dfs(0, 1, N);
    cout << mincost << '\n';

    return 0;  
}

void Dfs(int cost, int start, int num)
{
    if (num == 0)//回到1号邮局
    {
        if (mincost > cost){
            mincost = cost; return;
        }
    }
    
    visited[start] = true;
    if (num == 1)//只能回去1号邮局
    {
        Dfs(cost+map[start][1], 1, 0);
    }
    else
    {
        for (int i = 1; i <= N; i++){
            if (!visited[i]){
                visited[i] = true;
                Dfs(cost+map[start][i], i, num-1);
                visited[i] = false;
            }
        }
    }       
}