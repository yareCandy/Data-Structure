//doubleStack.cpp
//建立一个双栈，实现将两个栈存储在一个一维数组中

#include <iostream>
using namespace std;

template <class T>
class doubleStack
{
    private:
        T *data;//栈底
        int top_p, bottom, size;
        void DoubleSpace();
    public:
        doubleStack(int initSize = 10);
        ~doubleStack();
        void push(int pos, const T &d);//将d压入pos栈中
        T top(int pos)const;//返回pos的栈顶
        T pop(int pos);//弹出pos的栈顶元素
        bool isEmpty(int pos)const;//判断pos是否为空
};

template <class T>
doubleStack<T> :: doubleStack(int initSize)
{
    if (initSize <= 0)
    {
        cout << "Error" << endl;
        return;
    }

    data = new T [initSize];
    top_p = -1;
    size = initSize;
    bottom = size;
}

template <class T>
doubleStack<T> :: ~doubleStack()
{
    delete [] data;
}

template <class T>
T doubleStack<T> :: pop(int pos)
{
    if (pos == 0)
    {
        if (top_p != -1)
            return data[top_p--];
    }
    if (pos == 1)
    {
        if (bottom != size -1)
            return data[bottom++];
    }
}

template <class T>
void doubleStack<T> :: push(int pos, const T &d)
{
    if (top_p + 1 == bottom)
        DoubleSpace();
    if (pos == 0)
        data[++top_p] = d;
    else
        data[--bottom] = d;
}

template <class T>
T doubleStack<T> :: top(int pos)const
{
    if (pos == 0)
        return data[top_p];
    else
        return data[bottom];
}

template <class T>
bool doubleStack<T>::isEmpty(int pos)const
{
    if (pos == 0)
        return top_p == -1;
    else
        return bottom == size;
}

template <class T>
void doubleStack<T> :: DoubleSpace()
{
    T *tmp = data;
    data = new T[2 * size];
    for (int i = 0; i <= top_p; i++)
        data[i] = tmp[i];
    for (int i = size - 1; i >= bottom; i --)
        data[i + size] = tmp [i];

    bottom += size;
    size *= 2;
    delete [] tmp;
}
