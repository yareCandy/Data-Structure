//红黑树
//1、每个节点被染成黑色或者红色
//2、根节点是黑色
//3、如果任何一个节点是红色，那它的儿子一定是黑色
//4、从任何一个节点出发走到空节点（默认空节点为黑色节点）必须包含相同数目的黑色节点


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
class RedBlackTree
{
    struct redBlackNode
    {
        enum Color{RED, BLACK};

        SET<KEY, OTHER> dt;
        redBlackNode *left, *right;
        Color color;//保存当前节点高度

        redBlackNode(const SET<KEY, OTHER> &d, redBlackNode *l = nullptr, redBlackNode *r = nullptr, Color c = RED)
            :dt(d), left(l), right(r), color(c){}
        redBlackNode():left(nullptr), right(nullptr){}
    };

    redBlackNode *root;

public:
    RedBlackTree(redBlackNode *t = nullptr):root(t){}
    ~RedBlackTree(){clear(root);}
    SET<KEY, OTHER> *find(const KEY &d)const;
    void insert(const SET<KEY, OTHER> &d);
    void remove(const KEY &d);

private:
    void removeAdjust(redBlackNode *&p, redBlackNode *&c, redBlackNode *&t, KEY &del);
    void clear(redBlackNode *t);
    void LL(redBlackNode * &t);//左子树的左孩子插入导致失衡 //指针的引用，确保所有操作在原地址进行
    void RR(redBlackNode * &t);//右子树的右孩子上插入导致失衡
    void LR(redBlackNode * &t);//左子树的右孩子上插入导致失衡
    void RL(redBlackNode * &t);//右子树的左孩子上插入导致失衡
    void adjust(redBlackNode *gp, redBlackNode *p, redBlackNode *t);
};

template <class KEY,class OTHER>
SET<KEY, OTHER> *RedBlackTree<KEY, OTHER>::find(const KEY & d)const
{
    redBlackNode *t = root;
    while(t != nullptr && t ->dt.key != d)
        if (t ->dt.key > x) t = t ->left;
        else t = t ->right;

    if (t = nullptr) return nullptr;
    else return (SET<KEY, OTHER> *) t;  
}

template<class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::clear(redBlackNode * t)
{
    if (t == nullptr) return;
    clear(t ->left);
    clear(t ->right);
    delete t;
}

template<class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &d)
{
    if (roott == nullptr)
    {
        root = new redBlackNode(d, nullptr, nullptr, BLACK);
        return;
    }

    redBlackNode *t, *parent, *grandP;

    parent = grand = t = root;
    while(true)
    {
        if (t)
        {
            if (t ->left && t ->left ->color == RED && t ->right && t ->right ->color == RED)
            {
                t ->left ->color = t ->right ->color = BLACK;
                t ->color = RED;
                adjust(grandP, parent, t);
            }
            grandP = parent;
            parent = t;
            t = (t ->dt.key > d.key ? t ->left : t ->right);
        }
        else
        {
            t = new redBlackNode(d);
            if (d.key < parent ->dt.key) parent ->left = t;
            else parent ->right = t;
            adjust(grandP, parent, t);
            root ->color = BLACK;
            return;
        }
        
    }
}


template<class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::adjust(redBlackNode *gp, redBlackNode *p, redBlackNode *t)
{
    if (p ->color) return;\
    if (p == root)
    {
        p ->color = BLACK;
        return;
    }
    if(gp ->left == p)
    {
        if (p ->left == t) LL(gp);
        else LR(gp);
    }
    else if(p ->right == t) RR(gp);
    else RL(gp);
}

template<class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::LL(redBlackNode *&gp)
{
    //为什么不用AvlTree中的旋转方法
    redBlackNode *p = gp ->left, *t = p ->left;
    redBlackNode tmp = *gp;
    gp ->dt = p ->dt;
    gp ->left = t;
    gp ->right = p;
    p ->dt = tmp.dt;
    p ->left = p ->right;
    p ->right = tmp.right;
}

template<class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::RR(redBlackNode *&t)
{
    redBlackNode *p = t ->right;
    redBlackNode *cur = p ->right;
    redBlackNode tmp = *t;
    gp ->dt = p ->dt;
    gp ->right = t;
    gp ->left = p;
    p ->dt = tmp.dt;
    p ->right = p ->left;
    p ->left = tmp.left;
}

template<class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::LR(redBlackNode *&gp)
{
    redBlackNode *p = gp ->left, *t = p ->right;
    redBlackNode tmp = *gp;
    gp ->dt = t ->dt;
    gp ->right = t;
    p ->right = t ->left;
    t ->dt = tmp.dt;
    t ->left = t ->right;
    t ->right = tmp.right;
}

template<class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::RL(redBlackNode *&gp)
{
    redBlackNode *p = gp ->right, *t = p ->left;
    redBlackNode tmp = *gp;
    gp ->dt = t ->dt;
    gp ->left = t;
    p ->left = t ->right;
    t ->dt = tmp.dt;
    t ->right = t ->left;
    t ->left = tmp.left;
}

template<class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::remove(const KEY &d)
{
    KEY del = x;
    redBlackNode *t, *p, *c;

    if (root == nullptr) return;
    if (root ->dt.key == x && root ->left = nullptr && root ->right == nullptr)
    {
        delete root;
        root = nullptr;
        return;
    }

    p = c = t = root;
    while(true)
    {
        removeAdjust(p, c, t, del);
        if (c ->dt.key == del && c ->left && c ->right)
        {
            redBlackNode *tmp = c ->right;
            while(tmp ->left) tmp = tmp ->left;
            c ->dt = tmp ->dt;
            del = tmp ->dt.key;
            p = c;
            c = c ->right;
            t = p ->left;
            continue;
        }

        if (c ->dt.key == del)
        {
            delete c;
            if (p ->left == c) p ->left == nullptr;
            else p ->right = nullptr;
            root ->color = BLACK;
            return; 
        }
        p = c;
        c = (del < p ->dt.key ? p ->left : p ->right);
        t = (c == p ->left ? p ->right : p ->left);

    }
}

template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::removeAdjust(redBlackNode *&p, redBlackNode *&c, redBlackNode *&t, KEY &del)
{
    if (c ->color == RED) return;
    if (c == root)
    {
        if (c ->left && c ->right && c ->right ->color == c ->left ->color)
        {
            c ->color = RED;
            c ->left ->color = c ->right ->color = BLACK;
            return;
        }
    }

    if (((c ->left && c ->left ->color) || c ->left == nullptr)
        && ((c ->right && c ->right ->color) || c ->right == nullptr))
    {
        if (((t ->left && t ->left ->color) || t ->left == nullptr)
            && ((t ->right && t ->right ->color) || t ->right == nullptr))
        {
            p ->color = BLACK;
            t ->color = c ->color = RED;
        }
        else
        {
            if (p ->left == t)
            {
                if (t ->left && t ->left ->color == RED)
                {
                    t ->left ->color = BLACK;
                    LL(p);
                    p = t;
                }
                else
                {
                    LR(t);
                    p = p ->right;
                    p ->color = BLACK;
                }
            }
            else if (t ->right && t ->right ->color == RED)
            {
                t ->right ->color = BLACK;
                RR(t);
                p = t;
            }
            else
            {
                RL(p);
                p = p ->left;
                p ->color = BLACK;
            }
            
        } 
        c ->color = RED;
    }
    else
    {
        if (c ->dt.key == del)
        {
            if (c ->left && c ->right)
            {
                if (c ->right ->color == BLACK)
                {
                    LL(c);
                    c = c ->right;
                }
                return;
            }
            if (c ->left)
            {
                LL(c);
                p = c;
                c = c ->right;
            }
            else
            {
                RR(c);
                p = c;
                c = c ->left;
            }
        }
        else
        {
            p = c;
            c = (del < p ->dt.key ? p ->left : p ->right);
            t = (c == p ->left ? p ->right : p ->left);
            if (c ->color == BLACK)
            {
                if (t == p ->right) RR(p);
                else LL(p);
                p = t;
                t = (c == p ->left ? p ->right : p ->left);
                removeAdjust(p, c, t, del);
            }
        }
    }
}

int main()
{
    RedBlackTree<int, int> tree;
    SET<int, int> *tmp;
    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        
    }
    
    return 0;
}