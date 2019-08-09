//OJ1226
//快速排序
//堆排序

#include <iostream>
using namespace std;


/*
class priorityQueue//使用顺序存储实现的最小化堆
{
private:
    int *dt;
    int maxSize;
    int curSize;

void doubleSpace();
void buildHeap();
void perDown(int i);

public:
    priorityQueue(int initSize = 100);
    priorityQueue(const int a[], int size);
    ~priorityQueue(){delete [] dt;}
    void push(int d);
    int pop();
    bool empty(){return curSize == 0;}
    int top(){return dt[1];}  
}; // priorityQueue

void priorityQueue::doubleSpace()
{
    int *tmp = dt;
    maxSize *= 2;
    dt = new int[maxSize];
    for (int i = 0; i < curSize; i++)
        dt[i] = tmp [i];
    delete [] tmp;
}

void priorityQueue::buildHeap()
{
    for (int i = curSize/2; i > 0; i--)
        perDown(i);
}

void priorityQueue::perDown(int i)
{
    int child;
    int tmp = dt[i];

    for (; i * 2 <= curSize; i = child)
    {
        child = i * 2;
        if (child != curSize && dt[child] > dt[child+1])
        //最大化堆应该修改为
        //if （child != curSize && dt[child] < dt[child+1]
            child++;
        if (dt[child] < tmp) dt[i] = dt[child];
        //最大化堆应该修改为
        //if (dt[child] > tmp)
        else break;
    }
    dt[i] = tmp;
}

int priorityQueue::pop()
{
    int tmp = dt[1];
    dt[1] = dt[curSize--];
    perDown(1);
    return tmp;
}

void priorityQueue::push(int d)
{
    if (curSize == maxSize - 1) doubleSpace();

    int hole = ++curSize;

    for (; hole > 1 && d < dt[hole/2]; hole /= 2)
    //最大化堆应该修改为 d > dt[hole/2]

        dt[hole] = dt[hole/2];
    dt[hole] = d;
}

priorityQueue::priorityQueue(int initSize)
{
    dt = new int [initSize];
    maxSize = initSize;
    curSize = 0;
}

priorityQueue::priorityQueue(const int a[], int size)
{
    dt = new int[size];
    for (int i = 0; i < size; i++)
        dt[i+1] = a[i];
    curSize = size;
    maxSize = size * 2;
    buildHeap();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, num;

    priorityQueue que(1000000);
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> num;
        que.push(num);
    }

    for (int i = 0; i < N; i ++)
        cout << que.pop() << " ";
    cout << '\n';

    return 0;
}
*/

//====================================快排=============

void quick_sort(int a[], int left, int right)
{
    if (left >= right) return;
    int i = left, j = right, cur = a[left];

    while(i < j)
    {
        while (i < j && a[j] > cur) j--;
        if ( i < j) a[i++] = a[j];

        while (i < j && a[i] < cur) i++;
        if (i < j) a[j--] = a[i];
    }
    a[i] = cur;
    quick_sort(a, left, i-1);
    quick_sort(a, i+1, right);
}

int main()
{
    int N;
    cin >> N;
    int *array = new int [N];

    for (int i = 0; i < N; i++)
        cin >> array[i];
    quick_sort(array, 0, N-1);

    for (int i = 0; i < N; i++)
        cout << array[i] << " ";
    cout << '\n';

    delete [] array;
    return 0;
}