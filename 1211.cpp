//1214c.cpp
//OJ1214
//实现孩子兄弟链的遍历
//关键时要接收数据并将之构建成树

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

        void enQueue(T &d)
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
        int left;
        int right;
        int parent;

        node(int s = 0, int b = 0, int p = 0) : left(s), right(b), parent(p){}
    };

private:
    int root;
    node a[100001];//存储所有节点
public:
    tree()
    {
        int left, right, size;
        cin >> size;//节点数

        if (size == 0) root = 0;
        else root = 1;

        for (int i = 1; i <= size; i++)
        {
            cin >> left;
            a[i].left = left;
            cin >> right;
            a[i].right = right;

            a[left].parent = a[right].parent = i;

        }

        while (a[root].parent)
            root = a[root].parent;
    }

    ~tree(){};


    bool isCompleteTree()
    {
    if (!root) return true;

    bool twoleft = true;
    int tmp;
    linkQueue<int> que;
    que.enQueue(root);

    while (!que.isEmpty())
    {
        tmp = que.deQueue();

        if (twoleft)//尚未发现只有一个儿子或者没有儿子的节点
        {
            if (a[tmp].left != 0  && a[tmp].right != 0)
            {
                que.enQueue(a[tmp].left);
                que.enQueue(a[tmp].right);
            }
            else if (a[tmp].left == 0 && a[tmp].right != 0)//某个节点左儿子为空
            {
                return false;
            }
            else if (a[tmp].left == 0 && a[tmp].right == 0)//找到一个节点没有右孩子，那后面的所有节点应该全部没有孩子
            {
                twoleft = false;
            }
            else //左孩子不为0，右孩子为0
            {
                que.enQueue(a[tmp].left);
                twoleft = false;
            }
        }
        else //目前已经发现有一个节点没有孩子或只有左孩子，其后所有节点应该没有孩子
        {
            if (a[tmp].left || a[tmp].right) return false;//后面还有节点有孩子，就不是完全二叉树
        }

    }

    return true;
}

};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    tree t;
    bool flag = t.isCompleteTree();

    if (flag) cout << "Y\n";
    else cout << "N\n";

    return 0;
}
