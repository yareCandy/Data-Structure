#include <iostream>
using namespace std;

struct edge
{
    int end, dis, cost;
    edge *next;
    edge(int e = 0, int d = 0, int c = 0, edge *n = nullptr)
        :end(e), dis(d), cost(c), next(n){}
};

struct node
{
    int label;
    edge *head;
    node(int v = 0, edge *h = nullptr)
    {
        label = v;
        head = h;
    }
};

int vers, Start, End;//节点数
node *verList;
int mindis = 100000, mincost = 100000;
bool visited[1002]{0};

void DFS(int i, int cost, int dis, bool v[]);

int main()
{
    int M, st, ed, dis, cost;
    cin >> vers >> M;
    verList = new node[vers+1];

    for (int i = 1; i <= vers; i++)
        verList[i].label = i; 

    for (int i = 0; i < M; i++)
    {
        cin >> st >> ed >> dis >> cost;
        verList[st].head  = new edge(ed, dis, cost, verList[st].head);
    }

    cin >> Start >> End;

    DFS(Start, 0, 0, visited);
    cout << mindis << ' ' << mincost << '\n';

    return 0;
}

void DFS(int i, int cost, int dis, bool v[])
{
    if (i == End)//已经到了终点
    {
        if (mindis > dis){
            mindis = dis; 
            mincost = cost;
        }
        else if(mindis == dis)
            mincost = (mincost > cost ? cost : mincost);
        
        return;
    }
    
    //尚未到终点时
    v[i] = true;
    edge *p = verList[i].head;
    while(p != nullptr)
    {
        if (!v[p ->end]){
            v[p ->end] = true;
            DFS(p ->end, cost+p->cost, dis+p->dis, v);
            v[p ->end] = false;
        }
        p = p ->next;
    }
}