#include <iostream>
#include <stack>
using namespace std;

//无限背包（无限背包）---回溯法
//时间效率太低了！！！
struct elem
{
    int v, w;//体积和价值
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int max, k, size, v, w, cur;//体积和当前价值
    cin >> v;
    cin >> size;//样品的数量
    elem *thing = new elem[size];
    for (int i = 0; i <size; i++)
    {
        cin >> thing[i].v;
        cin >> thing[i].w;
    }

    k = 0; w = 0; cur = 0; max = 0;
    stack<int> st;

    do{
        while (cur < v && k < size)
        {
            while (cur + thing[k].v <= v)
            {
                st.push(k); cur += thing[k].v; w += thing[k].w;
            }

            k++;
        }

        if (w > max) max = w;//更新最大值

        if (!st.empty())
        {
            k = st.top(); st.pop(); cur -= thing[k].v;
            w -= thing[k].w; k++;
        }

    }while (!st.empty() || k < size);

    cout << max << '\n';

    return 0;
}


//0-1背包动态规划
//思想就是m(i)(w) = max(m(i-1)(w), m(i-1)(w - W[i]) + value[i])
//即当前的最大，是将 i 不放进去 和将 i 放进去的最大
//具体将 i 放进去的最大就是 没将 i 放进去时 总体积减去 i 的体积 加上 i 的价值
const int MAXSIZE = 10003;
const int MAXV = 20000;
int weight[MAXSIZE] = {0};
int value[MAXV] = {0};
int m[MAXSIZE][MAXV] = {0};

inline int Max(int n1, int n2)
{
    return n1 > n2 ? n1 : n2;
}

//动态规划
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int size, v, minv = 1000000;//体积和当前价值
    cin >> v;
    cin >> size;//样品的数量
    for (int i = 1; i <= size; i++)//接收重量和价值
    {
        cin >> weight[i] >> value[i];
        if (minv > weight[i])
            minv = weight[i];
    }

    for (int i = 1; i <= size; i++)//当前的物品种类数
    {
        for (int j = minv; j <= v; j++)
        {
            if (j - weight[i] >= 0)
            m[i][j] = Max(m[i-1][j], m[i-1][j-weight[i]] + value[i]);
            //取（物品数不增加，体积增加）与（物品数不增加情况下，当前重量减去将要进入的重量的物品的价值
            //加上将要进入的物品的价值）的最大值
            else
            m[i][j] = m[i-1][j];
            cout << i << " " << j << "最大价值为 "<< m[i][j] << endl;

        }
    }

    cout << m[size][v] << '\n';

    return 0;
}

void knapsack(int w[], int T, int size)
{
    //已知n件物品的体积，背包的总体积
    //输出所有能刚好装满背包的解
    stack<int> st;
    int k = 0;
    do{
        while (T > 0 && k < size)
        {
            if (T - w[k] >= 0)
            {
                st.push(k); T -= w[k];
            }
            k++;
        }

        if (T == 0)//表示找打了合理解，将结果输出，栈顶弹出，进行下次循环
        {
            st.traverse();
            k = st.top();
            st.pop();
            T += w[k];
            k++;
        }
        else if (T != 0 && !st.empty())//表示当前已经到了数组尾，切没有找打合理的解
        {
            k = st.top();
            st.pop();
            T += w[k];
            k++;
        }

        else break;

    } while (!st.empty() || (k < size));
}

