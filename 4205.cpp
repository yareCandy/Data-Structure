//4205.cpp
//Turing Award

#include <iostream>
#include <cstring>
using namespace std;

class linkList
{
    private:
        struct node
        {
            char *name;
            int year;
            node *next;
            node(const char n[], int y, node *nx = NULL)
            {
                name = new char[strlen(n) + 1];
                strcpy(name, n);
                year = y;
                next = nx;
            }
            node():next(NULL){}
            ~node(){};
        };
        node *head;
        int length;
        int getNum(const char []);

    public:
        linkList(){head = new node; length = 0;}
        ~linkList();
        void inSert(const char n[], int y);
        void print(int i)const;
        void del(int i);
        void operate(const char []);

};

int linkList::getNum(const char str[])
{
    int result = 0;
    while(str[0] != '\0' && str[0] != ' ' && str[0] >= '0' && str[0] <= '9')
    {
        result = result * 10 + str[0] - '0';
        str++;
    }
    return result;
}

linkList::~linkList()
{
    node *p = head -> next, *q;
    head -> next = NULL;
    while(p != NULL)
    {
        q = p -> next;
        delete p;
        p = q;
    }
    delete head;
}

void linkList::inSert(const char n[], int y)
{
    node *p = head;
    while(p -> next != NULL)
    {
        if (y < p -> next -> year)
        {
            p -> next = new node(n, y, p -> next);
            break;
        }
        else if (y == p -> next -> year)
        {
            if (strcmp(n, p -> next -> name) < 0)
            {
                p -> next  = new node(n, y, p -> next);
                break;
            }
            else p = p -> next;
        }
        else p = p -> next;
    }
    if (p -> next == NULL)
        p -> next = new node(n, y, NULL);
    length ++;
}

void linkList::print(int i)const
{
    if (i < 1 || i > length)
        return;

    node *p = head -> next;
    for(int j = 1; j < i; j++)
        p = p -> next;
    cout << p -> year << ' ' << p -> name << endl;
}

void linkList::del(int i)
{
    if (i < 1 || i > length)
        return;

    node *p = head, *tmp;
    for(int j = 1; j < i; j++)
        p = p -> next;
    tmp = p -> next;
    p -> next = tmp -> next;
    delete tmp;
    length--;
}

void linkList::operate(const char str[])
{
    int k;
    char op[10];
    while (str[0] == ' ') str++;
    for(k = 0; str[k] != '\0' && str[k] != ' '; k++)
        op[k] = str[k];
    op[k] = '\0';

    if (!strcmp(op, "list"))
    {
        int i;
        str += 4;
        while(str[0] == ' ') str++;
        if (str[0] <= '9' && str[0] >= '0')
        {
            i = getNum(str);
            print(i);
        }
        else return;
    }
    else if(!strcmp(op, "insert"))
    {
        int y;
        char name[30];
        str += 6;
        while(str[0] == ' ') str++;
        if (str[0] <= '9' && str[0] >= '0')
        {
            y = getNum(str);
            while(str[0] != '\0' && str[0] != ' ') str++;
            while(str[0] == ' ') str ++;
            strcpy(name, str);
            inSert(name, y);
        }
        else return;
    }
    else if(!strcmp(op, "delete"))
    {
        int i;
        str += 6;
        while(str[0] == ' ') str++;
        if (str[0] <= '9' && str[0] >= '0')
        {
            i = getNum(str);
            del(i);
        }
        else return;
    }
    else return;
}

int main()
{
    int N;
    char str[80];
    linkList turing;

    cin >> N;
    cin.get();
    for (int j = 0; j < N; j++)
    {
        cin.getline(str, 79);
        turing.operate(str);
    }
    return 0;
}
