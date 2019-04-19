//linkqueue.cpp
//链接实现队列

#include <iostream>
#include <cstring>
using namespace std;

template <class T>
class linkQueue
{
    private:
        struct node
        {
            T dt;
            node *next;
            node(const T &d, node *n = NULL): dt(d), next(n){}
            node(): next(NULL){}
        };

        node *front, *rear;
    public:
        linkQueue();
        ~linkQueue();
        T getHead()const;
        T getTail()const;
        bool isEmpty()const;
        void enQueue(const T& d);
        T deQueue();

};// linkQueue;

template <class T>
linkQueue<T>::linkQueue()
{
    rear = front = NULL;
}

template<class T>
linkQueue<T>::~linkQueue()
{
    node *tmp;
    while(front != NULL)
    {
        tmp = front -> next;
        delete front;
        front = tmp;
    }
}

template<class T>
bool linkQueue<T>::isEmpty()const
{
    return front == NULL;//对空标志：没有头节点，队空时两个指针皆为NULL
}

template <class T>
T linkQueue<T>::getHead()const
{
    return front -> dt;
}

template<class T>
T linkQueue<T>::getTail()const
{
    return rear -> dt;
}


template<class T>
void linkQueue<T>::enQueue(const T &d)
{
    if (rear == NULL) front = rear = new node(d);
    else  rear = rear -> next = new node(d);
}

template<class T>
T linkQueue<T>::deQueue()
{
    node *tmp = front;
    T value = front -> dt;
    front = front -> next;

    if (front == NULL) rear = NULL;//删除后为空链表
    delete tmp;
    return value;
}



//车厢重排函数
void arrage(const int [], int, int);//序列， 车厢数， 缓冲轨道数

//将合适的元素出队
void checkBuffer(linkQueue<int> *buffer, int size, int &last);//缓冲队列， 队列数， 轨上最后一节车厢的车厢号

//当in进入了合适的缓冲队列时返回true， 否则为false
bool putBuffer(linkQueue<int> *buffer, int size, int in);//一组缓冲队列， 缓冲队列数， 即将进入缓冲轨道的车厢号

//用链表实现火车车厢重排
//缓冲轨道的数量与n的关系是什么？
//思想：引入辅助的轨道（队列）分开存放，每条按照升序排列
//              根据队列性质，每次从队头取出元素即可
int main()
{
    int num, buffer,  *array;
    cin >> num >> buffer;
    array = new int [num];
    for (int i = 0; i < num; i++)
        cin >> array[i];

    arrage(array, num, buffer);

    delete [] array;

    return 0;
}


void arrage(const int a[], int size, int numOfBuffer)
{
    linkQueue<int> *buffer = new linkQueue<int> [numOfBuffer];//创建缓冲轨道
    int last = 0;

    for (int i = 0; i < size; i++)
    {
        //将车厢放入合适的缓冲轨道
        if (! putBuffer(buffer, numOfBuffer, a[i])) return;//如果没有合适的缓冲轨道，就退出
        checkBuffer(buffer, numOfBuffer, last);//每次将车厢放入缓冲车道后，均进行检查是否可以将下一个出轨
    }
}

bool putBuffer(linkQueue<int> *buffer, int num, int in)
{
    int avail = -1, max = 0;//avail保存合适的队列号， max保存该队列对为元素

    for (int i = 0; i < num; i++)
    {
        //如果当前队列为空，备用
        if (buffer[i].isEmpty())
        {
            if (avail == -1) avail = i;
        }
        else if (buffer[i].getTail() < in && buffer[i].getTail() > max)
        {
            avail = i;//原理：要注意对比每个缓冲队列队尾，找到与下个元素最接近的队列
           max = buffer[i].getTail();
        }
    }

    if (avail == -1) { cout << "No solution! " << endl;return false;}
    else {buffer[avail].enQueue(in); cout << in << " moves to  " << avail << endl; return true;}
}


void checkBuffer(linkQueue<int> *buffer, int size, int &last)
{
    int j;
    bool flag = true;

    while(flag)
    {
        //检查所有队列
        flag = false;
        for (j = 0; j < size; j++)
        {
            if (!buffer[j].isEmpty() && buffer[j].getHead() == last + 1)
            {
                //出队
                cout << "Make " << buffer[j].deQueue()  <<  " out of trace  from " << j<< endl;
                ++last;
                flag = true;
                break;
            }
        }
    }
}


void arrage(int in[], int n, int k)//入轨序列，车箱数，空轨数
{
    linkQueue<int> *buffer = new linkQueue<int> [k];//创建缓冲轨道
    int inPos = 0;//入轨上正在处理的车厢下标
    int avail, i , j;
    int noOfEmpty = k;//空闲缓冲轨道
    bool flag;

    for (i = 0; i < n; i++)
    {
        if (inPos < n && in[inPos] == i+1)//入轨上正好可以出轨
        {
            if (noOfEmpty>0)
            {
                cout << "将 " << i+1 << " 出轨\n";
                inPos++;
                continue;
            }
            else {cout << "无可行方案\n"; break;}
        }

        for (j = 0; j < k; j++)
        {
            if (!buffer[j].isEmpty() && buffer[j].getHead() == i+1)
            {
                cout << "将 " << buffer[j].getHead() << " 出轨\n";
                buffer[j].deQueue();
                if (buffer[j].isEmpty()) noOfEmpty++;//空轨数有多余的
                break;
            }
        }

        if (j < k) continue;

        //将入轨前面的车厢移入最合适的轨道
        flag = false;
        for (j = 0; j < k; j++)
        {
            if (buffer[j].isEmpty())
            {
                flag = true;
                avail = j;
                continue;
            }
            if (buffer[j].getTail() < in[inPos])
            {
                buffer[j].enQueue(in[inPos]);
                cout << in[inPos] << " 移入缓存区 " << j << '\n';
                ++inPos;
                break;
            }
        }

        if (j == k)
        {
            if (flag)
            {
                buffer[avail].enQueue(in[inPos]);
                cout << in[inPos] << " 移入缓存区 "<< avail << '\n';
                ++inPos;
                --noOfEmpty;
            }
            else
            {
                cout << "无可行方案\n";
                break;
            }
        }
    i--;
    }
}

//另外一种重排模型，转换站台是一个类似栈的区域，且有固定容量
//可以选择从入轨上将车厢直接出轨，也可以从转换站台顶出轨

#include <stack>

void Arrange()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;//测试点规模
    int num, vec;//火车数量以及站台容量
    int *out, j, m, i = 0;
    stack<int> st;

    cin >> n;

    for (int k = 0; k < n; k++)
    {
        stack<int> st;//也有问题
        i = j = 0;
        cin >> num;
        cin >> vec;
        out = new int[num];
        for (m = 0; m < num; m++)//接收出栈顺序
            cin >> out[m];

        //开始检测
        while (true)
        {
            if (i == out[j]) {i++; j++;}
            else if (!st.empty() && st.top() == out[j])
            {
                while (!st.empty() && st.top() == out[j]) {j++; st.pop();}//可能有问题
            }
            else if (!st.empty() && st.top() != out[j] && (int)st.size() != vec)
            {st.push(i); i++;}
            else if (!st.empty() && st.top() != out[j] && (int)st.size() == vec) break;
            else    {st.push(i); i++;}//栈空

            if (i == num) break;
        }
        while(!st.empty() && st.top() == out[j]) {st.pop(); j++;}
        if (st.empty()) cout << "Yes\n";
        else cout << "No\n";

        delete out;
    }
}
