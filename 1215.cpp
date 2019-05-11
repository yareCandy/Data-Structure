//二项堆
//实现一棵Bernoulli树。实现下列操作：
//1.insert X，将整数X加入优先队列
//2.delete，将优先队列中最小值弹出
//3.min，输出最小值
//初始优先队列为空。
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

//孩子兄弟树
template<class elem>
struct node
{
    elem dt;
    node *son;
    node *bro;
    node (const elem &d, node *s = nullptr, node *b = nullptr)
        :dt(d), son(s), bro(b){}
    node() : son (nullptr), bro(nullptr){}
};

template<class elem>
class bernoulliTree
{
private:
    node<elem> **forest;//存放森林
    int size;

public:
    bernoulliTree(int initSize = 10);
    ~bernoulliTree();
    void push(const elem &d);
    elem pop();
    bool empty();
    elem top();    
    void merge(const bernoulliTree &other);

private:
    int findmin();
    void deleteTree(node<elem> *rt);
    node<elem> *merge(node<elem> *t1, node<elem> *t2);
};

template<class elem>
bernoulliTree<elem>::bernoulliTree(int initSize)
{
    size = int (log(initSize)/log(2)) + 1;
    forest = new node<elem> *[size];

    for (int i = 0; i < size; i++)
        forest[i] = nullptr;    
}

template<class elem>
bernoulliTree<elem>::~bernoulliTree()
{
    for (int i = 0; i < size; i++)
        if (forest[i] != nullptr) deleteTree(forest[i]);
    delete forest;
}

template<class elem>
void bernoulliTree<elem>::merge(const bernoulliTree &other)
{
    node<elem> **tmp = forest, *carry;//进位
    int tmpSize = size;
    int min = size < other.size ? size : other.size;
    int i;

    if (size < other.size)
    {
        size = other.size;
        if (other.forest[size] != nullptr) ++size;
    }
    else if (forest[size] != nullptr) ++size;

    forest = new node<elem> *[size];
    for (i = 0; i < size; i++)
        forest[i] = nullptr;
    
    carry = nullptr;
    for (i = 0; i < min; i++)
    {
        if (carry == nullptr)
        {
            if (tmp[i] == nullptr) forest[i] = other.forest[i];
            else
            {
                if (other.forest[i] == nullptr) forest[i] = tmp[i];
                else carry = merge(other.forest[i], tmp[i]);
            }
        }
        else
        {
            if (tmp[i] != nullptr && other.forest[i] != nullptr)
            {
                forest[i] = carry;
                carry = merge(other.forest[i], tmp[i]);
            }
            else
            {
                if (tmp[i] == nullptr && other.forest[i] == nullptr)
                {
                    forest[i] = carry; carry = nullptr;
                }
                else if (tmp[i] == nullptr) carry = merge(other.forest[i], carry);
                else
                {
                    carry = merge(tmp[i], carry);
                }
            }
            
        }
    }

    if (other.size == min)
    {
        for (; i < tmpSize; i++)
        {
            if (carry == nullptr) forest[i] = tmp[i];
            else if (tmp[i] == nullptr)
            {
                forest[i] = carry; carry = nullptr;
            }
            else carry = merge(tmp[i], carry);
        }
    }  
    else
    {
        for (; i < other.size; i++)
        {
            if (carry == nullptr) forest[i] = other.forest[i];
            else if (other.forest[i] == nullptr)
            {
                forest[i] = carry;
                carry = nullptr;
            }
            else carry = merge(other.forest[i], carry);
        }
    }

    if (carry != nullptr) forest[i] = carry;

    for (i = 0; i < other.size; i++) other.forest[i] = nullptr;
    delete []tmp;
}

template<class elem>
void bernoulliTree<elem>::push(const elem &d)
{
    bernoulliTree tmp(1);
    tmp.forest[0] = new node<elem> (d);
    merge (tmp);
}

template<class elem>
elem bernoulliTree<elem>::pop()
{
    elem value;
    int min = findmin();

    if (min == 0)
    {
        value = forest[0] ->dt;
        delete forest[0];
        forest[0] = nullptr;
        return value;
    }

    node<elem> *t = forest[min], *son, *bro;
    int sizeOfQueue = int(pow(2,min)-1);
    bernoulliTree tmp(sizeOfQueue);
    value = t ->dt;
    forest[min] = nullptr;

    son = t ->son;
    delete t;
    int i = 0;

    do{
        tmp.forest[i++] = son;
        bro = son ->bro;
        son ->bro = nullptr;
    }while((son = bro) != nullptr);

    merge(tmp);

    return value;
}

template<class elem>
node<elem> *bernoulliTree<elem>::merge(node<elem> *t1, node<elem> *t2)
{
    node<elem> *min, *max;
    if (t1 ->dt > t2 ->dt){min = t2; max = t1;}
    else {min = t1; max = t2;}

    if (min ->son == nullptr) min ->son = max;
    else
    {
        node<elem> *t = min ->son;
        while(t ->bro != nullptr) t = t ->bro;
        t ->bro = max;
    }
    return min;
}

template<class elem>
void bernoulliTree<elem>::deleteTree(node<elem> *rt)
{
    node <elem> *son = rt ->son, *t;
    while(son != nullptr)
    {
        t = son;
        son = son ->bro;
        deleteTree(t);
    }
    delete rt;
}

template<class elem>
int bernoulliTree<elem>::findmin()
{
    int min, i;

    //找到第一颗非空的树min
    for (i = 0; i < size && forest[i] == nullptr; i++);
    min = i;

    for(; i < size; i++)
        if (forest[i] != nullptr && forest[i] ->dt < forest[min] ->dt)
            min = i;
    return min;
}

template<class elem>
bool bernoulliTree<elem>::empty()
{
    for (int i = 0; i < size; i++)
        if (forest[i] != nullptr) return false;
    return true;
}

template<class elem>
elem bernoulliTree<elem>::top()
{
    int pos = findmin();
    return forest[pos] ->dt;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, value; char ch[10];
    cin >> N;
    bernoulliTree<int> que(20004);

    for (int i = 0; i < N; i++)
    {
        cin >> ch;

        if (!strcmp(ch, "insert"))
        {
            cin >> value;
            que.push(value);
        }
        else if (!strcmp(ch, "delete"))
            que.pop();
        else if (!strcmp(ch, "min"))
            cout << que.top() << '\n';
        cin.get();

    }

    return 0;
}

/*
//基于二叉堆的优先队列的实现

#include <iostream>
#include <cstring>
using namespace std;

class priorityQueue//使用顺序存储
{
private:
    int *dt;
    int maxSize;
    int curSize;

void doubleSpace();
void buildHeap();
void perDown(int i);

public:
    priorityQueue(int initSize = 100);
    priorityQueue(const int a[], int size);
    ~priorityQueue(){delete [] dt;}
    void push(int d);
    int pop();
    bool empty(){return curSize == 0;}
    int top(){return dt[1];}  
}; // priorityQueue

void priorityQueue::doubleSpace()
{
    int *tmp = dt;
    maxSize *= 2;
    dt = new int[maxSize];
    for (int i = 0; i < curSize; i++)
        dt[i] = tmp [i];
    delete [] tmp;
}

void priorityQueue::buildHeap()
{
    for (int i = curSize/2; i > 0; i--)
        perDown(i);
}

void priorityQueue::perDown(int i)
{
    int child;
    int tmp = dt[i];

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

int priorityQueue::pop()
{
    int tmp = dt[1];
    dt[1] = dt[curSize--];
    perDown(1);
    return tmp;
}

void priorityQueue::push(int d)
{
    if (curSize == maxSize - 1) doubleSpace();

    int hole = ++curSize;

    for (; hole > 1 && d < dt[hole/2]; hole /= 2)
        dt[hole] = dt[hole/2];
    dt[hole] = d;
}

priorityQueue::priorityQueue(int initSize)
{
    dt = new int [initSize];
    maxSize = initSize;
    curSize = 0;
}

priorityQueue::priorityQueue(const int a[], int size)
{
    dt = new int[size];
    for (int i = 0; i < size; i++)
        dt[i+1] = a[i];
    curSize = size;
    maxSize = size * 2;
    buildHeap();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(0);

    int N, value; char ch[10];
    cin >> N;
    priorityQueue que(20004);

    for (int i = 0; i < N; i++)
    {
        cin >> ch;

        if (!strcmp(ch, "insert"))
        {
            cin >> value;
            que.push(value);
        }
        else if (!strcmp(ch, "delete"))
            que.pop();
        else if (!strcmp(ch, "min"))
            cout << que.top() << '\n';
        cin.get();

    }
    return 0;
}

*/