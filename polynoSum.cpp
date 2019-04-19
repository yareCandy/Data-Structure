//polynoSum.cpp
//用线性表实现对多项式求和

#include <iostream>
using namespace std;

struct node
{
    int coeff;
    int index;
    node *next;

    node(): next(NULL){};
    node(const node &other):coeff(other.coeff), index(other.index), next(NULL){};
    node(int c, int i, node *n = NULL) :coeff(c), index(i), next(n){};
};

class polynomal
{
    friend ostream &operator << (ostream &, const polynomal &);
    friend polynomal add(const polynomal &n1, const polynomal &n2);
    private:
        node *head;
        node *moveEnd()//返回末尾地址的指针
        {
            node *p = head;
            while (p -> next != NULL) p = p -> next;
            return p;
        }
    public:
        polynomal(){head = new node;}
        void insert(const node &n)
        {
            node *tmp = new node(n);
            node *p = moveEnd();
            p -> next = tmp;
        }
        ~polynomal()
        {
            node *p = head, *q;
            while (p != NULL)
            {
                q = p -> next;
                head = p;
                p = q;
            }
        }
};

ostream &operator << (ostream &os, const polynomal &n)
{
    node *p = n.head -> next;
    bool isFirst = true;
    while (p != NULL)
    {
        if (p -> index == 0) //和的系数位0，结果不写入
        {
            os << p -> coeff;
            isFirst = false;
        }
        else if (isFirst)
        {
            os << p -> coeff << "x^" << p -> index;
            isFirst = false;
        }
        else
        {
            if (p -> coeff < 0)
            {
                os << p -> coeff << "x^" << p -> index;
                isFirst = false;
            }
            else if (p -> coeff == 1)
            {
                os << '+' << "x^" << p -> index;
                isFirst = false;
            }
            else
            {
                os << '+' << p -> coeff << "x^" << p -> index;
                isFirst = false;
            }

        }
        p = p -> next;
    }

    return os;
}

polynomal add(const polynomal &n1, const polynomal &n2)
{
    node *t1, *t2, *tmp, *p;
    polynomal result; //存方运算结果
    //从头开始遍历两个多项式
    t1 = n1.head -> next;
    t2 = n2.head -> next;
    p = result.head;
    int coeff;

    while(t1 != NULL && t2 != NULL)
    {
        if (t1 -> index == t2 -> index) //指数相等
        {
            coeff = t1 -> coeff + t2 -> coeff;
            if (coeff)
            {
                tmp = new node(t1 -> coeff + t2 -> coeff, t1 -> index);
                p -> next = tmp;
                p = p -> next;
            }
            t1 = t1 -> next;
            t2 = t2 -> next;
        }
        else if (t1 -> index < t2 -> index) //指数不相等时取小的
        {
            tmp = new node(t1 -> coeff, t1 -> index);
            p -> next = tmp;
            p = p -> next;
            t1 = t1 -> next;
        }
        else
        {
            tmp = new node(t2 -> coeff, t1 -> index);
            p -> next = tmp;
            p = p -> next;
            t2 = t2 -> next;
        }
    }

    while (t1 != NULL)
    {
        tmp = new node(t1 -> coeff, t1 -> index);
        p -> next = tmp;
        p = p -> next;
        t1 = t1 -> next;
    }

    while (t2 != NULL)
    {
        tmp = new node(t2 -> coeff, t2 -> index);
        p -> next = tmp;
        p = p -> next;
        t2 = t2 -> next;
    }

    return result;
}

int main()
{
    polynomal n1, n2;
    node t1(2, 0), t2(1, 2);
    n1.insert(t1);
    node t3(1,1), t4(-1,2), t5(5, 3);
    n1.insert(t3);
    n1.insert(t4);
    cout << "n1 = " << n1 << endl;
    n2.insert(t2);
    n2.insert(t5);
    cout << "n2 = " << n2 << endl;
    cout << "n1 + n2 = " << add(n1, n2) << endl;

    return 0;
}

