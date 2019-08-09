//============================================
//基于线性探测的闭散列表
//============================================
#include <iostream>
using namespace std;

template<class KEY, class OTHER>
struct SET
{
    KEY key;
    OTHER other;
};


template<class KEY, class OTHER>
class closeHashTable
{
private:
    struct node{
        SET<KEY, OTHER> dt;
        int state;//0 --空， 1 --在， 2 --已删除
        node() {state = 0;}
    };

    node *array;
    int size;
    int (*key)(const KEY &x);
    static int defaultKey(const int &x){return x;}

public:
    closeHashTable(int length = 10, int (*f)(const KEY &x) = defaultKey);
    ~closeHashTable(){delete [] array;}
    SET<KEY, OTHER> *find(const KEY &x)const;
    void insert(const SET<KEY, OTHER> &x);
    void remove(const KEY &x);
};

template<class KEY, class OTHER>
closeHashTable<KEY, OTHER>::closeHashTable(int length, int (*f)(const KEY &x))
{
    size = length;
    array = new node[size];
    key = f;
}

template<class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::insert(const SET<KEY, OTHER> &x)
{
    int initPos, pos;
    initPos = pos = key(x.key) % size;
    do{
        if (array[pos].state != 1){
            array[pos].dt = x;
            array[pos].state = 1;
            return;
        }
        pos = (pos + 1) % size;
    }while(pos != initPos);

}

template<class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::remove(const KEY &x)
{
    int initPos, pos;
    initPos = pos = key(x.key)%size;

    do{
        if (array[pos].state == 0)return;
        if (array[pos].state == 1 && array[pos].dt.key == x){
            array[pos].state = 2;
            return;
        }
        pos = (pos+1) % size;
    }while(pos != initPos);
}

template<class KEY, class OTHER>
SET<KEY, OTHER> *closeHashTable<KEY, OTHER>::find(const KEY &x)const
{
    int initPos, pos;

    initPos = pos = key(x.key) % size;
    do{
        if (array[pos].state == 0) return nullptr;
        if (array[pos].state == 1 && array[pos].dt.key == x)
            return (SET<KEY, OTHER> *) &array[pos];
        pos = (pos + 1) % size;
    }while(pos != initPos);
}

//找大于指定元素的最小素数
bool isPrimer(int n)
{
    if (n == 2 || n ==3 ) return true;
    if (n == 1 || n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0) return false;
    }
    return true;
}

int nextPrimer(int n)
{
    if (n % 2 == 0) n++;
    while (! isPrimer(n)) n += 2;
    return n;
}

void doubleSpace()
{
    int *tmp = array;
    int oldSize = size;
    size = nextPrimer(oldSize*2);
    load = 0;

    array = new int [size];
    for (int i = 0; i < oldSize; i++)
        if (tmp[i].state == 1) 
            insert(tmp[i].dt);
    delete [] tmp;
}

//======================================================
//开散列表
//======================================================
template<class KEY, class OTHER>
class openHashTable
{
private:
    struct node{
        SET<KEY, OTHER> dt;
        node *next;
        node(const SET<KEY, OTHER> &d, node *n = nullptr)
            :dt(d), next(n){}
        node(){next = nullptr;}
    };

    node **array;
    int size;
    int (*key)(const KEY &x);
    static int defaultKey(const int &x){return x;}
public:
    openHashTable(int length = 101, int (*key)(const KEY &x) = defaultKey);
    ~openHashTable();
    SET<KEY, OTHER> *find(const KEY &x)const;
    void insert(const SET<KEY, OTHER> &x);
    void remove(const KEY &x);
};

template<class KEY, class OTHER>
openHashTable<KEY, OTHER>::openHashTable(int le, int (*f)(const KEY &x))
{
    size = le;
    array = new node *[size];
    key = f;
    for (int i = 0; i < size; i++)
        array[i] = nullptr;
}

template<class KEY, class OTHER>
openHashTable<KEY, OTHER>::~openHashTable()
{
    node *p, *q;
    for (int i = 0; i <size; i++)
    {
        p = array[i];
        while (p != nullptr){q = p ->next; delete p; p = q;}
    }

    delete [] array;
}

template<class KEY, class OTHER>
void openHashTable<KEY, OTHER>::insert(const SET<KEY, OTHER> &x)
{
    int pos;
    node *p;
    pos = key(x.key) % size;
    array[pos] = new ndoe(x, array[pos]);
}

template<class KEY, class OTHER>
void openHashTable<KEY, OTHER>::remove(const KEY &x)
{
    int pos;
    node *p, *q;

    pos = key(x) % size;
    if (array[pos] == nullptr) return;
    p = array[i];
    if (array[pos] ->dt.key == x){
        array[pos] = p ->next;
        delete p;
        return;
    }

    while (p ->next != nullptr && p ->next ->dt.key != x)
        p = p ->next;
    if (p ->next != nullptr){
        q = p ->next;
        p ->next = q ->next;
        delete q;
    }
}

template<class KEY, class OTHER>
SET<KEY, OTHER> *openHashTable<KEY, OTHER>::find(const KEY &x)const
{
    int pos;
    ndoe *p;

    pos = key(x) % size;
    p = array[pos];
    while(p != nullptr && p ->dt.key != x) p = p ->next;
    if (p == nullptr) return nullptr;
    else return (SET<KEY, OTHER> *) p;
}

//===============================================
//STL的应用
//===============================================
#include <set>
#include <map>

int main()
{
    set<int> s;
    set<int>::iterator p;//set的迭代器
    for (int i =0; i <10; i++)
        s.insert(i);
    for (p = s.begin(); p != s.end(); p++)
        cout << *p << endl;
    s.erase(9);

    map<int, string> m;
    map<int, string>::iterator q;//map的迭代器
    string a[] = {"aa", "bb", "cc", "dd"};

    for (int i = 0; i < 4; i++)
        m.insert(pair<int, string>(i, a[i]));
    for (q = m.begin(); q != m.end(); q++)
        cout << q ->first << "\t" << q ->second << " ";
    cout << endl;
    q = m.find(3);

    s.erase(3);

    return 0;
}

