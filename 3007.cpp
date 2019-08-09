//OJ3007
//根据先序遍历和中序遍历求解后序遍历

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct node
{
    char label;
    node *left;
    node *right;
    node (int la = 0, node *l = nullptr, node *r = nullptr)
        :label(la), left(l), right(r){}
};

void create(char *per, char *post, node *& t);
void postOrder(node *t);

int main()
{
    char perOrder[30];
    char midOrder[30];
    cin >> perOrder;
    cin.get();
    cin >> midOrder;
    node *root = nullptr;

    create(perOrder, midOrder, root);
    postOrder(root);
    cout << '\n';
    return 0;
}

void create(char *per, char *mid, node *&t)
{
    t = new node(per[0]);
    char per1[30], mid1[30], per2[30], mid2[30];//左孩子的前中序，右孩子的前中序  
    
    int i = 0;
    while (mid[i] != '\0' && mid[i] != per[0])
    {
        mid1[i] = mid[i];
        i++;        //左孩子的中序遍历
    }
    mid1[i] = '\0';

    strcpy(mid2, mid+i+1);
    strncpy(per1, per+1, i);
    per1[i] = '\0';

    strcpy(per2, per+i+1);

    if (mid1[0] == '\0')//左孩子中序为空，没有右孩子
        t ->left = nullptr;
    else create(per1, mid1, t ->left);

    if(mid2[0] == '\0')
        t ->right = nullptr;
    else create(per2, mid2, t ->right);
}

void postOrder(node *t)
{
    if (t == nullptr) return;
    postOrder(t ->left);
    postOrder(t ->right);
    cout << t ->label;
}

