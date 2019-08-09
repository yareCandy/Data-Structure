//邻接表实现图的存储
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class adjListGraph
{
private:
    struct edge
    {
        int end;
        int weight;
        edge *next;
        edge(int e = 0, int w = 0, edge *n = nullptr)
            :end(e), weight(w), next(n){}
    };

    struct node
    {
        int ver;//顶点值
        edge *head;//对应单链表的头节点

        node(int v = 0, edge *h = nullptr)
        {
            ver = v;
            head = h;
        }
    };

    node *verList;
    int vers, edges;//节点数和边数

    int find(int v)const
    {
        for (int i = 0; i < vers; i++)
            if (verList[i].ver == v) return i;
        return -1;
    }

public:
    adjListGraph(int vSize, const int d[]);//节点数和节点集合
    ~adjListGraph();
    void insert(int x, int y, int w);
    void remove(int x, int y);
    bool exist(int x, int y)const;
    void DFS()const;
    void BFS()const;
    //void dfs()const;//非递归
private:
    void DFS(int start, bool v[])const;
};

adjListGraph::adjListGraph(int vSize, const int d[])
{
    vers = vSize;
    edges = 0;
    verList = new node[vSize];
    for (int i = 0; i < vers; i++)
        verList[i].ver = d[i];
}

adjListGraph::~adjListGraph()
{
    int i;
    edge *p;

    for (i = 0; i < vers; i++)
    {
        while((p = verList[i].head) != nullptr)
        {
            verList[i].head = p ->next; 
            delete p;
        }
    }
    delete [] verList;
}

void adjListGraph::insert(int x, int y, int w)
{
    int u = find(x), v = find(y);
    verList[u].head = new edge(v, w, verList[u].head);
    edges++;
}

void adjListGraph::remove(int x, int y)
{
    int u = find(x), v = find(y);
    edge *p = (edge*)verList[u].head, *q;

    if (p == nullptr) return;

    if (p ->end == v)
    {
        verList[u].head = p ->next;
        delete p;
        edges --;
        return;
    }
    while (p ->next != nullptr && p ->next ->end != v)
        p = p ->next;
    if (p ->next != nullptr)
    {
        q = p ->next;
        p ->next = q ->next;
        delete q;
        edges --;
    }
}

bool adjListGraph::exist(int x, int y)const
{
    int u = find(x), v = find(y);
    edge *p = (edge*)verList[u].head;

    while(p != nullptr && p ->end != v)
        p = p ->next;
    if (p == nullptr) return false;
    else return true;
}

void adjListGraph::DFS()const
{
    bool *visited =  new bool[vers]{0};

    for (int i = 0; i < vers; i++)
    {
        if (visited[i]) continue;
        DFS(i, visited);
        cout << endl;           
    }
}

void adjListGraph::DFS(int i, bool v[])const
{
    edge *p = verList[i].head;
    cout << verList[i].ver << ' ';
    v[i] = true;
    while(p != nullptr)
    {
        if (!v[p ->end]) DFS(p ->end, v);
        p = p ->next;
    }
}


/*
void adjListGraph::dfs()const
{
    edge *p;
    stack<int> stack;
    int tmp;
    bool *visited = new bool [vers];

    for (int i = 0; i < vers; i++)
    {
        if (visited[i]) continue;
        stack.push(i);
        while (!stack.empty())
        {
            tmp = stack.top();
            stack.pop();
            p = verList[tmp].head;
            cout << verList[tmp].ver << ' ';
            visited[tmp] = true;
            
            while (p != nullptr && !visited[p ->end])
            {
                stack.push(p ->end);
                p = p ->next;
            }
        }

    }
}
*/

void adjListGraph::BFS()const
{
    bool *visited = new bool[vers]{0};
    queue<int> que;
    int cur;
    edge *p;

    for (int i = 0; i < vers; i++)
    {
        if (visited[i]) continue;
        que.push(i);
        while (!que.empty())
        {
            cur = que.front(); que.pop();
            if (visited[cur]) continue;
            cout << verList[cur].ver << ' ';
            visited[cur] = true;
            p = verList[cur].head;
            while(p != nullptr)
            {
                if (!visited[p ->end])
                    que.push(p ->end);
                p = p ->next;
            }
        }
        cout << endl;
    }
}