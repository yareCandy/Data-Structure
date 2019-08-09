//现在有一棵树T，有N个节点，我们想通过去掉一个节点p来把T分割成更小的树，并且满足每个小树中的节点数不超过n/2。
//请根据输入的树来输出所有可能的p的号码。
//Input Format
//第1行：一个整数N，代表有N个节点，且每个节点的编号为1,2,...,N。
//第2~N行：每行两个整数x,y，代表节点x和节点y之间连通。
//Output Format
//从小到大一次输出满足条件的p的号码，每行1个可行解。

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

//递归遍历树，同时确定每个节点的父亲节点，及其子节点个数
void traverse(int x)
{
    for (node *p = head[x] ->next; p != nullptr; p = p ->next)
    {
        if (father[p ->label] == 0 && p ->label != 1)
        {
            father[p ->label] = x;
            traverse(p ->label);
            cnt[x] += cnt[p ->label];
        }
    }
    ++cnt[x];
}

int main()
{  
    cin >> n;
    father = new int [n + 1];
    cnt = new int [n + 1]{0};
    head = new node *[n + 1];

    for (int i = 1; i <= n; i++)
        head[i] = new node(0);
    
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        node *tmp;
        tmp = new node(v, head[u] ->next);
        head[u] ->next = tmp;
        tmp = new node(u, head[v] ->next);
        head[v] ->next = tmp;
    }

    //以1为根节点遍历
    traverse(1);

    //时间复杂度时O(n)
    for (int i = 1; i <= n; i++)
    {
        bool check = true;
        for (node *p = head[i] ->next; p != nullptr; p = p ->next)
        {
            if (p ->label == father[i])
            {
                if (cnt[i] < n/2) check = false;
            }
            else
            {
                if (cnt[p ->label] > n/2) check = false;
            }
        }
        if (check) cout << i << endl;
    }
    return 0;
}


