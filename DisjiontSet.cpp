//===================================
// 并查集及其应用
//===================================

#include <iostream>
using namespace std;

class DisjiontSet
{
private:
    int size;
    int *parent;//双亲表示法
public:
    DisjiontSet(int s = 101);
    ~DisjiontSet(){delete [] parent;}
    void unioN(int root1, int root2);
    int find(int x);
};

DisjiontSet::DisjiontSet(int s)
{
    size = s;
    parent = new int [s];
    for (int i = 0; i < size; i++)
        parent[i] = -1;
}

void DisjiontSet::unioN(int root1, int root2)
{
    if (root1 == root2) return;
    else if(parent[root1] < parent[root2])
    {
        parent[root1] += parent[root2];
        parent[root2] = root1;
    }
    else
    {
        parent[root2] += parent[root1];
        parent[root1] += root2;
    }
}

int DisjiontSet::find(int x)
{
    if (parent[x] < 0) return x;
    else return parent[x] = find(parent[x]);
}


//================================================
// 查找最近公共祖先
//================================================
//二叉树中寻找最近的祖先
//在二叉树中加入下列函数
int LCA(int i, int j)
{
    if (i == j) return i;
    if (i < j) return LCA(i, j/2);
    else return LCA(i/2, j);
}

template<class T>
T LCA(T x, T y)//共有函数，两个接口
{
    int ix, yi, i;
    //查找x的下表
    for (i = 1; i <= size; i++)
        if (array[i] == x) break;
    if (i <= size) xi = i;
    else
    {
        cout << "没有 " << x << '\n';
        return x;
    }

    //查找y元素
    for (i =1; i <= size; i++)
    if (i <= size) yi = i;
    else
    {
        cout << "没有 " << y << endl;
        return y;
    }

    return array[LCA(xi, yi)];
}

//孩子兄弟树中查询最近祖先
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

//递归的lca函数
template<class elem>
elem lCA(node<elem> *t, elem x, bool &xFind, elem y, bool &yFind)
{
    bool xtmp, ytmp;
    node *p;
    elem lca;

    if (t == nullptr)
    {
        xFind = yFind = false;
        return x;
    }

    p = t ->son;
    while(p != nullptr)
    {
        xTmp = yTmp = false;
        lca = lCA(p, x, xtmp, y, ytmp);
        if(xtmp && ytmp)
        {
            xFind = yFind = true;
            return lca;
        }
        if (xtmp) xFind = true;
        if (ytmp) yFind = true;
        p = p ->brother;
    }

    if (t ->dt == x) xFind = true;
    if (t ->dt == y) yFind = true;
    return t ->dt;
}

template<class T>
T lCA(T x, T y)
{
    bool xfind = false, yFind = false;
    return lCA(root, x, xfind, y, yFind);
}