//hf.cpp
//哈夫曼树的定义及实现

#include <iostream>
using namespace std;

template<class Type>
class hfTree
{
private:
    struct node
    {
        Type dt;
        int weight;
        int parent, left, right;
    };

    node *dt;
    int length;

public:
    struct hfCode
    {
        Type dt;
        string code;
    };

    hfTree(const Type *x, const int *w, int size);
    void getCode(hfCode result[]);//从哈夫曼树生成哈夫曼编码
    ~hfTree(){delete [] root;}
};

template<class Type>
hfTree<Type>::hfTree(const Type *x, const int *w, int size)
{
    const int MAX = 32767;
    int min1, min2;//最小和次小的权值
    int X, y;//最小和次小的下标

    //置初值
    length = 2 * size;
    dt = new node[length];

    for (int i = size; i < length; i++)
    {
        dt[i].weight = w[i - size];
        dt[i].dt = v[i - size];
        dt[i].parent = dt[i].left = dt[i].right = 0;
    }

    //归并森林的树
    for (i = size - 1; i > 0; i--)
    {
        min1 = min2 = MAX;
        x = y = 0;
        for (int j = i + 1; j < length; j++)
            if (dt[j].parent == 0)
                if (dt[j].weight < min1)
                {
                    min2 = min1;
                    min1 = dt[j].weight;
                    x = y;
                    y = j;
                }
                else if (dt[j].weight < min2)
                {
                    min2 = dt[j].weight;
                    x = j;
                }
        dt[i].weight = min1 + min2;
        dt[i].left = x;
        dt[i].right = y;
        dt[i].parent = 0;
        dt[x].parent = i;
        dt[y].parent = i;
    }
}

template <class Type>
void hfTree<Type>::getCode(hfCode result[])
{
    int size = length / 2;
    int p,s;

    for (int i = size; i < length; i++)
    {
        result[i - size].dt = dt[i].dt;
        result[i - size].code = " ";
        p = dt[i].parent;
        s = i;
        while(p)
        {
            if (dt[p].left == s)
                result[i - size].code = '0' + result[i - size].code;
            else result[i - size].code = '1' + result[i - size].code;

            s = p;
            p = dt[p].parent;
        }
    }
}

int main()
{
    char ch[] = {"aeistdn"};
    int w[] = {10, 15, 12, 3, 4, 13, 1};
    hfTree<char> tree(ch, w, 7);
    hfTree<char>::hfCode result[7];

    tree.getCode(result);

    for (int i = 0; i < 7; i++)
        cout << result[i].dt << " " << result[i].code << '\n';
    
    return 0;
}