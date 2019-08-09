//Kruskal算法下的最小生成树
#include <iostream>
using namespace std;


//最小化优先队列
template<class T>
class priorityQueue//使用顺序存储实现的最小化堆
{
private:
    T *dt;
    int maxSize;
    int curSize;

void doubleSpace();
void buildHeap();
void perDown(int i);

public:
    priorityQueue(int initSize = 100);
    priorityQueue(const T a[], int size);
    ~priorityQueue(){delete [] dt;}
    void push(T &d);
    T pop();
    bool empty(){return curSize == 0;}
    int top(){return dt[1];}  
}; // priorityQueue

template<class T>
void priorityQueue<T>::doubleSpace()
{
    T *tmp = dt;
    maxSize *= 2;
    dt = new T[maxSize];
    for (int i = 0; i < curSize; i++)
        dt[i] = tmp [i];
    delete [] tmp;
}

template<class T>
void priorityQueue<T>::buildHeap()
{
    for (int i = curSize/2; i > 0; i--)
        perDown(i);
}

template<class T>
void priorityQueue<T>::perDown(int i)
{
    int child;
    T tmp = dt[i];

    for (; i * 2 <= curSize; i = child)
    {
        child = i * 2;
        if (child != curSize && dt[child] > dt[child+1])
            child++;
        if (dt[child] < tmp) dt[i] = dt[child];
        else break;
    }
    dt[i] = tmp;
}

template<class T>
T priorityQueue<T>::pop()
{
    T tmp = dt[1];
    dt[1] = dt[curSize--];
    perDown(1);
    return tmp;
}

template<class T>
void priorityQueue<T>::push(T &d)
{
    if (curSize == maxSize - 1) doubleSpace();
    int hole = ++curSize;

    for (; hole > 1 && d < dt[hole/2]; hole /= 2)
        dt[hole] = dt[hole/2];
    dt[hole] = d;
}

template<class T>
priorityQueue<T>::priorityQueue(int initSize)
{
    dt = new T [initSize];
    maxSize = initSize;
    curSize = 0;
}

template<class T>
priorityQueue<T>::priorityQueue(const T a[], int size)
{
    dt = new int[size];
    for (int i = 0; i < size; i++)
        dt[i+1] = a[i];
    curSize = size;
    maxSize = size * 2;
    buildHeap();
}

//并查集
template<class T>
class DisjiontSet
{
private:
    int size;
    int *parent;//双亲表示法
public:
    DisjiontSet(int s = 101);
    ~DisjiontSet(){delete [] parent;}
    void unioN(int root1, int root2);
    int find(int x);
};

template<class T>
DisjiontSet<T>::DisjiontSet(int s)
{
    size = s;
    parent = new int [s];
    for (int i = 0; i < size; i++)
        parent[i] = -1;
}

template<class T>
void DisjiontSet<T>::unioN(int root1, int root2)
{
    if (root1 == root2) return;
    
    if(parent[root1] > parent[root2])
    {
        parent[root2] += parent[root1];
        parent[root1] = root2;
    }
    else
    {
        parent[root1] += parent[root2];
        parent[root2] = root1;
    }

    //cout << "parent[" << root1 << "] " << parent[root1] << " parent[" << root2 << "] " << parent[root2] << endl;
}

template<class T>
int DisjiontSet<T>::find(int x)
{
    //cout << "x " << x << " parent[x] " << parent[x] << endl;
    if (parent[x] < 0) return x;
    else return parent[x] = find(parent[x]);
}

struct edge
{
    int end;
    int start;
    int cost;
    edge *next;
    edge(int e = 0, int s = 0, int c = 0, edge *n = nullptr)
        :end(e), start(s), cost(c), next(n){}
    bool operator<(const edge &other){
        return cost < other.cost;}
    bool operator>(const edge &other)
        {return cost > other.cost;}
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


void kruskal();

int vers;//节点数
node verList[28];
int mincost = 0;

int main()
{
    cin >> vers;
    char ch, tmp;
    int num, cost;

    for (int i = 0; i <= vers; i++)
        verList[i].ver = i; 

    for (int j = 0; j < vers-1; j++)//
    {
        cin >> ch;
        cin >> num;
        for (int i = 0; i < num; i++)
        {
            cin >> tmp;
            cin >> cost;
            verList[ch - 'A'].head  = new edge(tmp-'A', ch-'A', cost, verList[ch-'A'].head);
            verList[tmp - 'A'].head  = new edge(ch-'A', tmp-'A', cost, verList[tmp-'A'].head);
        }
    }

    kruskal();

    cout << mincost << '\n';
    return 0;
}

void kruskal()
{
    int edgeAccepted = 0, u, v;
    edge *p;
    edge e;

    DisjiontSet<edge> ds;
    priorityQueue<edge> que;

    //生成优先队列
    for (int i = 0; i < vers; i++)
    {
        for (p = verList[i].head; p != nullptr; p = p ->next)
        {
            if (i < p ->end)
            {
                e.start= i;
                e.end = p ->end;
                e.cost = p ->cost;
                que.push(e);
            }
        }
    }

    //归并
    while (edgeAccepted < vers - 1)
    {
        e = que.pop();
        //cout <<"e " << e.end << ' ' << e.start << ' ' << e.cost << endl;
        u = ds.find(e.start);
        v = ds.find(e.end);
        if (u != v)
        {
            edgeAccepted++;
            ds.unioN(u, v);
            mincost += e.cost;
            //cout << "mincost " << mincost << endl;
        }
    }
}
