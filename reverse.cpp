//循环单链表的逆转

#include <iostream>
using namespace std;

template <class elemType>
class sLinkList{
  private :
      struct node{
      elemType data;
      node *next;
      node(const elemType &x, node *n=NULL){ data = x; next = n;}
      node():next(NULL){}
      ~node(){}
      };

      node *head;
      int currentLength;

      node *Move(int i) const
      {
        node *p = head;
        while (i-- >=0) p = p->next;
        return p;
      }
  public  :
      sLinkList();
      ~sLinkList(){Clear(); delete head;}
      void Clear();
      void Insert(int i, const elemType &x);
      void traverse() const;
      void Reverse();
};

template <class elemType>
sLinkList<elemType>::sLinkList()
{
    head = new node;
    currentLength = 0;
}

template <class elemType>
void sLinkList<elemType>::Clear()
{
    node *p = head->next, *q;
    head->next = NULL;
    while (p!=NULL){
        q=p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

template <class elemType>
void sLinkList<elemType>::Insert(int i, const elemType &x)
{
    node *pos;

    pos = Move(i-1);
    pos->next = new node(x,pos->next);
    ++currentLength;
}

template <class elemType>
void sLinkList<elemType>::traverse() const
{
    node *p = head->next;
    cout << endl;
    while (p!=NULL){
        cout << p->data << " ";
        p = p->next;
    }
}

template <class elemType>
void sLinkList<elemType>::Reverse()
{
      node *p,*q,*tmp;
      p = head->next;
      if (p!=NULL){
        q = p->next;
        if (q!=NULL){
            p->next = NULL;
            while (q->next!=NULL){
                tmp=q->next;
                q->next = p;
                p = q;
                q = tmp;
            }
            q->next = p;
            head->next = q;
        }
      }
}

int main()
{
    int n,i;
    cout << "Input n:" <<endl;
    cin >> n;

    sLinkList<int> s;
    for (i=0;i<n;i++){
        s.Insert(i,i);
    }
    s.traverse();
    cout <<endl;
    s.Reverse();
    s.traverse();
    return 0;
}
