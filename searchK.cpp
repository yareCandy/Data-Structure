//search.cpp
//寻找单链表倒数第k个元素
//思想：用两个相距K的指针同时向前移动，当前面的指针为空时

#include <iostream>
using namespace std;

//栈：链表实现栈
template<class T>
class linkStack
{
private:
    struct node
    {
        T dt;
        node *next;
        node (const T &d, node *t = nullptr)
            :dt(d), next(t){}
        node(): next(nullptr){}
        ~node(){}
    };

    node *top_p;

public:
    linkStack(){top_p = nullptr;}
    ~linkStack();
    T top() {return top_p ->dt;}
    bool isEmpty(){return top_p == nullptr;}
    void push(const T &d);
    T pop();
    void traverse()const;
};

template<class T>
linkStack<T>::~linkStack()
{
    if (top_p == nullptr) return;

    node *p;
    while (p != nullptr)
    {
        p = top_p;
        top_p = top_p ->next;
        delete p;
    }
}

template<class T>
void linkStack<T>::push(const T &d)
{
    node *tmp = new node(d, top_p);
    top_p = tmp;
}

template<class T>
T linkStack<T>::pop()
{
    node *tmp = top_p;
    T value = tmp ->dt;
    top_p = top_p ->next;
    delete tmp;
    return value;
}


template <class T>
struct node
{
    T data;
    node *next;
};


//访问单链表倒数第k个元素
//成功返回1， 否则返回0
template <class T>
int searchK(const node<T> *head, int k)
{
    if (k <= 0) return 0;

    node<T> *p = head, *q = p;
    for (int i = 0; i < k && q != NULL; i++)
        q = q -> next;
    if (q == NULL)
        return 0;

    while(q != NULL)
    {
        p = p -> next;
        q = q -> next;
    }

    cout << p -> data << endl;
    return 1;

}

template<class T>
void linkStack<T>::traverse()const
{
    if (top_p == nullptr) return;

    node *p = top_p;
    while (p != nullptr)
    {
        cout << p ->dt <<' ';
        p = p ->next;
    }
    cout << endl;
}
