//change.cpp
//将中缀表达式转化为后缀表达式
//思想：有两个分别存放操作数和运算符的栈
//1、 如果读入的是操作数，将其存在操作数栈
//2、 如果读入的是左括号，让其进栈
//3、 如果读入的是右括号，则对应开括号间的所有运算均可执行，即将运算数栈中的在左括号之前的全部存到操作数栈
//4、 如果读入的是乘方，因为乘方的优先级最高，而且是右结合的，所有其前面的所有运算均不能执行，它本身能否执行也未知
//    将其存入栈中，若其后面的运算数不是乘方，则可以进行乘方运算，即将其存入操作数栈
//5、 如果读入的是乘除运算，则它前面的乘除、乘方都能进行运算，则运算数栈顶退至直到遇见加减运算，或者左括号
//6、 如果读入的是加减运算，出现在它前面的乘方、乘除、加减都可进行运算，栈顶退至栈为空或者遇见左括号
//7、 在读入结束时，将栈中所有剩余运算符依次出栈

#include <iostream>
#include <cstdlib>
#include <cstring>
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
    delete [] data;
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

bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '/' || ch == '^' || ch == '(' || ch == ')')
        return true;
    else return false;
}

char *infix_to_suffix(const char *infix)
{
    seqStack< char > opStack;
    //seqStack< char > numStack;
    char topOp;
    int j = 0;
    char *result = new char[strlen(infix) + 1];
    result[0] = '\0';
    int len = strlen(infix);
    static char flag[] = "error";

    for (int i = 0; i < len; i++)
    {
        if (infix[i] == ' ') continue;

        switch(infix[i])
        {
            case ')':   while(!opStack.isEmpty() && (topOp = opStack.pop()) != '(')
                        {
                            result[j++] = ' ';
                            result[j++] = topOp;
                        }

                        if (topOp != '(')
                        {
                            cerr << "缺左括号！" << endl;
                            return flag;
                        }
                        break;
            case '(':   opStack.push('('); break;
            case '^':   opStack.push('^'); break;
            case '*': case '/':
                        while (!opStack.isEmpty() && ((opStack.top()) == '*' ||
                        opStack.top() == '/' || opStack.top() == '^'))
                        {
                            result[j++] = ' ';
                            result[j++] = opStack.pop();
                        }
                        opStack.push(infix[i]);
                        break;
            case '+': case '-':
                        while(!opStack.isEmpty() && opStack.top() != '(')
                        {
                            result[j++] = ' ';
                            result[j++] = opStack.pop();
                        }
                        opStack.push(infix[i]);
                        break;

            default:    if (result[0] != '\0') result[j++] = ' ';
                        while (i < len && !isOperator(infix[i] && infix[i] != ' '))
                        {
                            result[j++] = infix[i];
                            ++i;
                        }
                        --i;
        }
    }

    while( !opStack.isEmpty())
    {
        if (opStack.top() == '(') return flag;
        result[j++] = ' ';
        result[j++] = opStack.pop();
    }

    result[j] = '\0';

    return result;
}

int cacl_suffix(const char *suffix)
{
    seqStack<int> dataStack;
    int num1, num2, result;
    int len = strlen(suffix);

    for (int i = 0; i < len; i++)
    {
        if (suffix[i] == ' ') continue;

        if (!isOperator(suffix[i]))
        {
            result = 0;
            while (i < len && suffix[i] != ' ')
            {
                result = result * 10 + suffix[i] - '0';
                i++;
            }
            dataStack.push(result);
            continue;
        }

        num2 = dataStack.pop();
        num1 = dataStack.pop();

        switch(suffix[i])
        {
            case '^': result = pow(num1, num2); break;
            case '*': result = num1 * num2; break;
            case '/': result = num1 / num2; break;
            case '+': result = num1 + num2; break;
            case '-': result = num1 - num2; break;
        }
        dataStack.push(result);
    }

    return dataStack.pop();
}

int main()
{
    const int MAX = 1000000;
    int i;
    char a;
    char ch[MAX];
    for (i = 0; i < 16; i++)
    {
        cin >> a;
        ch[i] = a;;
    }
    ch[i] = '\0';
    char *p = infix_to_suffix(ch);
    cout << p << '\n';
    cout << cacl_suffix(p) << '\n';
    delete p;

    return 0;
}
