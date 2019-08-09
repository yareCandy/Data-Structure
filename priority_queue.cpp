//基于二叉堆的优先级队列

#include <iostream>
using namespace std;

long long int times = 0;

template<class Type>
class priority_queue
{
private:
    Type *dt;
    int maxSize;
    int curSize;

    void doubleSpace();
    void buildHeap();
    void perDown(int i);
public:
    priority_queue(int size = 10);
    priority_queue(Type a[], int size);
    ~priority_queue(){delete [] dt;}
    void push(const Type &d);
    Type pop();
    Type top()const {return dt[1];}
    bool empty(){return curSize == 0;}
};

template<class Type>
priority_queue<Type>::priority_queue(Type a[], int size)
{
    curSize = size;
    maxSize = 2 * size;
    dt = new int[maxSize];
    for (int i = 0; i < size; i++)
        dt[i+1] = a[i];
    buildHeap();
}

template <class Type>
priority_queue<Type>::priority_queue(int size)
{
    dt = new int [size];
    curSize = 0;
    maxSize = size;
}

template <class Type>
void priority_queue<Type>::push(const Type &d)
{
    if (curSize == maxSize -1) doubleSpace();

    int hole = ++curSize;
    if (hole > 1) times++;
    for (; hole > 1 && dt[hole/2] > d; ++times, hole /=2)
        dt[hole] = dt[hole/2];
    if (curSize!= 1 && hole<=1) times--;
    dt[hole] = d;
}

template <class Type>
void priority_queue<Type>::doubleSpace()
{
    Type *tmp = dt;
    maxSize *= 2;
    dt = new Type[maxSize];
    for (int i = 1; i <= curSize; i++)
        dt[i] = tmp[i];
}

template <class Type>
Type priority_queue<Type>::pop()
{
    Type tmp = dt[1];
    dt[1] = dt[curSize--];
    perDown(1);
    return tmp;
}

template <class Type>
void priority_queue<Type>::perDown(int i)
{
    int child;
    Type tmp = dt[i];
    for (; 2 * i <= curSize; i = child)
    {
        child = i * 2;
        if (child < curSize) times++;
        if (child < curSize && dt[child + 1] < dt[child])
            child ++;
        
        ++times;
        if (dt[child] < tmp) dt[i] = dt[child];
        else break;
    }
    dt[i] = tmp;
}

template<class Type>
void priority_queue<Type>::buildHeap()
{
    for (int i = curSize/2; i > 0; i --)
        perDown(i);
}


void quick_sort(int a[], int left, int right)
{
    if (left >= right) return;
    int i = left, j = right;
    int cur = a[left];
    while(i < j)
    {
        while (i < j && a[j] > cur) {j--; times ++;}
        if (i < j) {a[i++] = a[j]; times++;}
        while (i < j && a[i] < cur) {i++; times ++;}
        if (i < j) {a[j--] = a[i]; times++;}
    }
    a[i] = cur;
    quick_sort(a, left, i-1);
    quick_sort(a, i+1, right);
}


void merge(int a[], int size1, int size)
{
    int *array = new int [size];
    int i = 0, j = size1, k = 0;
    while (i < size1 && j < size)
    {
        if (a[i] < a[j]) array[k++] = a[i++];
        else array[k++] = a[j++];
        ++times;
    }

    while (i < size1) array[k++] = a[i++];
    while (j < size) array[k++] = a[j++];
    for (int m = 0; m < size; m++)
        a[m] = array[m];
    delete [] array;
}

void merge_sort(int a[], int size)
{
    if (size <= 1) return;
    int mid = size/2;
    merge_sort(a, mid);
    merge_sort(a+mid, size-mid);
    merge(a, mid, size);
}

int main()
{
    int N, kind;
    cin >> N >> kind;
    int *array = new int [N];
    
    switch(kind)
    {
        case 1: //堆排

            {if (N == 1) {cout << 0 << '\n'; break;}
            int tmp;

            priority_queue<int> tree;
            for (int i = 0; i < N; i++)
            {
                cin >> tmp;
                tree.push(tmp);
            }
            
            for (int i = 0; i <N; i++) 
                tree.pop();
            cout << times <<'\n';}
            break;

        case 2: //归并排序
            for (int i = 0; i < N; i++)
                cin >> array[i];
            merge_sort(array, N);
            cout << times << '\n';
            break;

        case 3: //快排
            for (int i = 0; i < N; i++)
                cin >> array[i];
            quick_sort(array, 0, N-1);
            cout << times << '\n';
            
            break;
            
        default: break;
    }

    delete [] array;
    return 0;
} 