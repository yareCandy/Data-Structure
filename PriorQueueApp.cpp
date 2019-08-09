//优先级队列

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

//--------------------------------------------顺序实现的最小化堆（最大化堆）-------------------------------

class priorityQueue//使用顺序存储实现的最小化堆
{
private:
    int *dt;
    int maxSize;
    int curSize;

void doubleSpace();
void buildHeap();
void perDown(int i);

public:
    priorityQueue(int initSize = 100);
    priorityQueue(const int a[], int size);
    ~priorityQueue(){delete [] dt;}
    void push(int d);
    int pop();
    bool empty(){return curSize == 0;}
    int top(){return dt[1];}  
    int Find(const int &d);
    void decrease(int i, int x);
}; // priorityQueue

void priorityQueue::doubleSpace()
{
    int *tmp = dt;
    maxSize *= 2;
    dt = new int[maxSize];
    for (int i = 0; i < curSize; i++)
        dt[i] = tmp [i];
    delete [] tmp;
}

void priorityQueue::buildHeap()
{
    for (int i = curSize/2; i > 0; i--)
        perDown(i);
}

void priorityQueue::perDown(int i)
{
    int child;
    int tmp = dt[i];

    for (; i * 2 <= curSize; i = child)
    {
        child = i * 2;
        if (child != curSize && dt[child] > dt[child+1])
        //最大化堆应该修改为
        //if （child != curSize && dt[child] < dt[child+1]
            child++;
        if (dt[child] < tmp) dt[i] = dt[child];
        //最大化堆应该修改为
        //if (dt[child] > tmp)
        else break;
    }
    dt[i] = tmp;
}

int priorityQueue::pop()
{
    int tmp = dt[1];
    dt[1] = dt[curSize--];
    perDown(1);
    return tmp;
}

void priorityQueue::push(int d)
{
    if (curSize == maxSize - 1) doubleSpace();

    int hole = ++curSize;

    for (; hole > 1 && d < dt[hole/2]; hole /= 2)
    //最大化堆应该修改为 d > dt[hole/2]

        dt[hole] = dt[hole/2];
    dt[hole] = d;
}

priorityQueue::priorityQueue(int initSize)
{
    dt = new int [initSize];
    maxSize = initSize;
    curSize = 0;
}

priorityQueue::priorityQueue(const int a[], int size)
{
    dt = new int[size];
    for (int i = 0; i < size; i++)
        dt[i+1] = a[i];
    curSize = size;
    maxSize = size * 2;
    buildHeap();
}

//找到大于等于d的最小值下标
int priorityQueue::Find(const int &d)
{
    int min;
    int ID = -1;

    for (int i = 1; i <= curSize; i++)
    {
        if (dt[i] > d && (ID == -1 || min > dt[i]))
        {
            min = dt[i];
            ID = i;
        }
    }

    cout << ID << '\n';
    return ID;
}

//将第i个元素优先值减小x
void priorityQueue::decrease(int i, int x)
{
    int hole;
    
    hole = i;
    dt[hole] -= x;
    int tmp = dt[hole];

    for (; hole > 1 && dt[hole/2] > tmp; hole /= 2)
        dt[hole] = dt[hole/2];
    dt[hole] = tmp;
}

//----------------------------------------三叉表实现最小堆（外加一个合并函数）--------------------------------

//三叉链表实现的最小化堆
class priority_Queue
{
private:
    struct node
    {
        int dt;
        node *parent, *left, *right;
        node (int d, node *p = nullptr, node *l = nullptr, node *r = nullptr)
            :dt(d), parent(p), left(l), right(r){}
        node(): parent(0), left(0), right(nullptr){}
    };

    node *root;
    int size;
public:
    priority_Queue():size(0), root(nullptr){};
    ~priority_Queue(){clear(root);}
    void push(int i);
    int pop();
    int top()const {return root ->dt;}
    bool empty()const {return root == nullptr;}
    void merge(priority_Queue &other);//合并两个等高的满二叉堆

private:
    node* merge(node * &t1, node *& t2)
    {
        node *p;
        if (t1 ->dt < t2 ->dt)
        {
            if (t1 ->left != nullptr)
            {
                p = merge(t1 ->left, t1 ->right);
                t1 ->right = p;
                p ->parent = t1;
            }
            t1 ->left = t2;
            t2 ->parent = t1;
            return t1;
        }
        else
        {
            if (t2 ->left != nullptr)
            {
                p = merge(t2 ->left, t2 ->right);
                t2 ->right = p;
                p ->parent = t2;
            }
            t2 ->right = t1;
            t1 ->parent = t2;
            return t2;
        }
        
    }

    void clear(node *t)
    {
        if (t == nullptr) return;
        clear(t ->left);
        clear(t ->right);
        delete t;        
            
    }

    void perDown(node *t)
    {
        int tmp = t ->dt;
        node *child;

        for (; t ->left != nullptr; t = child)
        {
            child = t ->left;
            if (t ->right != nullptr && t ->right ->dt < t ->left ->dt)
                child = t ->right;
            if (child ->dt < tmp) t ->dt = child ->dt;
            else break;
        }
        t ->dt = tmp;
    }

    node * &find(int i)//返回第i个元素的地址//nb
    {
        if (i == 1) return root;
        if (i % 2) return find(i/2) ->right;
        else return find(i/2) ->left;
    }
};


int priority_Queue::pop()
{
    int result = root ->dt;
    node *tmp = find(size);
    root ->dt = tmp ->dt;
    size--;
    if (tmp == root)//只有一个节点
    {
        delete root;
        root = nullptr;
    }
    else
    {
        (tmp == tmp ->parent ->left) ? tmp ->parent ->left = nullptr: tmp ->parent ->right = nullptr;
        delete tmp;
        perDown(root);
    }

    return result;
}

void priority_Queue::push(int d)
{
    size++;
    if (root == nullptr)
    {
        root = new node(d);
        return;
    }
    node *tmp = find(size/2);
    if (size%2)//新节点位于右子树上
    {
        tmp ->right = new node(d, tmp);
        tmp = tmp ->right;
    }
    else
    {
        tmp ->left = new node(d, tmp);
        tmp = tmp ->left;
    }

    for (; tmp != nullptr && d < tmp ->parent ->dt; tmp = tmp ->parent)
        tmp ->dt = tmp ->parent ->dt;
    tmp ->dt = d;
}

void priority_Queue::merge(priority_Queue &other)
{
    root = merge(root, other.root);
    size *= 2;
    other.root = nullptr;
    other.size = 0;
}


int main()
{
    //
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(0);

    int N, value; char ch[10];
    cin >> N;
    priorityQueue myQue(20004);//上述实现的类
    priority_queue<int, vector<int>, greater<int> > que;//STL中的类模板，注意空格

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

//-----------------------------------------贪婪法算最小背包------------------------------------------
    int n, num = 0;
    int *ar;
    cin >> n;
    ar = new int [n];

    for (int i = 0; i < n; i++)
    {
        cin >> ar[i];
        myQue.push(10);//初始空间全为10
    }

    for (int i = 0; i < n; i ++)//寻找能放下ar[i]的最小容量的背包
    {
        myQue.decrease(myQue.Find(ar[i]), ar[i]);
        while(myQue.top() == 0)//将刚好装满的背包弹出，背包数+1
        {
            num++;
            myQue.pop();
        }
    }
    while(!myQue.empty())
        if (myQue.pop() < 10) num++;

    cout << num << '\n';

    return 0;
}


//===================================================================
//          基于二项堆的优先队列
//===================================================================
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