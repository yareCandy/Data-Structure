//binaryTree.h
//二叉链表法实现二叉树

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template<class  T>
class binaryTree;
template<class T>
void printTree(const binaryTree<T> &t, T flag);

template<class T>
class binaryTree
{
    friend void printTree<T>(const binaryTree<T> &t, T flag);
    private:
        struct node
        {
            T dt;
            node *lchild;
            node *rchild;

            node (const T &d, node *l = NULL, node *r = NULL)
                :dt(d), lchild(l), rchild(r){}
            node (): lchild(NULL), rchild(NULL){}
            ~node(){}
        };

        node *root;

    public:
        binaryTree();                              //默认构造函数
        binaryTree(const T &);                     //构造函数
        ~binaryTree();                             //析构
        void clear();                              //清空树函数的包裹函数
//        T getParent(const T &, const T flag)const; //获取父节点
        T getlChild(const T &, const T flag)const; //获取左儿子
        T getrChild(const T &, const T flag)const; //获取右儿子
        void delLeft(const T &);                   //删除左子树
        void delRight(const T &);                  //删除右子树
        bool isEmpty()const;                       //判树空
        T getRoot(const T flag)const;              //获取树根
        void createTree(T flag);                   //辅助完成创建树
        void preOrder()const;                      //前序遍历包裹函数
        void midOeder()const;                      //中序遍历包裹函数
        void postOrder()const;                     //后序遍历包裹函数
        void levelOrder()const;                    //层次遍历包裹函数

    private:
        node *find(const T &, node *t)const;       //查询对应数据所在节点位置
        void clear(node *&t);                      //删除树的所有节点，实际函数
        void preOrder(node *t)const;               //实际前序遍历函数
        void midOeder(node *t)const;               //实际中序遍历函数
        void postOrder(node *t)const;              //实际后序遍历函数
};

template<class T>
binaryTree<T>::binaryTree()
{
    root = NULL;
}

template <class T>
binaryTree<T>::binaryTree(const T &x)
{
    root = new node(x);
}

template<class T>
binaryTree<T>::~binaryTree()
{
    clear(root);
}

template<class T>
bool binaryTree<T>::isEmpty()const
{
    return root == NULL;
}

template<class T>
T binaryTree<T>::getlChild(const T &d, const T flag)const
{
    node *tmp = find(d, root);
    if (tmp == NULL || tmp ->rchild == NULL) return flag;

    return tmp ->rchild -> dt;
}

template <class T>
void binaryTree<T>::clear()
{
    clear(root);
}

template<class T>
T binaryTree<T>::getrChild(const T &d, const T flag)const
{
    node *tmp = find(d, root);
    if (tmp == NULL || tmp ->rchild == NULL) return flag;

    return tmp ->rchild -> dt;
}

/*
template<class T>
void binaryTree<T>::getParent(const T &d, const T flag)const
{
    node *tmp = find (d, root);
    if (tmp == NULL || tmp ->parent == NULL) return flag;

    return tmp ->parent ->dt;
}
*/

template<class T>
void binaryTree<T>::delLeft(const T &d)
{
    node *tmp = find(d, root);
    if (tmp == NULL) return;
    clear(tmp ->lchild);
}

template<class T>
void binaryTree<T>::delRight(const T &d)
{
    node *tmp = find(d, root);
    if (tmp == NULL) return;
    clear(tmp ->rchild);
}


template<class T>
T binaryTree<T>::getRoot(const T flag)const
{
    if (root == NULL) return flag;
    return root ->dt;
}


template<class T>
void binaryTree<T>::preOrder()const
{
    cout << "\nPreorder traverse: ";
    preOrder(root);
}

template<class T>
void binaryTree<T>::preOrder(binaryTree<T>::node *t)const
{
    if (t == NULL) return;

    cout << t ->dt << ' ';
    preOrder(t ->lchild);
    preOrder(t ->rchild);
}


template<class T>
void binaryTree<T>::midOeder()const
{
    cout << "\nMidoeder traverse: ";
    midOeder(root);
}

template<class T>
void binaryTree<T>::midOeder(binaryTree<T>::node *t)const
{
    if (t == NULL) return;

    midOeder(t ->lchild);
    cout << t ->dt <<' ';
    midOeder(t ->rchild);
}

template<class T>
void binaryTree<T>::postOrder()const
{
    cout << "\nPostorder traverse: ";
    postOrder(root);
}

template <class T>
void binaryTree<T>::postOrder(binaryTree<T>::node *t)const
{
    postOrder(t ->lchild);
    postOrder(t ->rchild);
    cout << t ->dt;
}


//level traverse
//use the characteristic of queue
//FIFO: first-in first-out
template <class T>
void binaryTree<T>::levelOrder()const
{
    queue<node *> que;
    node *tmp;

    cout << "\nLevelOrder traverse: ";
    que.enQueue(root);

    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        cout << tmp ->dt;
        if (tmp ->lchild) que.enQueue(tmp ->lchild);
        if (tmp ->rchild) que.enQueue(tmp ->rchild);
    }
}


template<class T>
void binaryTree<T>::createTree(T flag)
{
    queue<node *> que;
    node *tmp;
    T x, ldata, rdata;

    //Create a tree, flag represents NULL
    cout << "Input the root: ";
    cin >> x;

    root = new node(x);
    que.enQueue(root);

    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        cout << "Input " << tmp ->dt << "'s two sons(" << flag << "represents NULL): ";
        cin >> ldata >> rdata;
        if (ldata != flag) que.enQueue(tmp ->lchild = new node(ldata));
        if (rdata != flag) que.enQueue(tmp ->rchild = new node(rdata));
    }
    cout << "Create completely!" << endl;
}

template<class T>
void binaryTree<T>::clear(binaryTree<T>::node *&t)
{
    if (t == NULL) return;

    clear(t ->lchild);
    clear(t ->rchild);
    delete t;
    t = NULL;
}

template<class T>
void printTree(const binaryTree<T> &t, T flag)
{
    queue<T> que;

    if (t.root == NULL) cout << flag << endl;
    que.enQueue(t.root ->dt);
    while (!que.isEmpty())
    {
        T tmp, lc, rc;

        tmp = que.deQueue();
        cout << tmp  << endl;
        lc = t.getlChild(tmp, flag);
        rc = t.getrChild(tmp, flag);
        cout << tmp << ' ' << lc << ' '<< rc << endl;
        if (lc != flag) que.enQueue(lc);
        if (rc != flag) que.enQueue(rc);
    }
}

//Preorder traverse non-recursive implementation

template<class T>
void binaryTree<T>::preOrder()const
{
    stack<binaryTree<T>::node *> stack;
    node *tmp = root;
    if (tmp == NULL) return;

    stack.push(tmp);
    while (!stack.isEmpty())
    {
        tmp = stack.pop();
        cout << tmp ->dt << ' ';
        if (tmp ->rchild != NULL) stack.push(tmp ->rchild);
        if (tmp ->lchild != NULL) stack.push(tmp ->lchild);
    }
}

//Midorder traverse non-recursive implmentation
template<class T>
void binaryTree<T>::midOeder()const
{
    struct slNode
    {
        int timeOfPop;
        node *n;
        slNode(binaryTree<T>::node *t): n(t), timeOfPop(0){}
    };

    stack<slNode *> stack;
    slNode s(root);
    stack.push(s);

    while (!stack.isEmpty())
    {
        s = stack.pop();
        s.timeOfPop ++;
        if (s.timeOfPop == 2)
        {
            cout << s.n ->dt;
            if (s.n ->rchild != NULL)
                stack.push(slNode(s.n ->rchild));
        }
        else
        {
            stack.push(s);
            if (s.n ->lchild != NULL)
                stack.push(slNode(s.n ->lchild));
        }
    }
}

//PostOrder traverse non-recusive implemention
template<class T>
void binaryTree<T>::postOrder()const
{
    struct slNode
    {
        int timeOfPop;
        node *n;
        slNode(binaryTree<T>::node *t): n(t), timeOfPop(0){}
    };

    stack<slNode *> stack;
    slNode s(root);
    stack.push(s);

    while (!stack.isEmpty())
    {
        s = stack.pop();
        s.timeOfPop ++;
        if (s.timeOfPop == 3)            //third times out stack, root can be visited
        {
            cout << s.n ->dt << ' ';
            continue;
        }

        s.push(s);
        if (s.timeOfPop == 1)            //first times out stack, let left sons in stack
        {
            if (s.n ->lchild != NULL)
                stack.push(slNode(s.n ->lchild));
        }
        else                             //second times out stack, let right sons in stack
        {
            if (s.n ->rchild != NULL)
                stack.push(slNode(s.n ->rchild));
        }

    }
}


int main()
{
    binaryTree<char> tree;
    tree.createTree('@');
    tree.preOrder();
    tree.midOeder();
    tree.postOrder();
    tree.levelOrder();
    printTree(tree, '@');
    tree.delLeft('L');
    tree.delRight('C');
    printTree(tree, '@');

    return 0;
}
