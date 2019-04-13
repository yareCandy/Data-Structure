    //OJ1599
    //括号栈
    //支持的操作，插入，弹出，显示栈顶，检查匹配
    //三个栈作用
    #include <iostream>
    using namespace std;


    template <class T>
    class linkStack
    {
        private:
            struct node
            {
                T data;
                node *next;
                node (const T &x, node *n = NULL):data(x), next(n){};
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
            T top()const{return top_p -> data;}
            T pop()
            {
                node *tmp = top_p;
                T x = top_p -> data;
                top_p = top_p -> next;
                delete tmp;
                return x;
            }
            bool isEmpty()const {return top_p == NULL;}
    };

    linkStack<char> stack, pasent, tmp;//stack判匹配否， pasent存储所有元素

    int main()
    {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int size, op;
        char ch, s;
        cin >> size;

        for (int i = 0; i < size; i++)
        {
            cin >> op;
            switch(op)
            {
                case 1: cin.get();
                        scanf("%c", &ch);
                        pasent.push(ch);

                        if (!stack.isEmpty() && ((stack.top() == '[' && ch == ']') ||
                         (stack.top() == '{' && ch == '}') ||(stack.top() == '(' && ch == ')')))
                            tmp.push(stack.pop());
                        else {stack.push(ch); tmp.push(0);}
                        break;

                case 2: if (pasent.isEmpty()) break;
                        pasent.pop();
                        s = tmp.top();
                        if (s == 0) stack.pop();
                        else stack.push(s);
                        tmp.pop();
                        break;

                case 3: if (!pasent.isEmpty()) cout << pasent.top() << "\n";
                        break;

                case 4: if (stack.isEmpty()) cout << "YES\n";
                        else cout << "NO\n";
                        break;
            }
        }
        return 0;
    }
