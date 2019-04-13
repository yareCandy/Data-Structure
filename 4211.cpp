//4206.cpp
//OJ 4211
//输出每个元素后面第一个比它大的元素

#include <iostream>
#include <cstring>
using namespace std;

template <class T>
class linkStack
{
    private:
        struct node
        {
            T dt;
            node *next;
            node (const T &x, node *n = NULL):dt(x), next(n){};
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
        void push(const T &x)
        {
            node *tmp = new node(x, top_p);
            top_p = tmp;
        }
        T top()const{return top_p -> dt;}
        T pop()
        {
            node *tmp = top_p;
            T x = top_p -> dt;
            top_p = top_p -> next;
            delete tmp;
            return x;
        }
        bool isEmpty()const {return top_p == NULL;}
};


struct Node
{
    int label;
    int index;
    char name[70];
    Node (int n, const char *str)
    {
        index = n;
        strcpy(name, str);
    }
    Node () {index = 0; label = 0; name[0] = '\0';}
};

void Get(Node &c);

int main()
{
    int size;
    Node current;
    linkStack<Node> stack;
    scanf("%d", &size);
    cin.get();
    char **name = new char *[size];

    for (int i = 0; i < size; i++)
    {
        Get(current);

        while (!stack.isEmpty() && stack.top().index < current.index)
        {
            name[stack.top().label] = new char[strlen(current.name) + 1];
            strcpy(name[stack.top().label], current.name);
            stack.pop();
        }
        stack.push(current);
    }

    while (!stack.isEmpty())
    {
        name[stack.top().label] = new char [3];
        strcpy(name[stack.top().label], "-1");
        stack.pop();
    }

    for (int i = 0; i < size; i++)
        puts(name[i]);

    return 0;
}

void Get(Node &c)
{
    static int label = 0;
    c.label = label;
    scanf("%d", &c.index);
    cin.get();
    fgets(c.name, 70, stdin);

    c.name[strlen(c.name)-1] = '\0';
    label++;
}
