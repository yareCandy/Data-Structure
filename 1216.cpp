//1216.cpp
//OJ1216
//最小化堆实现的整型的优先队列，提供以下操作
//insert x，将优先级值为x的元素入队
//find x，找出优先级值大于x的最小的元素，输出其下标。如果有多个元素优先级值相同输出下标最小的那个
//decrease i v，将第i个节点的优先级值减少v
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;


template<class T>
class priorQueue
{
private:
    T *dt;
    int maxSize;
    int curSize;

public:
    priorQueue(int initSize = 10);
    priorQueue(const T data[], int size);
    ~priorQueue();
    void push(const T &d);
    T pop();
    T top()const;
    bool empty()const;
    void Find(const T &d);
    void decrease(int i, int x);
private:
    void doubleSpace();
    void percolateDown(int k);
    void buildHeap();
};

template<class T>
priorQueue<T>::priorQueue(int initSize)
{
    dt = new T[initSize];
    maxSize = initSize;
    curSize = 0;
}

template<class T>
priorQueue<T>::priorQueue(const T data[], int size)
{
    dt = new T[size+10];
    maxSize = size+10;
    curSize = size;
    for (int i = 0;i < size; i++)
        dt[i+1] = data[i];
    buildHeap();
}

template<class T>
priorQueue<T>::~priorQueue()
{
    delete [] dt;
}

template<class T>
bool priorQueue<T>::empty()const
{
    return curSize == 0;
}

template<class T>
T priorQueue<T>::top()const
{
    return dt[1];
}

template<class T>
T priorQueue<T>::pop()
{
    T tmp = dt[1];
    dt[1] = dt[curSize--];
    percolateDown(1);
    return tmp;
}

template<class T>
void priorQueue<T>::push(const T &d)
{
    if (curSize == maxSize - 1) doubleSpace();

    int tmp = ++curSize;
    for(; tmp > 1 && d < dt[tmp/2]; tmp /= 2)
        dt[tmp] = dt[tmp/2];
    dt[tmp] = d;
}

template<class T>
void priorQueue<T>::doubleSpace()
{
    T *tmp = dt;
    maxSize *= 2;
    dt = new T[maxSize];
    for (int i = 1; i <= curSize; i++)
        dt[i] = tmp[i];

    delete [] tmp;
}

template<class T>
void priorQueue<T>::percolateDown(int k)
{
    int child;
    T tmp = dt[k];

    for (; k*2 <= curSize; k = child)
    {
        child = k;
        if (child != curSize && dt[child+1] < dt[child])
            child++;
        if (dt[child] < tmp) dt[k] = dt[child];
        else break;
    }

    dt[k] = tmp;
}

template<class T>
void priorQueue<T>::buildHeap()
{
    for (int  i = curSize/2; i > 0; i--)
        percolateDown(i);
}

template<class T>
void priorQueue<T>::Find(const T &d)
{
    T min;
    int ID = -1;

    for (int i = 1; i <= curSize; i++)
    {
        if (dt[i] > d && (ID == -1 || min > dt[i]))
        {
            min = dt[i];
            ID = i;
        }
    }

    cout << ID << '\n';
}


template<class T>
void priorQueue<T>::decrease(int i, int x)
{
    int hole;
    
    hole = i;
    dt[hole] -= x;
    T tmp = dt[hole];

    for (; hole > 1 && dt[hole/2] > tmp; hole /= 2)
        dt[hole] = dt[hole/2];
    dt[hole] = tmp;
}

int main()
{
    int N, tmp, x;
    char command[10];
    cin >> N;
    priorQueue<int> que(20003);

    for (int i = 0; i < N; i++)
    {
        cin >> command;
        if (!strcmp(command, "insert"))
        {
            cin >> tmp;
            que.push(tmp);
        }
        else if (!strcmp(command, "find"))//找到比他大的最小元素，输出下标
        {
            cin >> tmp;
            que.Find(tmp);
        }
        else if (!strcmp(command, "decrease"))
        {
            cin >> tmp;
            cin >> x;
            que.decrease(tmp, x);
        }
        
    }

    return 0;
}
