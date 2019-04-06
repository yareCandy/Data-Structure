//OJ1206
//检查pascal中 begin，end，if，then，else 是否匹配

#include <iostream>
#include <fstream>
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

enum word {BEGIN, END, IF, THEN, ELSE};
void getstr(const char str[], bool &flag);

int main()
{
    char str[80];
    bool flag = false;
    linkStack<int> stack;


    while ( cin >> str)
    {
            getstr(str, flag);
            if (flag) continue;

            if (!strcmp(str, "then"))
            {
                if (stack.isEmpty() || stack.top() != IF)
                    {cout << ( "Error!\n"); return 0;}
                stack.push(THEN);
                continue;
            }
            if (!strcmp(str, "else"))
            {
                if (stack.isEmpty() || stack.top() != THEN)
                    {cout << ( "Error!\n"); return 0;}
                if (!stack.isEmpty()) {stack.pop(); stack.pop();}

                continue;
            }

            if (!strcmp(str, "if"))
            {
                if (!stack.isEmpty() && stack.top() == IF)
                    {cout << ( "Error!\n"); return 0;}

                stack.push(IF);
                continue;
            }

            if (!strcmp(str, "end"))
            {
                if (stack.isEmpty() || stack.top() == IF) {cout << "Error!\n"; return 0;}
                bool flag = true;
                while (!stack.isEmpty())
                    if (stack.pop() == BEGIN) {flag = false; break;}
                if (flag) {cout << ( "Error!\n"); return 0;}
                continue;
            }
            if (!strcmp(str, "begin"))
            {
                if (!stack.isEmpty() && stack.top() == IF) {cout << ( "Error!\n"); return 0;}

                stack.push(BEGIN);
                continue;
            }
        }

        if (!stack.isEmpty())  {cout << "Error!\n"; return 0;}

       cout << ("Match!\n");
            return 0;

}

