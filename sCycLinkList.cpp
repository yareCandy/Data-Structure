//sCycLinkList.cpp
//单循环链表的定义及实现

#include <iostream>
using namespace std;

template<class T>
class sCycLinkList
{
    private:
        struct node
        {
            T data;
            node *next;

            node(const T &d, node *n = NULL): data(d), next(n) {}
            node(): next(NULL) {}
        };

        int size;
        node *head;

    public:
        sCycLinkList(): head(NULL), size(0){}
        ~sCycLinkList()
        {
            if (head != NULL)
            {
                node *p = head, *tmp;

                do{
                   tmp = head -> next;
                   delete head;
                   head = tmp;
                }while(head == p);
            }
        }

        class myItr
        {
            private:
                node *current;

            public:
                myItr(node *p = NULL): current(p){}

                myItr operator++(int i)//后置++
                {
                    node *tmp = current;
                    current = current -> next;
                    return tmp;
                }
                //前置++
                myItr operator++(){ return current = current -> next;}

                T &operator*(){ return current -> data;}//取迭代器指向的元素值

                bool operator==(const myItr &other)const { return current == other;}

                bool operator!=(const myItr &other)const { return current != other;}

                bool IsNull()const { return current == NULL;}
        };

        //与迭代器有关的操作
        myItr begin(){ return head;} //返回表头的迭代器
        //在迭代器后面插入一个节点，迭代器返回新节点的地址
        myItr insert(myItr &p, const T &n)
        {
            if (p.current = NULL)
            {
                head = p.current = new node(n);
                head = head -> next;
            }
            else
            {
                p.current = p.current -> next = new node(n);
            }
        }
        //删除迭代器后面的节点
        void erear(myItr &p)
        {
            if (p.current == NULL) return;
            if (p.current -> next == p.current)
            {
                delete p.current;
                head = p.current = NULL;
            }
            else
            {
                node *q;
                q = p.current -> next;
                p.current -> next = q -> next;
                if (q == head) head = q -> next;
                delete q;
            }
        }
        //查找指定元素对应的地址
        myItr search(const T &a)
        {
            myItr p = begin(), q = p;
            for (++p; p != q; p++)
                if (a == *p) return p;
            return NULL;
        }
};
