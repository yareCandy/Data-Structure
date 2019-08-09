#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 105;
const int maxsize = maxn * maxn;
int map[maxn][maxn];
int markmap[maxn][maxn];
int m, n;

struct step
{
    int x, y, size;
}queue[4 * maxsize], st, ed;
int front, rear;

bool check(step tmp)
{
    if (tmp.x < 1 || tmp.x > m || tmp.y < 1 || tmp.y > n || map[tmp.x][tmp.y] == 0
         || map[tmp.x][tmp.y] == 2 || markmap[tmp.x][tmp.y] >= tmp.size)
        return false;
    return true;
}

void bfs(int dir[][2])
{
    step now, tmp;
    front = rear = -1;
    queue[++rear] = st;
    while (front < rear)
    {
        now = queue[++front];
        if (now.x == ed.x && now.y == ed.y)
        {
            cout << now.size;
            return;
        }
        for (int i = 0; i < 8; ++i)
        {
            tmp.x = now.x + dir[i][0];
            tmp.y = now.y + dir[i][1];
            tmp.size = now.size + 1;
            if (check(tmp))
            {
                queue[++rear] = tmp;
                markmap[tmp.x][tmp.y] = tmp.size;
            }
        }
    }
}

int main()
{
    for (int i =0; i < maxn; i++)
        for (int j =0; j < maxn; j++)
            markmap[i][j] = -1;

    int m1, m2;
    cin >> m >> n >> m1 >> m2;
    int dir[8][2] = {{m, n}, {-m, n}, {m, -n}, {-m, -n}, {n, m}, {n, -m}, {-n, m}, {-n, -m}};//向下、向上、向右、向左

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
        {
            cin >> map[i][j];
            if (map[i][j] == 3)
            {
                st.x = i;
                st.y = j;
                st.size = 0;
            }
            if (map[i][j] == 4)
            {
                ed.x = i;
                ed.y = j;
            }
        }
    bfs(dir);

    return 0;
}