//linkqueue.cpp
//链接实现队列

#include <iostream>
#include <cstring>
using namespace std;

template <class T>
class linkQueue
{
    private:
        struct node
        {
            T dt;
            node *next;
            node(const T &d, node *n = nullptr): dt(d), next(n){}
            node(): next(nullptr){}
        };

        node *front, *rear;
    public:
        linkQueue();
        ~linkQueue();
        T getHead()const;
        T getTail()const;
        bool isEmpty()const;
        void enQueue(const T& d);
        T deQueue();

};// linkQueue;

template <class T>
linkQueue<T>::linkQueue()
{
    rear = front = nullptr;
}

template<class T>
linkQueue<T>::~linkQueue()
{
    node *tmp;
    while(front != nullptr)
    {
        tmp = front;
        front = front ->next;
        delete tmp;
    }
}

template<class T>
bool linkQueue<T>::isEmpty()const
{
    return front == nullptr;//对空标志：没有头节点，队空时两个指针皆为nullptr
}

template <class T>
T linkQueue<T>::getHead()const
{
    return front -> dt;
}

template<class T>
T linkQueue<T>::getTail()const
{
    return rear -> dt;
}


template<class T>
void linkQueue<T>::enQueue(const T &d)
{
    if (rear == nullptr) front = rear = new node(d);
    else
    {
        rear ->next = new node(d);
        rear = rear ->next;
    }
}

template<class T>
T linkQueue<T>::deQueue()
{
    node *tmp = front;
    T value = front -> dt;
    front = front -> next;

    if (front == nullptr) rear = nullptr;//删除后为空链表
    delete tmp;
    return value;
}


//队列的循环实现
template<class T>
class seqQueue
{
private:
    T *dt;
    int maxSize;
    int front, rear;
    void doubleSpace();
public:
    seqQueue(int initSize = 10);
    ~seqQueue(){delete [] dt;}
    bool isEmpty()const {return front == rear;}
    void enQueue(const T &d);
    T deQueue();
    T getHead()const {return dt[(front + 1) % maxSize];}
};

template<class T>
void seqQueue<T>::doubleSpace()
{
    T *tmp = dt;
    dt = new T [maxSize * 2];

    for (int i = 1; i <= maxSize; i++)
        dt[i] = tmp[(front + i) % maxSize];
    front = 0;
    rear = maxSize;
    maxSize *= 2;
    delete [] tmp;
}

template<class T>
seqQueue<T>::seqQueue(int initSize)
{
    dt = new T [initSize];
    maxSize = initSize;
    front = rear = 0;
}

template<class T>
void seqQueue<T>::enQueue(const T &d)
{
    if ((rear+1)%maxSize == front)
        doubleSpace();
    rear = (rear+1) % maxSize;
    dt[rear] = d;
}

template<class T>
T seqQueue<T>::deQueue()
{
    front = (front + 1) % maxSize;
    return dt[rear];
}

