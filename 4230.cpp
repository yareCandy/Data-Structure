//4230.cpp
//OJ4230
//输入若干行，每行执行一个操作。
//每行的第一个字段指示操作的类型，分别有cite, query, finish三种不同的操作，格式如下。
//如果第一个字段是cite，则接下来输入一个字符串，表示论文的标题，该操作表示这篇论文被引用一次，其引用数加1。
//如果第一个字段是query，则输出当前论文被引用数最高的被引用数和论文题目，用空格隔开，如果有两篇以上的论文符合条件，输出论文题目字典序最小的那一个。
//如果第一个字段是finish，则结束输入。
//对于每个query操作，输出一行，表示引用量最高的引用量和论文标题，中间用一个空格隔开。
#include <iostream>
#include <cstring>
using namespace std;

//保存目前最大引用数的论文
int maxTimes = 0;
char maxTitle[150];

struct node
{
        char title[150];
        int times;
        node *left;
        node *right;
        node(const char t[], node *l = nullptr, node *r = nullptr)
        {
            strcpy(title, t);
            left = l;
            right = r;
            times = 1;
        }
        node ():left(nullptr), right(nullptr){}
};

class citeTree
{
private:
    node *root;
public:
    citeTree():root(nullptr){}
    ~citeTree(){clear(root);}
    void insert(const char a[]);
private:
    void clear(node *t);
    void insert(const char a[], node * &t);
};

int label = 0;

void citeTree::insert(const char a[])
{
    insert(a, root);
}

void citeTree::insert(const char title[], node * &t)
{
    if (t == nullptr)
    {
        t = new node (title, nullptr, nullptr);
        if (t ->times > maxTimes)
        {
            maxTimes = t ->times;
            strcpy(maxTitle, t ->title);
        }

        else if(t ->times == maxTimes)
            if (strcmp(t ->title, maxTitle) < 0)
                strcpy(maxTitle, t ->title);
    }

    else if (strcmp(title, t ->title) > 0)
        insert(title, t ->right);
    else if (strcmp(title, t ->title) < 0)
        insert(title, t ->left);
    else
    {
        t ->times ++;

        if (t ->times > maxTimes)
        {
            maxTimes = t ->times;
            strcpy(maxTitle, t ->title);
        }

        else if(t ->times == maxTimes)
            if (strcmp(t ->title, maxTitle) < 0)
                strcpy(maxTitle, t ->title);
    }
}

void citeTree::clear(node *t)
{
    if (t == nullptr) return;

    clear(t ->left);
    clear(t ->right);
    delete t;
}

int main()
{
    citeTree tree;
    char command[10], title[150];

    while (true)
    {
        scanf("%s", command);
        cin.get();//丢掉空格

        if (!strcmp(command, "cite"))
        {
            fgets(title, 149, stdin);//接收标题
            title[strlen(title)] = '\0';
            tree.insert(title);
        }

        else if(!strcmp(command, "query"))
            printf("%d %s", maxTimes, maxTitle);

        else if (!strcmp(command, "finish"))
            break;
    }

    return 0;    
}