//binarySearchTree.cpp
//二叉查找树
//定义：
//要么树为空，要么左子树和右子树均是二叉查找树
//指针的引用：就是指针变量的别名，与被引用的指针处于同一个地址

#include <iostream>
using namespace std;

template<class KEY, class VALUE>
struct SET
{
    KEY key;
    VALUE value;
};

template<class KEY, class VALUE>
class binarySearchTree
{
private:
    struct node
    {
        SET<KEY, VALUE> dt;
        node *left;
        node *right;
        node (const SET<KEY, VALUE> &d, node *l = nullptr, node *r = nullptr)
            :dt(d), left(l), right(r){}
        node ():left(nullptr), right(nullptr){}
    };

    node *root;
public:
    binarySearchTree(){root = nullptr;}//构造函数
    ~binarySearchTree(){clear(root);}//析构函数
    SET<KEY, VALUE> *find(const KEY &d)const;
    void insert(const SET<KEY, VALUE> &d);
    void remove(const KEY &d);
    bool isBSTree()const;
    bool isBSTree(node *t, int &min, int &max)const;
    void searchK(int i){searchK(i, root);};
    void searchK(int &i, node *t);
    void midOrder(){midOrder(root);}
    void midOrder(node *t);
private:
    void insert(const SET<KEY, VALUE> &d, node * &t);
    void remove(const KEY &d, node *&t);
    SET<KEY, VALUE> *find(const KEY &d, node *t)const;
    void clear(node *t);
};

template<class KEY, class VALUE>
void binarySearchTree<KEY, VALUE>::midOrder(node *t)
{
    if (t == nullptr) return;
    midOrder(t ->left);
    cout << t ->dt.key << " ";
    midOrder(t ->right);
}

template<class KEY, class VALUE>
void binarySearchTree<KEY, VALUE>::searchK(int &i, node *t)
{
    if (t == nullptr) return;
    searchK(i, t ->left);
    if (--i == 0) {cout << t ->dt.key << endl; return;}
    searchK(i, t ->right);
}

template<class KEY, class VALUE>
SET<KEY, VALUE> *binarySearchTree<KEY, VALUE>::find(const KEY &d)const
{
    return find(d, root);
}

template<class KEY, class VALUE>
SET<KEY, VALUE> *binarySearchTree<KEY, VALUE>::find(const KEY &d, node *t)const
{
    if (t == nullptr || t ->dt.key == d)
        return (SET<KEY, VALUE> *) t;
    if (d < t ->dt.key)
        return find(d, t ->left);
    else
        return find(d, t ->right);
}


template<class KEY, class VALUE>
void binarySearchTree<KEY, VALUE>::insert(const SET<KEY, VALUE> &d)
{
    insert(d, root);
}

//插入，使用指针引用的好处：
//形参和实参指向同一块地址，保证其父节点时指向当前节点的
template<class KEY, class VALUE>
void binarySearchTree<KEY, VALUE>::insert(const SET<KEY, VALUE> &d, node * &t)
{
    if (t == nullptr)
        t = new node(d, nullptr, nullptr);
    else if (d.key < t ->dt.key)
        insert(d, t ->left);
    else if (t ->dt.key < d.key)
        insert(d, t ->right);
}


template<class KEY, class VALUE>
void binarySearchTree<KEY, VALUE>::remove(const KEY &d)
{
    remove(d, root);
}

//删除节点的操作，思想如下：
//若被删节点是叶节点或者只有一个孩子时，直接将被删节点的孩子代替被删节点即可
//若被删节点有两个孩子，根据查找树的特点，有两种方法：
//1.找到左子树中的最大值代替被删节点
//2.找到右子树的最小值代替根节点
template<class KEY, class VALUE>
void binarySearchTree<KEY, VALUE>::remove(const KEY &d, node *&t)
{
    if (t == nullptr) return;

    if (t ->dt.key < d) remove(d, t ->right);
    else if (t ->dt.key > d) remove (d, t ->left);
    else if (t ->left != nullptr && t ->right != nullptr)//有两个孩子时
    {
        //用右子树的最小值代替被删节点
        node *tmp = t ->right;//进入右子树
        while (tmp ->left != nullptr) tmp = tmp ->left;//寻找最小值
        t ->dt = tmp ->dt;
        remove(t ->dt.key, t ->right);//不能直接将最小值节点删除，因为其可能有右孩子
    }
    else//叶节点或者只有一个孩子
    {
        node *tmp = t;
        t = (t ->left != nullptr) ? t ->left : t ->right;
        delete tmp;
    }
}


template<class KEY, class VALUE>
bool binarySearchTree<KEY, VALUE>::isBSTree()const
{
    if (root == nullptr) return true;
    bool flag;
    KEY min, max;

    if (root ->left != nullptr)
    {
        flag = isBSTree(root ->left, min, max);
        if (!flag || max > root ->dt.key) return false;
    }
    if (root ->right != nullptr)
    {
        flag = isBSTree(root ->right, min, max);
        if(!flag || min < root ->dt.key) return false;
    }

    return true;
}

template<class KEY, class VALUE>
bool binarySearchTree<KEY, VALUE>::isBSTree(node *t, int &min, int &max)const
{  
    KEY mint, maxt;
    bool flag;

    if (t ->left)
    {
        flag = isBSTree(t ->left, min, maxt);
        if(!flag || maxt > t ->dt.key) return false;
    }
    if (t ->right)
    {
        flag = isBSTree(t ->right, mint, max);
        if (!flag || mint < t ->dt.key) return false;
    }

    else max = t ->dt;
    return true;
}

template<class KEY, class VALUE>
void binarySearchTree<KEY, VALUE>::clear(node *t)
{
    if (t == nullptr) return;

    clear(t ->left);
    clear(t ->right);
    delete t;
}

int main()
{
    SET<int, int> a[10];
    binarySearchTree<int,int> tree;

    for (int i = 0; i < 10; i++)
    {
        a[i].key = i;
        a[i].value = i;
        tree.insert(a[i]);
    }

    tree.searchK(8);

    return 0;
}