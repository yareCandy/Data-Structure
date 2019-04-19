//sLinkList.cpp
//实现单链表类的基本运算

#include <iostream>
using namespace std;

template <class T>
class sLinkList
{
    private:
        struct node
        {
            T data;
            node *next;

            node(const T &d, node *n = NULL):data(d), next(n){}
            node(){next = NULL;}
        };

        node *head;
        int size;

        node *move(int i)const
        {
            if (i < 0 || i > size - 1) { cout << "Error!" << endl; return NULL;}

            node *p = head -> next;
            for (int j = 0; j < i; j++) p = p->next;

            return p;
        }

    public:
        //构造函数，创建一个头节点
        sLinkList(){head = new node; size = 0;}
        //clear: 清空链表, 但保留头节点
        void clear(){ while(length() != 0) remove(0);}
        //length: 返回当前链表长度
        int length()const {return size;}
        //insert: 指定的位置插入数据
        void insert(int i, T &d)
        {
            node *p = move(i - 1);
            p->next = new node(d, p->next);
            size++;
        }
        //remove: 删去指定的节点
        void remove(int i)
        {
            node *p = move(i-1), *q = p->next;
            p->next = q->next;
            delete q;
            size--;
        }
        //search: 查找指定的数据对应的节点号
        int search(T d)const
        {
            int i = 0;
            node *p = head->next;
            while (p->data != d && p != NULL)
            {
                p = p->next;
                i++;
            }
            if (p == NULL) return -1;
            else return i;
        }
        //visit: 访问指定节点
        T visit(int i)const
        {
            node *p = head->next;
            for (int j = 0; j < i; j++) p = p->next;
            return p->data;
        }
        //traverse: 遍历链表
        void traverse()const
        {
            node *p = head -> next;
            while(p != NULL)
            {
                cout << p -> data << '\t';
                p = p -> next;
            }
        }
        //析构函数，回收空间
        ~sLinkList(){ clear(); delete head;}

        //翻转函数，将单链表中的元素反序，要求时间复杂度为O（N）
        void reverse()
        {
            if (head -> next == NULL || head -> next -> next == NULL) return;//空表或仅一个元素的表
            node *p = head -> next, *q = p -> next;
            p -> next = NULL;
            while(p != NULL)
            {
                p = q;
                q = q -> next;
                p -> next = head -> next;
                head -> next = p;
            }
        }
};

int main()
{
    sLinkList<int> List;
    cout << List.length() << endl;

    system("pause");
    return 0;
}
