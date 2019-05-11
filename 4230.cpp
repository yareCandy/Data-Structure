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

 
class citeTree
{
private:
    struct node
    {
        char title[300];
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
        //node ():left(nullptr), right(nullptr){}
    };

    node *root;
public:
    citeTree():root(nullptr){}
    ~citeTree(){clear(root);}
    int insert(const char a[]);
private:
    void clear(node *t);
    int insert(const char a[], node * &t);
};
 
int citeTree::insert(const char a[])
{
    return insert(a, root);
}
 
int citeTree::insert(const char title[], node * &t)
{
    if (t == nullptr) {t = new node (title); return 1;}
    else if (strcmp(title, t ->title) > 0)
        return insert(title, t ->right);
    else if (strcmp(title, t ->title) < 0)
        return insert(title, t ->left);
    else return ++t ->times;
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
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //保存目前最大引用数的论文
    int i, times, maxTimes = 0;
    char maxTitle[300];

    citeTree tree;
    char ch, command[10], title[300];
 
    while (true)
    {
        cin >> command;
        cin.get();//丢掉空格
 
        if (strcmp(command, "cite") == 0)
        {
            i = 0;//单1字符读入的效率！！！！！
            //cin.getline(title, 150);//接收标题
            while(true)
            {
                cin.get(ch);
                if (ch == '\n') break;
                else title[i++] = ch;
            }
            title[i] = '\0';
            
            times = tree.insert(title);

            if (times > maxTimes)
            {
                maxTimes = times;
                strcpy(maxTitle, title);
            }
            else if(times == maxTimes && strcmp(title, maxTitle) < 0)
                strcpy(maxTitle, title);
        }
 
        else if(strcmp(command, "query") == 0)
            cout << maxTimes << ' ' << maxTitle << '\n';
        else if (strcmp(command, "finish") == 0)
            break;
    }
 
    return 0;    
}