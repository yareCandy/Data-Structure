//AVLTree.cpp
//AVL树的实现
//AVL树 特点：
//在查找二叉树的基础上努力构建出的一棵平衡树
//要求左右子树的高度差小于等于1，用平衡因子表示节点的平衡度
//平衡度只有三种情况：0（高度相等） 1（左子树高度比有节点大1） -1（右比左大1）
//性能分析：
//定理：一棵节点数为N的AVL树，高度小于等于 1.44log(N+1) - 0.328 （推倒过程利用斐波拉切数列）
//这使得AVL树在最坏的情况下依然可以以log(N)的复杂度工作

#include <iostream>
#include <cstring>
using namespace std;

template<class KEY, class OTHER>
struct SET
{
    KEY key;
    OTHER other;
};

template <class KEY, class OTHER>
class AvlTree
{
    struct AvlNode
    {
        SET<KEY, OTHER> dt;
        AvlNode *left, *right;
        int height;//保存当前节点高度

        AvlNode(const SET<KEY, OTHER> &d, AvlNode *l = nullptr, AvlNode *r = nullptr)
            :dt(d), left(l), right(r){}
        AvlNode():left(nullptr), right(nullptr){}
    };

    AvlNode *root;

public:
    AvlTree():root(nullptr){}
    ~AvlTree(){clear(root);}
    SET<KEY, OTHER> *find(const KEY &d)const;
    void insert(const SET<KEY, OTHER> &d);
    void remove(const KEY &d);

private:
    void insert(const SET<KEY, OTHER> &d, AvlNode * &t);
    bool remove(const KEY &d, AvlNode * &t);
    void clear(AvlNode *t);//为什么不用引用
    int height(AvlNode *t)const {return t == nullptr ? 0 : t ->height;}
    void LL(AvlNode * &t);//左子树的左孩子插入导致失衡 //指针的引用，确保所有操作在原地址进行
    void RR(AvlNode * &t);//右子树的右孩子上插入导致失衡
    void LR(AvlNode * &t);//左子树的右孩子上插入导致失衡
    void RL(AvlNode * &t);//右子树的左孩子上插入导致失衡
    int max(int a, int b){return a > b ? a : b;}
    bool adjust(AvlNode * &t, int subTree);
};


template<class KEY, class OTHER>
SET<KEY, OTHER> *AvlTree<KEY, OTHER>::find(const KEY &d)const
{
    AvlNode *t = root;

    while (t != nullptr && t ->dt.key != d)
    {
        if (t ->dt.key < d) t = t ->right;
        else t = t ->left;
    }
    if (t == nullptr) return nullptr;
    else return (SET<KEY, OTHER> *) t;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &d)
{
    inert(d, root);
}

//私有插入函数
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &d, AvlNode * &t)
{
    if (t == nullptr) t = new AvlNode(d);
    else if (d.key < t ->dt.key)
    {
        insert(d, t ->left);//z左子树插入
        if (height(t ->left) - height(t ->right) == 2) //失衡
        {
            if (d.key < t ->left ->dt.key) LL(t);//LL型失衡
            else LR(t);//LR型失衡
        }
    }
    else if (d.key > t ->dt.key)
    {
        insert(d, t ->right);
        if (height(t ->right) - height(t ->left) == 2)
        {
            if (d.key < t ->left ->dt.key) RL(t);//RL型失衡
            else RR(t);
        }
    }

    //更新高度
    t ->height = max(t ->left, t ->right) + 1;
}


template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LL(AvlNode *&t)
{
    AvlNode *t1 = t ->left;
    t ->left = t1 ->left;
    t1 ->right = t;
    t ->height = max(height(t ->left), height(t ->right)) + 1;
    t1 ->height = max(height(t1 ->left), height(t1 ->right)) + 1;
    t = t1;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RR(AvlNode *&t)
{
    AvlNode *t1 = t ->right;
    t ->right = t1 ->right;
    t1 ->left = t;
    t ->height = max(height(t ->left), height(t ->right)) + 1;
    t1 ->height = max(height(t1 ->left), height(t1 ->right)) + 1;
    t = t1;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LR(AvlNode *&t)
{
    RR(t ->left);
    LL(t);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RL(AvlNode *&t)
{
    LL(t ->right);
    RR(t);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::clear(AvlNode *t)
{
    if (t == nullptr) return;
    
    clear(t ->left);
    clear(t ->right);
    delete t;
}


template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::remove(const KEY &d)
{
    remove(d, root);
}

template<class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::remove(const KEY &d, AvlNode *&t)
{
    if (t == nullptr) return;
    if (d == t ->dt.key)
    {
        if (t ->left == nulptr || t ->right == nullptr)
        {
            AvlNode *oldNode = t;
            t = (t ->left != nullptr) ? t ->left : t ->right;
            delete oldNode;
            return false;
        }
        else
        {
            AvlNode *tmp = t ->right;
            while (tmp ->left != nullptr) tmp = tmp ->left;
            t ->dt = tmp ->dt;
            if (remove(tmp ->dt.key, t ->right))) return true;
            return adjust(t, 1);
        }
    }

    if (d < t ->dt.key)
    {
        if (remove(d, t ->left)) return true;
        return adjust(t, 0);
    }
    else
    {
        if (remove(x, t ->right)) return true;
        return adjust(t, 1);
    }
}

template<class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::adjust(AvlNode *&t, int subTree)
{
    if (subTree) 
    {
        if (height(t ->left) - height(t ->right) == 1) return ture;
        if (height(t ->rihgt) == height(t ->left))
        {
            --t ->height; return false;
        }
        if (height(t ->left ->right) > height(t ->left ->right))
        {
            LR(t); return false;
        }
        LL(t);
        if (height(t ->right) == height(t ->left)) return false;
        else return true;
    }
    else
    {
        if (height(t ->left) - height(t ->right) == -1) return ture;
        if (height(t ->rihgt) == height(t ->left))
        {
            --t ->height; return false;
        }
        if (height(t ->right ->right) < height(t ->right ->left))
        {
            RL(t); return false;
        }
        RR(t);
        if (height(t ->right) == height(t ->left)) return false;
        else return true;
    }
       
}

