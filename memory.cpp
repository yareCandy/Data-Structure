//memory.cpp
//模拟动态内存管理器

#include <iostream>
using namespace std;

class memory
{
    private:
        struct node
        {
            int start;
            int end;
            node *prev;
            node *next;
            node():prev(NULL),next(NULL){};
            node(int s, int e, node *p = NULL, node *n = NULL)
            :start(s), end(e), prev(p), next(n){};
        };

        node *head, *tail;//尾指针
    public:
        memory(int capacity);  //初始化
        ~memory();
        int malloc(int size);  //分配动态内存
        void free(int start, int end);//回收内存
};

memory::memory(int capacity)
{
    head = new node;                                  //申请头节点
    head -> next = new node(0, capacity - 1, head);   //初始化内存大小
    head -> next -> next = tail = new node;           //申请尾节点
    tail -> prev = head -> next;                       //为为节点设置前驱
}

memory::~memory()
{
    node *p = head, *q;
    while(p != NULL)
    {
        q = p -> next;//神奇的移动: 包含勒最后元素的删除
        delete p;
        p = q;
    }
}

int memory::malloc(int size)
{
    node *p = head -> next;
    int returnValue;

    while(p != tail && p -> end - p -> start + 1 < size)
        p = p -> next;
    if (p == tail) return -1; //没找到大小合适的位置
    returnValue = p -> start;
    //将要分配出去的空间从内存记录中去掉
    if (p -> end - p -> start + 1 == size)
    {
        p -> prev -> next = p -> next;//去掉这一大块的内存
        p -> next -> prev = p -> prev;
        delete p;
    }

    else p -> start += size;

    return returnValue;
}


void memory::free(int start, int size)
{
    node *p = head -> next, *np;
    while (p != tail && p -> start < start)//找到比释放空间地址大的第一个节点
        p = p -> next;

    //如果释放的空间可以和p连成一片
    if (p != tail && start + size == p -> start)
    {
        p -> start = start;
        np = p;
    }
    else
    {
        np = new node (start, start + size - 1, p -> prev, p);
        p -> prev -> next = np;
        p -> prev = np;
    }

    //处理与前一节点能否连成一片
    p = np -> prev;
    if (p -> end + 1 == np -> start)
    {
        p -> end = np -> end;
        p -> next = np -> next;
        np -> next -> prev = p;
        delete np;
    }
}