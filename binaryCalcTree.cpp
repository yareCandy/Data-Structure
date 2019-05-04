//binaryCalcTree.cpp
//利用二叉树计算中缀表达式的值
//先构建一刻表达式树，再进行后序遍历即可
#include <iostream>
using namespace std;

class calcTree
{
    //节点类型：数值，加减乘除开闭行结束
    enum Type{DATA, ADD, SUB,MULTI, DIV, OPRAEN, CPAREN, EOL};

    struct node
    {
        Type type;
        int dt;
        node *left, *right;
        node (Type t, int d = 0, node *l = nullptr, node *r = nullptr)
            :type(t), dt(d), left(l), right(r){}
    };

    node *root;

    node *create(char *&s)//从s创建一颗表达式树
    {
        node *p, *root = nullptr;
        Type returnType;
        int value;

        while(*s)
        {
            returnType = getToken(s, value);
            switch(returnType)
            {
                case DATA: case OPRAEN:
                    if (returnType == DATA) p= new node (DATA, value);
                    else p = create(s);
                    if (root != nullptr)
                    {
                        if (root ->right == nullptr) root ->right = p;
                        else root ->right ->right = p;
                    }
                    break;
                case CPAREN: case EOL:
                    return root;
                case ADD: case SUB:
                    if (root == nullptr) root = new node (returnType, 0, p);
                    else root = new node (returnType, 0, root);
                    break;
                case MULTI: case DIV:
                    if (root == nullptr) root = new node(returnType, 0, p);
                    else if (root ->type == MULTI || root ->type == DIV)
                        root = new node (returnType, 0, root);
                    else root ->right = new node (returnType, 0, root ->right);
            }
        }

        return root;
    }

    Type getToken(char *&s, int &data)//从s中获取一个语法单元
    {
        char type;
        while(*s == ' ') s++;

        if (*s >= '0' && *s <= '9')
        {
            data = 0;
            while(*s >= '0' && *s <= '9')
            {
                data = data * 10 + *s - 10;
                s++;
            }
            return DATA;
        }

        if (*s == '\0') return EOL;

        type = *s, s++;
        switch(type)
        {
            case '-': return SUB;
            case '+': return ADD;
            case '*': return MULTI;
            case '/': return DIV;
            case '(': return OPRAEN;
            case ')': return CPAREN;
            default: return EOL;
        }
    }

    int result(node *t)
    {
        int num1, num2;

        if (t ->type == DATA) return t ->dt;
        num1 = result(t ->left);
        num2 = result(t ->right);
        switch(t ->type)
        {
            case ADD: t ->dt = num1 + num2; break;
            case SUB: t ->dt = num1 - num2; break;
            case MULTI: t ->dt = num1 * num2; break;
            case DIV: t ->dt = num1 / num2; break;
            default: break;
        }

        return t ->dt;
    }
public:
    calcTree(char *s){root = create(s);}
    int result()
    {
        if (root == nullptr) return 0;
        else return result(root);
    }
};
