//1221.cpp
//二叉查找树的相关操作
//插入、删除
//删除比x小的元素，比min大，比max小的元素
//查找第i小的元素
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

template <class KEY>
class binarySearchTree
{
private:
    struct node
    {
        KEY dt;
        node *left;
        node *right;
        node (const KEY &d, node *l = nullptr, node *r = nullptr)
            :dt(d), left(l), right(r){}
        node():left(nullptr), right(nullptr){}
    };

    node *root;

public:
    binarySearchTree():root(nullptr){}
    ~binarySearchTree(){clear(root);}
    bool empty()const {return root == nullptr;}
    void push(const KEY &d);
    void pop(const KEY &d);
    void delete_less_than(const KEY &d);
    void delete_greater_than(const KEY &d);
    void delete_interval(const KEY &min, const KEY &max);
    void find(const KEY &d)const;
    void find_ith(int i)const;


private:
    void push(const KEY &d, node *&t);
    void pop(const KEY &d, node *& t);
    void delete_less_than(const KEY &d, node *&t);
    void delete_greater_than(const KEY &d, node *&t);
    void delete_interval(const KEY &min, const KEY &max, node *&t);

private:
    void clear(node *t);
};


template<class KEY>
void binarySearchTree<KEY>::push(const KEY &d, node *&t)
{
    if (t == nullptr)
        t = new node (d);
    if (d < t ->dt)
        push(d, t ->left);
    else
        push(d, t ->right);
}

template<class KEY>
void binarySearchTree<KEY>::pop(const KEY &d, node *&t)
{
    if (t == nullptr)
        return;
    if (d < t ->dt)
        pop(d, t ->left);
    else if (d > t ->dt)
        pop(d, t ->right);
    else
    {
        if (t ->left != nullptr && t ->right != nullptr)
        {
            node *tmp = t ->right;
            while (tmp ->left != nullptr)
                tmp = tmp ->left;
            t ->dt = tmp ->dt;
            pop(d, tmp);
        }
        else
        {
            node *tmp = t;
            t = (t ->left == nullptr) ? right : left;
            delete tmp;
        }
    }
}

template<class KEY>
void binarySearchTree<KEY>::find(const KEY &d)const
{
    if (root == nullptr) {cout << "N\n"; return;}

    stack<node *> stack;
    stack.push(root);
    node *tmp;

    while (!stack.empty())
    {
        tmp = stack.top();
        stack.pop();
        if (tmp == nullptr)
        {
            cout << "N\n";
            return;
        }

        if (d == tmp ->dt)
        {
            cout << "Y\n";
            return;
        }
        else if (d < tmp ->dt)
            stack.push(tmp ->left);
        else
            stack.push(tmp ->right);
    }
    cout << "N\n";
    return;
}

template<class KEY>
void binarySearchTree<KEY>::find_ith(int i)const
{
    if (root == nullptr) {cout << "N\n"; return;}

    struct Node
    {
        node *t;
        int timePop;
        Node (node *T = nullptr, int times = 0):t(T), timePop(times){}
    };

    stack<Node> stack;
    Node current(root);
    stack.push(current);

    while (!stack.empty())
    {
        current = stack.top();
        stack.pop();

        if (++current.timePop == 2)
        {
            i--;
            if (current.t ->right != nullptr)
                stack.push(Node(current.t ->right));
        }
        else
        {
            stack.push(current);
            if (current.t ->left != nullptr)
                stack.push(Node(current.t ->left));
        }

        if (i == 0)
        {
            cout << current.t ->dt << "\n";
            return;
        }
    }

    cout << "N\n";
    return;
}

template<class KEY>
void binarySearchTree<KEY>::delete_less_than(const KEY &d, node *&t)
{
    if (t == nullptr) return;

    if (d <= t ->dt)
        delete_less_than(d, t ->left);
    else
    {
        clear(t ->left);
        delete_less_than(d, t ->right);
        pop(t);
    }
}

template<class KEY>
void binarySearchTree<KEY>::delete_greater_than(const KEY &d, node *&t)
{
    if (t == nullptr) return;

    if (d >= t ->dt)
        delete_greater_than(d, t ->right);
    else
    {
        clear(t ->right);
        delete_greater_than(d, t ->left);
        pop(t);
    }
}

template<class KEY>
void binarySearchTree<KEY>::delete_interval(const KEY &min, const KEY &max, node *&t)
{
    if (t == nullptr) return;

    if (min >= t ->dt)
        delete_interval(min, max, t ->right);
    else if (max <= t ->dt)
        delete_interval(min, max, t ->left);
    else
    {
        delete_interval(min, max, t ->left);
        delete_interval(min, max, t ->right);
        pop(t);
    }
}

template<class KEY>
void binarySearchTree<KEY>::clear(node *t)
{
    if (t == nullptr) return;

    clear(t ->left);
    clear(t ->right);
    delete t;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char command[30];
    int N, j, k;
    cin >> N;

    binarySearchTree<int> tree;

    for (int i = 0; i < N; i++)
    {
        cin >> command;

        if (!strcmp(command, "insert"))
        {
            cin >> k;
            tree.push(k);
        }
        else if (!strcmp(command, "delete"))
        {
            cin >> j;
            tree.pop(j);
        }
        else if (!strcmp(command, "find"))
        {
            cin >> k;
            tree.find(k);
        }
        else if (!strcmp(command, "find_ith"))
        {
            cin >> j;
            tree.find_ith(i);
        }
        else if(!strcmp(command, "delete_less_than"))
        {
            cin >> k;
            tree.delete_less_than(k);
        }
        else if(!strcmp(command, "delete_greater_than"))
        {
            cin >> j;
            tree.delete_greater_than(j);
        }
        else if (!strcmp(command, "delete_interval"))
        {
            cin >> j >> k;
            tree.delete_interval(j, k);
        }

        cin.get();
    }

    return 0;
}
