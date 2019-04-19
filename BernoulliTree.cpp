//二项堆
//贝努利树，用森岭保存一颗有序树
//合并简单
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

//孩子兄弟树
template<class elem>
struct node
{
    elem dt;
    node *son;
    node *bro;
    node (const elem &d, node *s = nullptr, node *b = nullptr)
        :dt(d), son(s), bro(b){}
    node() : son (nullptr), bro(nullptr){}
};

template<class elem>
class bernoulliTree
{
private:
    node<elem> **forest;//存放森林
    int size;

public:
    bernoulliTree(int initSize = 10);
    ~bernoulliTree();
    void push(const elem &d);
    elem pop();
    bool empty();
    elem top();    
    void merge(const bernoulliTree &other);

private:
    int findmin();
    void deleteTree(node<elem> *rt);
    node<elem> *merge(node<elem> *t1, node<elem> *t2);
};

template<class elem>
bernoulliTree<elem>::bernoulliTree(int initSize)
{
    size = int (log(initSize)/log(2)) + 1;
    forest = new node<elem> *[size];

    for (int i = 0; i < size; i++)
        forest[i] = nullptr;    
}

template<class elem>
bernoulliTree<elem>::~bernoulliTree()
{
    for (int i = 0; i < size; i++)
        if (forest[i] != nullptr) deleteTree(forest[i]);
    delete forest;
}

template<class elem>
void bernoulliTree<elem>::merge(const bernoulliTree &other)
{
    node<elem> **tmp = forest, *carry;//进位
    int tmpSize = size;
    int min = size < other.size ? size : other.size;
    int i;

    if (size < other.size)
    {
        size = other.size;
        if (other.forest[size] != nullptr) ++size;
    }
    else if (forest[size] != nullptr) ++size;

    forest = new node<elem> *[size];
    for (i = 0; i < size; i++)
        forest[i] = nullptr;
    
    carry = nullptr;
    for (i = 0; i < min; i++)
    {
        if (carry == nullptr)
        {
            if (tmp[i] == nullptr) forest[i] = other.forest[i];
            else
            {
                if (other.forest[i] == nullptr) forest[i] = tmp[i];
                else carry = merge(other.forest[i], tmp[i]);
            }
        }
        else
        {
            if (tmp[i] != nullptr && other.forest[i] != nullptr)
            {
                forest[i] = carry;
                carry = merge(other.forest[i], tmp[i]);
            }
            else
            {
                if (tmp[i] == nullptr && other.forest[i] == nullptr)
                {
                    forest[i] = carry; carry = nullptr;
                }
                else if (tmp[i] == nullptr) carry = merge(other.forest[i], carry);
                else
                {
                    carry = merge(tmp[i], carry);
                }
            }
            
        }
    }

    if (other.size == min)
    {
        for (; i < tmpSize; i++)
        {
            if (carry == nullptr) forest[i] = tmp[i];
            else if (tmp[i] == nullptr)
            {
                forest[i] = carry; carry = nullptr;
            }
            else carry = merge(tmp[i], carry);
        }
    }  
    else
    {
        for (; i < other.size; i++)
        {
            if (carry == nullptr) forest[i] = other.forest[i];
            else if (other.forest[i] == nullptr)
            {
                forest[i] = carry;
                carry = nullptr;
            }
            else carry = merge(other.forest[i], carry);
        }
    }

    if (carry != nullptr) forest[i] = carry;

    for (i = 0; i < other.size; i++) other.forest[i] = nullptr;
    delete []tmp;
}

template<class elem>
void bernoulliTree<elem>::push(const elem &d)
{
    bernoulliTree tmp(1);
    tmp.forest[0] = new node<elem> (d);
    merge (tmp);
}

template<class elem>
elem bernoulliTree<elem>::pop()
{
    elem value;
    int min = findmin();

    if (min == 0)
    {
        value = forest[0] ->dt;
        delete forest[0];
        forest[0] = nullptr;
        return value;
    }

    node<elem> *t = forest[min], *son, *bro;
    int sizeOfQueue = int(pow(2,min)-1);
    bernoulliTree tmp(sizeOfQueue);
    value = t ->dt;
    forest[min] = nullptr;

    son = t ->son;
    delete t;
    int i = 0;

    do{
        tmp.forest[i++] = son;
        bro = son ->bro;
        son ->bro = nullptr;
    }while((son = bro) != nullptr);

    merge(tmp);

    return value;
}

template<class elem>
node<elem> *bernoulliTree<elem>::merge(node<elem> *t1, node<elem> *t2)
{
    node<elem> *min, *max;
    if (t1 ->dt > t2 ->dt){min = t2; max = t1;}
    else {min = t1; max = t2;}

    if (min ->son == nullptr) min ->son = max;
    else
    {
        node<elem> *t = min ->son;
        while(t ->bro != nullptr) t = t ->bro;
        t ->bro = max;
    }
    return min;
}

template<class elem>
void bernoulliTree<elem>::deleteTree(node<elem> *rt)
{
    node <elem> *son = rt ->son, *t;
    while(son != nullptr)
    {
        t = son;
        son = son ->bro;
        deleteTree(t);
    }
    delete rt;
}

template<class elem>
int bernoulliTree<elem>::findmin()
{
    int min, i;

    //找到第一颗非空的树min
    for (i = 0; i < size && forest[i] == nullptr; i++);
    min = i;

    for(; i < size; i++)
        if (forest[i] != nullptr && forest[i] ->dt < forest[min] ->dt)
            min = i;
    return min;
}

template<class elem>
bool bernoulliTree<elem>::empty()
{
    for (int i = 0; i < size; i++)
        if (forest[i] != nullptr) return false;
    return true;
}

template<class elem>
elem bernoulliTree<elem>::top()
{
    int pos = findmin();
    return forest[pos] ->dt;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, value; char ch[10];
    cin >> N;
    bernoulliTree<int> que(20004);

    for (int i = 0; i < N; i++)
    {
        cin >> ch;

        if (!strcmp(ch, "insert"))
        {
            cin >> value;
            que.push(value);
        }
        else if (!strcmp(ch, "delete"))
            que.pop();
        else if (!strcmp(ch, "min"))
            cout << que.top() << '\n';
        cin.get();

    }

    return 0;
}