#include <iostream>
using namespace std;

template<class Type>
class assemble
{
    friend assemble<Type> operator+(assemble<Type> &a, assemble<Type> &b);
    friend assemble<Type> operator-(assemble<Type> &a, assemble<Type> &b);
    friend assemble<Type> operator*(assemble<Type> &a, assemble<Type> &b);

private:
    Type *dt;
    int curSize;
    int maxSize;
    void doubleSpace();
public:
    assemble(int size = 10);
    ~assemble(){delete [] dt;}
    void insert(const Type &d);
    void find(const Type &d);
    void remove(const Type &d);
};

template<class Type>
assemble<Type>::assemble(int size)
{
    dt = new Type[size];
    curSize = 0;
    maxSize = size;
}

template <class Type>
void assemble<Type>::remove(const Type &d)
{
    int i = find(d);
    if (i == 0) return;
    int j = i;
    for (j; j < curSize; j++)
        dt[j] = dt[j+1];
    curSize--;
}

template<class Type>
void assemble<Type>::insert(const Type &d)
{
    if (curSize == maxSize -1) doubleSpace();
    dt[++curSize] = d;//从1开始放元素
}

template<class Type>
void assemble<Type>::find(const Type &d)
{
    int i;
    dt[0] = d;
    for(i = curSize; d != dt[i]; i--);
    return i;
}

template<class Type>
assemble<Type> operator+(assemble<Type> &a, assemble<Type> &b)
{
    assemble<Type> tmp(a.maxSize + b.maxSize);
    for (int i = 1; i <= a.curSize; i++)
        tmp.insert(a.dt[i]);
    for (int i = 1; i <= b.curSize; i++)
        tmp.insert(b.dt[i]);
    return tmp;
}

template<class Type>
assemble<Type> operator*(assemble<Type> &a, assemble<Type> &b)
{
    assemble<Type> tmp(a.maxSize + b.maxSize);
    int i = 1;
    for (int j = 1; j < a.curSize; j++)
    {
        if (!tmp.find(a.dt[j]))
            tmp.insert(a.dt[j]);
    }

    for (int j = 1; j < b.curSize; j++)
    {
        if (!tmp.find(b.dt[j]))
            tmp.insert(b.dt[j]);
    }

    return tmp;
}

template<class Type>
assemble<Type> operator-(assemble<Type> &a, assemble<Type> &b)
{
    int k, j = b.curSize;
    while(j > 0 && a.curSize > 0)
    {
        if (k = a.find(b.dt[j]))
        {
            for(int m = k; m < a.curSize; m++)
                a.dt[m] = a.dt[m+1];
            a.curSize--;
        }

        j--;
    }
}
