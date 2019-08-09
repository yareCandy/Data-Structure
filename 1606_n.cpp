#include <iostream>
#include <cstring>
using namespace std;

int n, m;
char map[55][55];
bool mark[55][55];
bool flag = true;
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void isFill(int x, int y)
{
    if (map[x][y] == '.')
    {
        flag = false;
        return;
    }
    mark[x][y] = true;
    for (int k = 0; k < 4; ++k)
    {
        int tmpx = x + dir[k][0];
        int tmpy = y + dir[k][1];
        if (tmpx >= 1 && tmpx <= n && tmpy >= 1 && tmpy <= m && map[tmpx][tmpy] != '#' && !mark[tmpx][tmpy])
            isFill(tmpx, tmpy);
        if (!flag) return;
    }
}

void FillMap(int x, int y)
{
    mark[x][y] = true;
    map[x][y] = '#';
    for (int k = 0; k < 4; ++k)
    {
        int tmpx = x + dir[k][0];
        int tmpy = y + dir[k][1];
        if (tmpx >= 1 && tmpx <= n && tmpy >= 1 && tmpy <= m && map[tmpx][tmpy] == '?' && !mark[tmpx][tmpy])
            FillMap(tmpx, tmpy);
    }
}

void Fill(int x, int y)
{
    mark[x][y] = true;
    for (int k = 0; k < 4; ++k)
    {
        int tmpx = x + dir[k][0];
        int tmpy = y + dir[k][1];
        if (tmpx >= 1 && tmpx <= n && tmpy >= 1 && tmpy <= m && map[tmpx][tmpy] != '#' && !mark[tmpx][tmpy])
            Fill(tmpx, tmpy);
    }
}

bool check()
{
    bool flag = true;
    memset(mark, 0, sizeof(mark));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (map[i][j] == '.')
            {
                Fill(i, j);
                flag = false;
                break;
            }
        }
        if (!flag) break;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (map[i][j] == '.' && !mark[i][j])
                return false;
        }
    }
    return true;
}

void isIso(int i, int j)
{
    flag = true;
    memset(mark, 0, sizeof(mark));
    isFill(i, j);
    if (flag)
    {
        memset(mark, 0, sizeof(mark));
        FillMap(i, j);
    }
}

int main()
{
    bool flag = false;
    int cnt = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> map[i][j];
            if (map[i][j] == '.') flag = true;
            if (map[i][j] == '?') ++cnt;
        }
    }

    if (!flag)//没有陆地，若问好大于一个，肯定时Am
    {
        if (cnt >= 2)
        {
            cout << "Ambiguous" << endl;
            return 0;
        }
        else if (cnt == 0)
        {
            cout << "Impossible" << endl;
            return 0;
        }
        else//只有一个问号
        {
            for (int i = 1; i <= n; ++i)
            {
                for (int j = 1; j <= m; ++j)
                {
                    if (map[i][j] == '?') cout << '.';
                    else cout << map[i][j];
                }
                cout << endl;
            }
            return 0;
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (map[i][j] == '?')
            {
                isIso(i, j);
                if (map[i][j] != '?') continue;

                bool flag1 = false, flag2 = false;
                map[i][j] = '.';
                flag1 = check();
                map[i][j] = '#';
                flag2 = check();

                if (flag1 && flag2)
                {
                    cout << "Ambiguous" << endl;
                    return 0;
                }
                if (!flag1 && !flag2)
                {
                    cout << "Impossible" << endl;
                    return 0;
                }
                map[i][j] = '.';
            }
        }
    }

    bool isImpossible = true;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (map[i][j] == '.')
            {
                isImpossible = false;
                break;
            }
    if (isImpossible)
    {
        cout << "Impossible" << endl;
        return 0;
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            cout << map[i][j];
        cout << endl;
    }

    return 0;
}