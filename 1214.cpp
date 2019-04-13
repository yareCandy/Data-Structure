//1214.cpp
//OJ1214
//实现孩子兄弟链的遍历
//关键是根据无需节点创建一棵树

#include <iostream>
using namespace std;

template <class T>
class linkQueue
{
    private:
        struct node
        {
            T dt;
            node *pre;
            node *next;
            node (T d, node *f = nullptr, node *r = nullptr)
                :dt(d), pre(f), next(r){}
            node() :pre(nullptr), next(nullptr){}
        };

        node *front, *rear;
    public:
        linkQueue() :front(nullptr), rear(nullptr){}
        ~linkQueue()
        {
            if (front == nullptr)
                return;

            node *p;
            while (front != nullptr)
            {
                p = front ->next;
                delete front;
                front = p;
            }
        }

        bool isEmpty(){return front == nullptr;}

        void enQueue(int d)
        {
            if (front == nullptr)
                front = rear = new node(d);
            else rear = rear ->next = new node(d);
        }

        T deQueue()
        {
            node *tmp = front;
            T value = front ->dt;
            front = front ->next;

            delete tmp;
            if (front == nullptr)
                rear = nullptr;

            return value;
        }
};


class tree
{
    struct node{
        int dt;
        int son;
        int brother;
        int parent;

        node(int d = 0, int s = 0, int b = 0, int p = 0) :dt(d), son(s), brother(b), parent(p){}
    };

private:
    int root;
    node a[100001];//存储所有节点
public:
    tree()
    {
        int son, bro, size;
        cin >> size;//节点数

        if (size == 0) root = 0;
        else root = 1;

        for (int i = 1; i <= size; i++)
        {
            cin >> son;
            a[i].son = son;

            cin >> bro;
            a[i].brother = bro;

            a[son].parent = a[bro].parent = i;
            cin >> a[i].dt;
        }

        while (a[root].parent)
            root = a[root].parent;
    }

    ~tree(){};

    void preOrder()const{preOrder(root);}
    void postOrder()const{postOrder(root);}
    void levelOrder()const
    {
        if (root == 0) return;
        int tmp;
        linkQueue<int> que;
        que.enQueue(root);

        while(!que.isEmpty())
        {
            tmp = que.deQueue();
            cout << a[tmp].dt << ' ';
            tmp = a[tmp].son;

            while(tmp != 0)
            {
                que.enQueue(tmp);
                tmp = a[tmp].brother;
            }
        }
    }

private:
    void preOrder(int t)const
    {
        if (t == 0) return;

        cout << a[t].dt << ' ';
        preOrder(a[t].son);
        preOrder(a[t].brother);

    }

    void postOrder(int t)const
    {
        if (t == 0) return;

        postOrder(a[t].son);
        cout << a[t].dt << ' ';
        postOrder(a[t].brother);

    }

};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    tree t;
    t.preOrder();
    cout << '\n';
    t.postOrder();
    cout << '\n';
    t.levelOrder();
    cout << '\n';

    return 0;
}
