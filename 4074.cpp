//有一块矩形土地被划分成 N×M 个正方形小块，每块是一平方米。这些小块高低不平，
//每一小块地都有自己的高度H(i, j)米。水可以由任意一块地流向周围四个方向的四块地中，
//但不能直接流入对角相连的小块中。一场大雨后，许多低洼地方都积存了不少降水，求出它最多能积存多少立方米的降水么?

//思路：
//根据木桶原理，水位的高低取决于最低的边界。我们可以从最低的边界入手，向内灌水，使水面于边界齐平。如果灌到了新的边界，而且不低于最低的边界，则这个点一定是不能被灌水的。
//可以想象成一个深度搜索的过程，我们从最低边界开始灌水，遇到比最低边界低的，它的水平面顶多就是最低边界，直到遇到一个边界比最低边界高的，将高边界放入优先队列中。
//每次取边界最小值向内灌水，于是可以用一个最小堆来维护高度。
//算法流程如下：
//把所有的边界上的点加入堆，且标记为已使用过。
//取出高度最小的点(x,y)，枚举与(x,y)相邻的未使用过的点(x’,y’)，从(x’,y’)开始Floodfill，边界高度h=(x,y)的高度。
//重复第二步，直到堆为空。

//Floodfill(x,y)
//标记(x,y)为已使用过。
//如果(x,y)的高度>=h，则该点不能积水，加入堆并返回。
//否则(x,y)的点的积水量为h-(x,y)的高度。
//枚举与(x,y)相邻的未使用过的点(x’,y’)，Floodfill(x’,y’)。

#include<cstdio>
#include<iostream>
using namespace std;

struct point{
    struct xy
    {
        int x, y;
    };
    xy p;
    int height;
};

class priority_queue
{
private:
    point *dt;
    int maxSize;
    int curSize;

    void doubleSpace();
    void buildHeap();
    void perDown(int i);
public:
    priority_queue(int size = 104);
    priority_queue(point a[], int size);
    ~priority_queue(){delete [] dt;}
    void push(const point &d);
    point pop();
    point top()const {return dt[1];}
    bool empty(){return curSize == 0;}
};

priority_queue::priority_queue(point a[], int size)
{
    curSize = size;
    maxSize = 2 * size;
    dt = new point[maxSize];
    for (int i = 0; i < size; i++)
        dt[i+1] = a[i];
    buildHeap();
}

priority_queue::priority_queue(int size)
{
    dt = new point [size];
    curSize = 0;
    maxSize = size;
}

void priority_queue::push(const point &d)
{
    if (curSize == maxSize -1) doubleSpace();

    int hole = ++curSize;

    for (; hole > 1 && dt[hole/2].height > d.height; hole /=2)
        dt[hole] = dt[hole/2];
    dt[hole] = d;
}

void priority_queue::doubleSpace()
{
    point *tmp = dt;
    maxSize *= 2;
    dt = new point[maxSize];
    for (int i = 1; i <= curSize; i++)
        dt[i] = tmp[i];
}

point priority_queue::pop()
{
    point tmp = dt[1];
    dt[1] = dt[curSize--];
    perDown(1);
    return tmp;
}

void priority_queue::perDown(int i)
{
    int child;
    point tmp = dt[i];
    for (; 2 * i <= curSize; i = child)
    {
        child = i * 2;
        if (child < curSize && dt[child + 1].height < dt[child].height)
            child ++;
        
        if (dt[child].height < tmp.height) dt[i] = dt[child];
        else break;
    }
    dt[i] = tmp;
}

void priority_queue::buildHeap()
{
    for (int i = curSize/2; i > 0; i --)
        perDown(i);
}



int u[4][2]={{0, 1}, {0, -1}, {1, 0}, {-1,0}};//移动方向

priority_queue que;//最小化优先队列
int m, n;//土地规模

int map[104][104];//土地的海拔图
int ans[104][104];//保存每个位置所能保存的最大体积
bool pd[104][104];//保存元素的转态，是否已经检查过

void Pre()//初始化：将边界元素入堆
{
    int i, j;
    point in;
    for(i = 1; i <= n; i++)
    {
        in.p.x = i; in.p.y = 1;
        in.height = map[i][1]; 
        pd[i][1] = 1;
        que.push(in);

        in.p.x = i; in.p.y = m;
        in.height = map[i][m]; 
        pd[i][m] = 1;
        que.push(in);
    }

    for (j = 2; j <= m; j++)
    {
        in.p.x = 1; in.p.y = j;
        in.height = map[1][j];
        pd[1][j] = 1;
        que.push(in);

        in.p.x = n; in.p.y = j;
        in.height = map[n][j];
        que.push(in);
        pd[n][j] = 1;
    }
    
}

bool inmap(point &p){
    return p.p.x <= n && p.p.x >= 1 && p.p.y >= 1 && p.p.y <= m;
}

void Fill(point &z,int h){
    int i, xx = z.p.x, yy = z.p.y;

    pd[xx][yy] = 1;//标记该元素已经处理过
    if(z.height >= h)//邻近元素海拔较高，无法储水
    {
        que.push(z);
        return;
    }

    //临近元素海拔较低，可以储水时
    ans[xx][yy] += h - map[xx][yy];
    for(i = 0; i < 4; i++)
    {
        point t;//四个方向试探能否继续储水
        t.p.x = xx + u[i][0]; 
        t.p.y = yy + u[i][1];
        t.height = map[t.p.x][t.p.y];

        if(inmap(t) && !pd[t.p.x][t.p.y])
            Fill(t,h);
    }
}

void Search()
{
    int i;
    point temp;

    while(!que.empty()){
        temp = que.top();
        que.pop();
        for(i = 0; i < 4; i++){
            point t;

            t.p.x = temp.p.x + u[i][0]; 
            t.p.y = temp.p.y + u[i][1]; 
            t.height = map[t.p.x][t.p.y];

            if(inmap(t) && !pd[t.p.x][t.p.y])
                Fill(t, temp.height);
        }
    }
}

int main()
{
    int result = 0, i, j;
    
    cin >> n >> m;

    for(i = 1; i <= n; i++)
        for(j = 1; j <= m; j++)
            cin >> map[i][j];
            
    Pre();
    Search();

    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            result += ans[i][j];
    cout << result << '\n';

    return 0;
}