//4228.cpp
//OJ4228
//第一行包含一个正整数N，表示下面给出的姓名个数。
//接下来N行每行给出一个名字（名字中没有空格且没有重名的人），然后接一个email地址。
//输出合并后的姓名组。一行一组，每组的姓名按照输入的先后顺序以空格隔开。
//输出的组按照第一个姓名输入的顺序排序。

#include <iostream>
#include <queue>
#include <string>
using namespace std;


struct node
{
        string address;
        int label;
        node *left;
        node *right;
        node(string mail, node *l = nullptr, node *r = nullptr)
        {
            address = mail;
            left = l;
            right = r;
        }
        node ():left(nullptr), right(nullptr){}
};

class nameTree
{
//    friend void change(nameTree &t);
private:
    node *root;
public:
    nameTree():root(nullptr){}
    ~nameTree(){clear(root);}
    void insert(const string address, const string name, string a[]);
//    void traverse()const;
//    void insert(const node *t);
private:
//    void traverse(node *t)const;
    void clear(node *t);
    void insert(const string address, const string name, string a[], node * &t);
//    void insert(const node *t, node *&rt);
};

int label = 0;

/*
void change(nameTree &t)
{
    if (t.root == nullptr||(t.root ->left == nullptr && t.root ->right == nullptr)) return;

    node *tmp = t.root;
    t.root = nullptr; 

    queue<node *> que;
    que.push(tmp);

    while(!que.empty())
    {
        tmp = que.front();
        que.pop();
        t.insert(tmp);

        if (tmp ->left) que.push(tmp ->left);
        if (tmp ->right) que.push(tmp ->right);
    }
}

void nameTree::insert(const node *t)
{
    insert(t, root);
}

void nameTree::insert(const node *t, node * &rt)
{
    if (rt == nullptr) 
    {
        rt = new node (t ->address);
        rt ->name = t ->name;
    }

    else if (rt ->name < t ->name)
        insert(t, rt ->right);
    else
        insert(t, rt ->left);    
}
*/


void nameTree::insert(const string address, const string name, string a[])
{
    insert(address, name, a, root);
}

void nameTree::insert(const string address, const string name, string a[], node * &t)
{
    if (t == nullptr)
    {
        t = new node (address, nullptr, nullptr);
        a[++label] = name;
        t ->label = label;
    }

    else if (address > t ->address)
        insert(address, name, a, t ->right);
    else if (address < t ->address)
        insert(address, name, a, t ->left);
    else if (address == t ->address)
    {
        a[t ->label] += ' ';
        a[t ->label] += name;
    }
}

/*
void nameTree::traverse()const
{
    traverse(root);
}
void nameTree::traverse(node *t)const
{
    if (t == nullptr) return;

    traverse(t ->left);
    cout << t ->name << '\n';
    traverse(t ->right);
}
*/

void nameTree::clear(node *t)
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

    string name;
    nameTree tree;
    string email;
    int N;
    cin >> N;

    string array[N+1];

    for (int i = 0; i < N; i++)
    {
        cin >> name; cin.get();
        cin >> email;
        tree.insert(email, name, array);
    }

    for (int i = 1; i <= label; i++)
        cout << array[i] << '\n';

    return 0;    
}