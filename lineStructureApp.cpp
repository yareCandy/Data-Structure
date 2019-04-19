//lineApp.cpp
//线性表的应用

#include <iostream>
using namespace std;

//应用1：根据字典书序比较两个线性表的大小
template<class T>
int compare(seqList &a, seqList &b)
{
    //若 a == b 返回0，a < b返回 -1；否则返回1
    int j = 0;
    while (j < a.length() && j < b.length())
    {
        if (a.dt[j] < b.dt[j]) return -1;
        else if (a.dt[j] > b.dt[j]) return 1;
        else j++;
    }

    if (a.length() == b.length()) return 0;
    else if (a.length() < b.length()) return -1;
    else return 1;
}

//应用二：将用线性表表示的集合合并为纯集合，即不含重复元素
template<class T>
void purge_sq(seqList &a, seqList &b)
{
    //已知a为空，将b的所有值不重复的插入到a
    a.dt[0] = b.dt[0];
    T tmp;
    int j;

    for (int i = 1; i < b.length(); i++)
    {
        tmp = b.dt[i];
        j = 0;
        while (j < a.length() && a.dt[j] != tmp) j++;
        if (j == a.length())
        {
            a.dt[a.length] = tmp;
        }
    }
}

//应用3：逆序创建单链表
template<class T>
void createList(linkList &l, T dt[], int n)
{
    head = nullptr;
    node *tmp;

    for (i = n -1; i >= 0; --i)
    {
        tmp = new node(dt[i], head);
        head = tmp;
    }
}

//应用3：有序表的插入
template<class T>
void ordInsert_sq(seqList &l, T &x)
{
    node *p = head, *q = p ->next;
    while (q != nullptr && q->dt <x)
    {
        q = q ->next;
        p = p ->next;
    }
    node *tmp = new node(x, q);
    p ->next = tmp;
}


//有序表求并集
void union(linkList &la, linkList &lb)
{
    const int MAX = 1000000;
    //头节点的数据设置为最大值
    la ->next ->dt = MAX;
    lb ->next ->dt = MAX;

    node *pa = la ->next ->next;
    node *pb = lb ->next ->next;
    node *rc = la ->next;
    node *qb;
    while (pa != la ->next || pb != lb ->next)
    {
        if (pa ->dt < pb ->dt;
        {
            rc ->next = pa;
            rc = pa;
            pa = pa ->next;
        }
        else if (pa ->dt > pb ->dt)
        {
            rc ->next = pb ->next;
            rc = pb;
            pb = pb ->next;
        }
        else
        {
            rc ->next = pa;
            rc = pa;
            pa = pa ->next;
            qb = pb ->next;
            pb = pb ->next;
            delete qb;
        }
    }

    rc ->next = la;
    delete lb ->next;
}
