//stack.cpp
//栈的定义及其实现
/*
栈：
    线性表的一类，但特点是：先进的后出，后进的先出，乒乓球放进管子中
    主要运算:isEmpty（）判空：检查当前栈是否为空
            push（数据）压入：让数据进栈，放在最顶端
            pop（）：弹出并返回最顶端的元素

    题库：判断进出站序列是否可能：（查找题目）
*/

#include <iostream>
#include <cmath>
using namespace std;

template <class T>
class seqStack
{
    private:
        T *data;//栈底
        int top_p;//栈顶的序列，创建时 top_p 应该设置为 -1，便于检查非空
        int maxSize;//栈的大小
        void doubleSpace();
    public:
        seqStack(int initSize = 10);
        ~seqStack();
        void push(const T &x);
        bool isEmpty()const;

        T top()const;
        T pop();
};

template <class T>
seqStack<T>::seqStack(int initSize)
{
    maxSize = initSize;
    top_p = -1;
    data = new T[initSize];

}

template<class T>
seqStack<T>::~seqStack()
{
   delete [] data;//为什么不用释放动态数组，否则会报“double free"的错误？
}

template <class T>
bool seqStack<T>::isEmpty()const
{
    return top_p == -1;
}

template <class T>
void seqStack<T>::push(const T &x)
{
    if (top_p == maxSize -1)
        doubleSpace();
    data[top_p] = x;
    top_p ++;
}

template <class T>
T seqStack<T>::pop()
{
    return data[--top_p];
}

template <class T>
T seqStack<T>::top()const
{
    return data[top_p];
}

template<class T>
void seqStack<T> :: doubleSpace()
{
    T *tmp = data;
    data = new T[maxSize * 2];
    for (int i = 0; i < maxSize; i++)
        data[i] = tmp[i];
    delete [] tmp;
}

//作业：判断对于一个出栈顺序是否可能
//a1,a2,a3...aN依次进栈，判断p1, p2, ...pN出栈顺序是否可能
//人工选择思想：i个元素输出后面比i先进栈的元素必须按照先进后出原则
//代码实现思想：将进栈的元素依次压入，如果栈顶的元素与出栈元素的首个相等，就弹出该元素
bool isValid(const int *stack_in, const int *stack_out, int len_in, int len_out)
{
    if (!(stack_in && stack_out) || len_in != len_out)
        return false;

    seqStack<int> s;
    int i, j = 0;
    for (i = 0; i < len_in; i++)
    {
        s.push(stack_in[i]);
        while(!s.isEmpty() && s.top() == stack_out[j])
        {
            //如果，栈顶等于出栈元素，那么弹出栈顶元素
            s.pop();
            j++;
        }
    }

    return (s.isEmpty()) ? true : false;
}




//单链表实现栈
//思想：用top_P指针作为头指针，始终将其指在栈顶，next指针指向栈顶下一位
template <class T>
class linkStack
{
    private:
        struct node
        {
            T data;
            node *next;
            node (const T &x, node *n = NULL):data(x), next(n){};
            node():next(NULL){};
        };

        node *top_p;

    public:
        linkStack():top_p(NULL){};
        ~linkStack()
        {
            node *p;
            while(top_p != NULL)
            {
                p = top_p;
                top_p = top_p ->next;
                delete p;
            }
        }
        T pop()
        {
            node *tmp = top_p;
            T x = top_p -> data;
            top_p = top_p -> next;
            delete tmp;
            return x;
        }
        void push(const T &x)
        {
            node *tmp = new node(x, top_p);
            top_p = tmp;
        }
        T top()const{ return top_p -> data;}

        bool isEmpty()const {return top_p == NULL;}
};

//栈的应用
//一、 打印正整数
void print(int num)
{
    seqStack<int> s;
    int tmp;
    s.push(num);

    while (!s.isEmpty())
    {
        tmp = s.pop();
        if (tmp > 9)
        {
            s.push(tmp % 10);
            s.push(tmp / 10);
        }
        else
            cout << (tmp);
    }
}

//计算后缀表达式的值
int calc(const char []);
//从字符串中提取出数字
int getNum(const char[], int &i);//i表示下标

int main()
{
    char str[80];
    cin.getline(str, 80);

    cout << calc(str) << endl;

    return 0;
}


int calc(const char str[])
{
    seqStack<int> stack;

    int i = 0, result;
    int num1, num2;
    while (str[i] == ' ') i++;//跳过前置空格

    while (str[i] != '\0')
    {
        if (str[i] <= '9' && str[i] >= '0')
        {
            result = getNum(str, i);
            stack.push(result);
        }

        if (str[i] == '^' || str[i] == '*' || str[i] == '/' ||
            str[i] == '+' || str[i] == '-')
        {
            if (!stack.isEmpty())
            {
                num2 = stack.pop();
                if (!stack.isEmpty()) num1 = stack.pop();
                else {cerr << "Absence of the operator numbers!" << endl; exit(1);}

                switch(str[i])
                {
                    case '^': stack.push(pow(num1, (double)num2));
                              break;
                    case '*': stack.push(num1 * num2);
                              break;
                    case '/': stack.push(num1 / num2);
                              break;
                    case '+': stack.push(num1 + num2);
                              break;
                    case '-': stack.push(num1 - num2);
                              break;
                    default:  break;
                }
                i++;
            }
            else {cerr << "Absence of the operator numbers!" << endl; exit(1);}
        }

        while (str[i] == ' ') i++;
    }

    //没有计算结果
    if (stack.isEmpty()) {cerr << "Absence of the operator numbers!" << endl; exit(1);}
    //计算结果不止一个，缺少运算符
    result = stack.pop();
    if (!stack.isEmpty()) {cerr << "Absence of the operator" << endl; exit(1);}

    return result;
}

int getNum(const char str[], int &i)
{
    int result = 0;

    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + str[i] - '0';
        i++;
    }

    while (str[i] == ' ') i++;

    return result;
}
