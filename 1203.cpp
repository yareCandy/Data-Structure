//1203.cpp
//OJ1203
//将两个线性表合为一个
#include <iostream>
#include <cstring>
using namespace std;

template<class T>
class ls
{
    private:
        T *dt;
        int maxSize;
        int curSize;
        void doubleSpace();
    public:
        ls(int initSize = 10);
        ~ls(){delete [] dt;}
        void ADD();
        void ADD2();
        void insert(int i, const T &d);
        ls operator+ (const ls &n1)const;
};

template <class T>
void ls<T>::ADD()
{
    for (int i = 0; i < maxSize; i++)
    {
        cin >> dt[i];
        curSize++;
    }
}

template <class T>
void ls<T>::ADD2()
{
    for (int i = 0; i < maxSize; i++)
    {
        dt[i] = cin.get();
        curSize++;
        cin.get();
    }
}

template <class T>
ls<T>::ls(int initSize)
{
    dt = new T[initSize];
    maxSize = initSize;
    curSize = 0;
}

template <class T>
void ls<T>::doubleSpace()
{
    T *tmp = dt;
    maxSize *= 2;
    dt = new T[maxSize];
    for (int i = 0; i < curSize; ++i)
        dt[i] = tmp[i];
    delete [] tmp;
}

template<class T>
void ls<T>::insert(int i, const T &d)
{
    if (i < 0 || i > curSize) return;
    int j;
    if (curSize == maxSize) doubleSpace();

    for (j = curSize; j > i; j--) dt[j] = dt[j-1];
    dt[i] = d;
    curSize++;
}

template<class T>
ls<T> ls<T>::operator+(const ls<T> &n2)const
{
    int j;
    ls<T> result(maxSize + n2.maxSize);

    for(j = 0; j < curSize; j++)
        result.insert(j, dt[j]);
    for(j = 0; j < n2.curSize; j++)
        result.insert(j + curSize, n2.dt[j]);
    for(j = 0; j < result.curSize; j++)
        cout << result.dt[j] << ' ';

    return result;
}

int main()
{
    char op[10], command[10];
    cin.getline(command, 10);

    int size1, size2, i = 0;
    cin >> size1 >> size2;

    for (i = 0; command[i] != ' ' && command[i] != '\0'; i++)
        op[i] = command[i];
    op[i] = '\0';

    if (!strcmp(op, "double"))
    {
        ls<double> n1(size1);
        ls<double> n2(size2);

        n1.ADD();
        n2.ADD();
        n1 + n2;
    }
    else if (!strcmp(op, "int"))
    {
        ls<int> n1(size1);
        ls<int> n2(size2);

        n1.ADD();
        n2.ADD();
        n1 + n2;
    }
    else if (!strcmp(op, "char"))
    {
        ls<char> n1(size1);
        ls<char> n2(size2);
        cin.get();
        n1.ADD2();
        n2.ADD2();
        n1 + n2;
    }

    return 0;
}
