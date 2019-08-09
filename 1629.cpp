//有一棵节点编号为1~N的树，删除其中任意一个节点都会令树分裂成森林。 
//请你找出这样的节点（我们称之为树的重心），使得该节点被删除后，形成的森林中，节点数最多的树的节点数最少。
//第一行一个整数
//接下来N−1行，每行两个整数u,v，表示两个节点之间存在边。
//输出一行两个整数
//代表树的重心和森林中最大树的节点数。
//如果重心不止一个，输出序号最小的情况

#include <iostream>
using namespace std;

struct node
{
    int label;
    node *next;
    node (int l, node *n = nullptr): label(l), next(n){}
};

int n;
int *father, *cnt;
node **head;

void traverse(int i)
{
    node *p;
    for (p = head[i] ->next; p != nullptr; p = p ->next)
    {
        if (father[p ->label] == 0 && p ->label != 1)
        {
            father[p ->label] = i;
            traverse(p ->label);
            cnt[i] += cnt[p ->label];
        }
    }
    cnt[i] ++;
}

int max(int i, int j, int z = 0)
{
    if (z == 0)
        return (i > j ? i : j);
    else
    {
        int max = (i > j ? i : j);
        max = (max > z ? max : z);
        return max;
    }
}

int main()
{
    int m, k;
    cin >> n;
    head = new node*[n+1];
    father = new int [n+1]{0};
    cnt = new int [n+1]{0};
    for (int i = 0; i <= n; i++)
        head[i] = new node(0);
    
    for (int i = 1; i < n; i++)
    {
        cin >> m >> k;
        head[m] ->next = new node(k, head[m] ->next);
        head[k] ->next = new node(m, head[k] ->next);
    }

    traverse(1);

    node *p;
    int tmpN, tmpI, resultN = 30003, resultI = 0;
    for (int i = 1; i <= n; i++)
    {
        tmpN = 0, tmpI = 30001;
        for (p = head[i] ->next; p != nullptr; p = p ->next)
        {
            if (p ->label == father[i])
            {
                tmpN = (tmpN > (n - cnt[i]) ? tmpN : n - cnt[i]);
                tmpI = i;
            }
            else if (tmpN < cnt[p ->label])
            {
                tmpN = cnt[p ->label];
                tmpI = i;
            }
            else if (tmpN == cnt[p ->label] && p ->label < tmpI)
                tmpI = p ->label;

        }

        if (resultN > tmpN)
        {
            resultN = tmpN;
            resultI = tmpI;
        }
        else if (tmpN == resultN && resultI > tmpI)
            tmpI = p ->label;
    }
    cout << resultI << " " << resultN << '\n';

    return 0;
}