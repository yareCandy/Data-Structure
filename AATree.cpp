//AATree.cpp
//对红黑树加了限制：左儿子不能为红色
//用层次的概念代替颜色，层次：到空节点路径上的左链数

#include <iostream>
using namespace std;

template<class KEY, class OTHER>
struct SET
{
    KEY key;
    OTHER other;
};

template <class KEY, class OTHER>
class AATree
{
    struct AANode
    {
        SET<KEY, OTHER> dt;
        int level;
        AANode *left, *right;

        AANode(const SET<KEY, OTHER> &d, int le = 1, AANode *l = nullptr, AANode *r = nullptr)
            :dt(d), level(le), left(l), right(r){}
        AANode():left(nullptr), right(nullptr){}
    };

    AANode *root;

public:
    AATree(AANode *t = nullptr):root(t){}
    ~AATree(){clear(root);}
    SET<KEY, OTHER> *find(const KEY &d)const;
    void insert(const SET<KEY, OTHER> &d){insert(d, root);}
    void remove(const KEY &d);

private:
    void remove(const KEY &d, AANode *&t);
    void insert(const SET<KEY, OTHER> &d, AANode *&t);
    void clear(AANode *t);
    void LL(AANode * &t);//左子树的左孩子插入导致失衡 //指针的引用，确保所有操作在原地址进行
    void RR(AANode * &t);//右子树的右孩子上插入导致失衡
    int min(int a, int b){return a > b ? b : a;}
};

template <class KEY,class OTHER>
SET<KEY, OTHER> *AATree<KEY, OTHER>::find(const KEY & d)const
{
    AANode *t = root;
    while(t != nullptr && t ->dt.key != d)
        if (t ->dt.key > d) t = t ->left;
        else t = t ->right;

    if (t == nullptr) return nullptr;
    else return (SET<KEY, OTHER> *) t;  
}

template<class KEY, class OTHER>
void AATree<KEY, OTHER>::clear(AANode * t)
{
    if (t == nullptr) return;
    clear(t ->left);
    clear(t ->right);
    delete t;
}

template<class KEY, class OTHER>
void AATree<KEY, OTHER>::LL(AANode *&t)
{
    //为什么不用AvlTree中的旋转方法
    if (t ->left != nullptr && t ->left ->level == t ->level)
    {
        AANode *t1 = t ->left;
        t ->left = t1 ->right;
        t1 ->right = t;
        t = t1;
    }
}

template<class KEY, class OTHER>
void AATree<KEY, OTHER>::RR(AANode *&t)
{
    if (t ->right != nullptr && t ->right ->right != nullptr
        && t ->right ->right ->level == t ->level)
    {
        AANode *t1 = t ->right;
        t ->right = t1 ->left;
        t1 ->left = t;
        t = t1;
        t ->level++;
    }
}

template<class KEY, class OTHER>
void AATree<KEY, OTHER>::insert(const SET<KEY, OTHER> &d, AANode *&t)
{
    if (t == nullptr)
        t = new AANode(d);
    else
    {
        if (d.key < t->dt.key) insert(d, t ->left);
        else if (d.key > t ->dt.key) insert(d, t ->right);
        else return;
    }

    LL(t);
    RR(t);    
}

template <class KEY, class OTHER>
void AATree<KEY, OTHER>::remove(const KEY &d)
{
    remove(d, root);
}

template <class KEY, class OTHER>
void AATree<KEY, OTHER>::remove(const KEY &d, AANode *&t)
{
    if (t == nullptr) return;
    if (d < t ->dt.key) remove(d, t ->left);
    else if (d > t ->dt.key) remove(d, t ->right);
    else if (t ->left != nullptr && t ->right != nullptr)
    {
        AANode *tmp = t ->right;
        while (tmp ->left != nullptr) tmp = tmp ->left;
        t ->dt = tmp ->dt;
        remove(t ->dt.key, t ->right);
    }
    else
    {
        AANode *tmp = t;
        t = (t ->left == nullptr) ? t ->right : t ->left;
        delete tmp;
        return;
    }

    //修改父节点的层次并调整
    if (t ->left == nullptr || t ->right == nullptr) t ->level = 1;
    else t ->level = min(t ->left.level, t ->right.level) + 1;
    if (t ->right != nullptr && t ->right ->level > t ->level)
        t ->right ->level = t ->level;
    LL(t);
    if (t ->right != nullptr) LL(t ->right);
    if (t ->right != nullptr && t ->right ->right != nullptr) 
        LL(t ->right ->right);
    RR(t);
    if (t ->right != nullptr) RR(t ->right);
}

int main()
{
    AATree<int, int> tree;
    SET<int, int> tmp, a[10];
    for (int i = 0; i < 10; i++)
    {
        a[i].key = i;
        a[i].other = i;
        tree.insert(a[i]);
    }
    tmp = *(tree.find(9));
    cout << tmp.key << endl;

    return 0;
}